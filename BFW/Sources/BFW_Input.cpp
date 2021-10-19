#include "..\Headers\BFW.hpp"



#ifdef BFW_WINDOWS_PLATFORM



BFW::Input::Key::Key() : VKCode(0xFF), HoldTimer(), State()
{
	State[Enums::_Previous] = false;
	State[Enums::_Current] = false;
}

BFW::Input::Key::Key(const Key& _Other) : VKCode(_Other.VKCode), HoldTimer((const Time::Timer&)(_Other.HoldTimer)), State()
{
	State[Enums::_Previous] = _Other.State[Enums::_Previous];
	State[Enums::_Current] = _Other.State[Enums::_Previous];
}

BFW::Input::Key::Key(Key&& _Other) noexcept : VKCode(_Other.VKCode), HoldTimer((Time::Timer&&)(_Other.HoldTimer)), State()
{
	State[Enums::_Previous] = _Other.State[Enums::_Previous];
	State[Enums::_Current] = _Other.State[Enums::_Previous];

	_Other.VKCode = 0xFF;
	_Other.State[Enums::_Previous] = false;
	_Other.State[Enums::_Current] = false;
}

BFW::Input::Key::~Key()
{

}

void BFW::Input::Key::UpdateState()
{
	State[Enums::_Previous] = State[Enums::_Current];
	State[Enums::_Current] = ((GetAsyncKeyState(VKCode) & 0x1000000000000000) != 0);

	if (!State[Enums::_Previous] && !State[Enums::_Current])
	{
		HoldTimer.Reset();
	}

	if (!State[Enums::_Previous] && State[Enums::_Current])
	{
		HoldTimer.Start();
	}
	if (State[Enums::_Previous] && !State[Enums::_Current])
	{
		HoldTimer.Stop();
	}
}

void BFW::Input::Key::DeleteState()
{
	State[Enums::_Previous] = false;
	State[Enums::_Current] = false;
	HoldTimer.Reset();
	GetAsyncKeyState(VKCode);
}

void BFW::Input::Key::SetVKCode(const unsigned char _VKCode)
{
	VKCode = _VKCode;

	State[Enums::_Previous] = false;
	State[Enums::_Current] = false;
	HoldTimer.Reset();
	GetAsyncKeyState(VKCode);
}

const unsigned char BFW::Input::Key::GetVKCode() const
{
	return VKCode;
}

const BFW::Time::Timer& BFW::Input::Key::GetHoldTimer() const
{
	return HoldTimer;
}

const bool BFW::Input::Key::operator[] (const unsigned long _Index) const
{
	return State[_Index];
}

void BFW::Input::Key::operator= (const Key& _Other)
{
	VKCode = _Other.VKCode;
	HoldTimer = (const Time::Timer&)(_Other.HoldTimer);
	State[Enums::_Previous] = _Other.State[Enums::_Previous];
	State[Enums::_Current] = _Other.State[Enums::_Previous];
}

void BFW::Input::Key::operator= (Key&& _Other) noexcept
{
	VKCode = _Other.VKCode;
	HoldTimer = (Time::Timer&&)(_Other.HoldTimer);
	State[Enums::_Previous] = _Other.State[Enums::_Previous];
	State[Enums::_Current] = _Other.State[Enums::_Previous];

	_Other.VKCode = 0xFF;
	_Other.HoldTimer.Reset();
	_Other.State[Enums::_Previous] = false;
	_Other.State[Enums::_Current] = false;
}



static POINT _CursorPosition = { 0 };

const BFW::Typedef::PointRef BFW_API BFW::Input::Cursor::CursorPosition = _CursorPosition;



void BFW_API BFW::Input::Cursor::UpdatePosition()
{
	GetCursorPos(&_CursorPosition);
}

bool BFW_API BFW::Input::Cursor::SetPosition(const long _X, const long _Y)
{
	if (!SetCursorPos(_X, _Y))
	{
		return false;
	}

	_CursorPosition.x = _X;
	_CursorPosition.y = _Y;

	return true;
}



BFW::Input::RumbleState::RumbleState(const unsigned short _RumbleSpeedLeft, const unsigned short _RumbleSpeedRight, const float _Begin, const float _End) :
	RumbleSpeedLeft(_RumbleSpeedLeft), RumbleSpeedRight(_RumbleSpeedRight), Begin(_Begin), End(_End)
{

}

BFW::Input::RumbleState::RumbleState(const RumbleState& _Other) :
	RumbleSpeedLeft(_Other.RumbleSpeedLeft), RumbleSpeedRight(_Other.RumbleSpeedRight), Begin(_Other.Begin), End(_Other.End)
{

}

BFW::Input::RumbleState::RumbleState(RumbleState&& _Other) noexcept :
	RumbleSpeedLeft(_Other.RumbleSpeedLeft), RumbleSpeedRight(_Other.RumbleSpeedRight), Begin(_Other.Begin), End(_Other.End)
{
	_Other.RumbleSpeedLeft = 0;
	_Other.RumbleSpeedRight = 0;
	_Other.Begin = 0.0f;
	_Other.End = 0.0f;
}

BFW::Input::RumbleState::~RumbleState()
{

}

void BFW::Input::RumbleState::operator= (const RumbleState& _Other)
{
	RumbleSpeedLeft = _Other.RumbleSpeedLeft;
	RumbleSpeedRight = _Other.RumbleSpeedRight;
	Begin = _Other.Begin;
	End = _Other.End;
}

void BFW::Input::RumbleState::operator= (RumbleState&& _Other) noexcept
{
	RumbleSpeedLeft = _Other.RumbleSpeedLeft;
	RumbleSpeedRight = _Other.RumbleSpeedRight;
	Begin = _Other.Begin;
	End = _Other.End;

	_Other.RumbleSpeedLeft = 0;
	_Other.RumbleSpeedRight = 0;
	_Other.Begin = 0.0f;
	_Other.End = 0.0f;
}



BFW::Input::RumbleSequence::RumbleSequence() : Time(0), Index(0), RumbleStateVec()
{

}

BFW::Input::RumbleSequence::RumbleSequence(const RumbleSequence& _Other) :
	Time(_Other.Time), Index(_Other.Index), RumbleStateVec((const Vector<RumbleState>&)(_Other.RumbleStateVec))
{

}

BFW::Input::RumbleSequence::RumbleSequence(RumbleSequence&& _Other) noexcept :
	Time(_Other.Time), Index(_Other.Index), RumbleStateVec((Vector<RumbleState>&&)(_Other.RumbleStateVec))
{
	_Other.Time = 0;
	_Other.Index = 0;
}

BFW::Input::RumbleSequence::~RumbleSequence()
{

}

bool BFW::Input::RumbleSequence::Update(const float _DeltaTime)
{
	if (!RumbleStateVec.GetSize())
	{
		return false;
	}

	Time = Math::fPeriod(Time + _DeltaTime, 0.0f, RumbleStateVec[RumbleStateVec.GetSize() - 1].End);

	for (unsigned long _Index = Index; _Index < RumbleStateVec.GetSize(); _Index++)
	{
		if (Time >= RumbleStateVec[_Index].Begin && Time < RumbleStateVec[_Index].End)
		{
			Index = _Index;
			return true;
		}
	}

	for (unsigned long _Index = 0; _Index < Index; _Index++)
	{
		if (Time >= RumbleStateVec[_Index].Begin && Time < RumbleStateVec[_Index].End)
		{
			Index = _Index;
			return true;
		}
	}

	return false;
}

void BFW::Input::RumbleSequence::SetTime(const float _Time)
{
	if (!RumbleStateVec.GetSize())
	{
		return;
	}

	Time = Math::fPeriod(_Time, 0.0f, RumbleStateVec[RumbleStateVec.GetSize() - 1].End);

	for (unsigned long i = 0; i < RumbleStateVec.GetSize(); i++)
	{
		if (Time >= RumbleStateVec[i].Begin && Time < RumbleStateVec[i].End)
		{
			Index = i;
			return;
		}
	}
}

void BFW::Input::RumbleSequence::SetIndex(const unsigned long _Index)
{
	if (!RumbleStateVec.GetSize())
	{
		return;
	}

	Index = _Index;
	Time = RumbleStateVec[_Index].Begin;
}

const float BFW::Input::RumbleSequence::GetTime() const
{
	return Time;
}

const unsigned long BFW::Input::RumbleSequence::GetIndex() const
{
	return Index;
}

const BFW::Input::RumbleState& BFW::Input::RumbleSequence::GetCurrentRumbleState() const
{
	return RumbleStateVec[Index];
}

BFW::Vector<BFW::Input::RumbleState>& BFW::Input::RumbleSequence::GetRumbleStateVec()
{
	return RumbleStateVec;
}

const BFW::Vector<BFW::Input::RumbleState>& BFW::Input::RumbleSequence::GetRumbleStateVec() const
{
	return RumbleStateVec;
}

void BFW::Input::RumbleSequence::Load(const float* _Time, const unsigned short* _RumbleSpeed, const unsigned long _Count)
{
	RumbleStateVec.Clear();

	for (unsigned long _Index = 0; _Index < _Count; _Index++)
	{
		RumbleState _Aux = { 0 };

		_Aux.Begin = _Time[_Index * 2];
		_Aux.End = _Time[_Index * 2 + 1];
		_Aux.RumbleSpeedLeft = _RumbleSpeed[_Index * 2];
		_Aux.RumbleSpeedRight = _RumbleSpeed[_Index * 2 + 1];

		RumbleStateVec.PushBack(_Aux);
	}
}

void BFW::Input::RumbleSequence::Load(const float* _Begin, const float* _End, const unsigned short* _RumbleSpeedLeft, const unsigned short* _RumbleSpeedRight, const unsigned long _Count)
{
	RumbleStateVec.Clear();

	for (unsigned long _Index = 0; _Index < _Count; _Index++)
	{
		RumbleState _Aux = { 0 };

		_Aux.Begin = _Begin[_Index];
		_Aux.End = _End[_Index];
		_Aux.RumbleSpeedLeft = _RumbleSpeedLeft[_Index];
		_Aux.RumbleSpeedRight = _RumbleSpeedRight[_Index];

		RumbleStateVec.PushBack(_Aux);
	}
}

void BFW::Input::RumbleSequence::operator= (const RumbleSequence& _Other)
{
	Time = _Other.Time;
	Index = _Other.Index;
	RumbleStateVec = (const Vector<RumbleState>&)(_Other.RumbleStateVec);
}

void BFW::Input::RumbleSequence::operator= (RumbleSequence&& _Other) noexcept
{
	Time = _Other.Time;
	Index = _Other.Index;
	RumbleStateVec = (Vector<RumbleState>&&)(_Other.RumbleStateVec);

	_Other.Time = 0;
	_Other.Index = 0;
}



BFW::Input::Controller::Controller(const unsigned long _ID) :
	Start(_Start), Select(_Select),
	XLeft(_XLeft), YLeft(_YLeft), XRight(_XRight), YRight(_YRight),
	ThumbLeft(_ThumbLeft), ThumbRight(_ThumbRight),
	BtnLeft(_BtnLeft), BtnRight(_BtnRight), BtnUp(_BtnUp), BtnDown(_BtnDown),
	DPadLeft(_DPadLeft), DPadRight(_DPadRight), DPadUp(_DPadUp), DPadDown(_DPadDown),
	ShoulderUpLeft(_ShoulderUpLeft), ShoulderUpRight(_ShoulderUpRight),
	ShoulderDownLeft(_ShoulderDownLeft), ShoulderDownRight(_ShoulderDownRight),
	ID(_ID),
	Connected(ValidID(_ID)),
	ThresHold(true), DeadZone(true),
	RumbleSpeedLeft(0), RumbleSpeedRight(0),
	_Start(), _Select(),
	_XLeft(), _YLeft(), _XRight(), _YRight(),
	_ThumbLeft(), _ThumbRight(),
	_BtnLeft(), _BtnRight(), _BtnUp(), _BtnDown(),
	_DPadLeft(), _DPadRight(), _DPadUp(), _DPadDown(),
	_ShoulderUpLeft(), _ShoulderUpRight(),
	_ShoulderDownLeft(), _ShoulderDownRight()
{
	DeleteState();
	SetRumbleSpeed(0, 0);
}

BFW::Input::Controller::~Controller()
{

}

bool BFW::Input::Controller::UpdateState()
{
	XINPUT_STATE State = { 0 };

	if (XInputGetState(ID, &State) != ERROR_SUCCESS)
	{
		Connected = false;
		DeleteState();
		SetRumbleSpeed(0, 0);
		return false;
	}

	Connected = true;

	_Start[Enums::_Previous] = _Start[Enums::_Current];
	_Select[Enums::_Previous] = _Select[Enums::_Current];
	_XLeft[Enums::_Previous] = _XLeft[Enums::_Current];
	_YLeft[Enums::_Previous] = _YLeft[Enums::_Current];
	_XRight[Enums::_Previous] = _XRight[Enums::_Current];
	_YRight[Enums::_Previous] = _YRight[Enums::_Current];
	_ThumbLeft[Enums::_Previous] = _ThumbLeft[Enums::_Current];
	_ThumbRight[Enums::_Previous] = _ThumbRight[Enums::_Current];
	_BtnLeft[Enums::_Previous] = _BtnLeft[Enums::_Current];
	_BtnRight[Enums::_Previous] = _BtnRight[Enums::_Current];
	_BtnUp[Enums::_Previous] = _BtnUp[Enums::_Current];
	_BtnDown[Enums::_Previous] = _BtnDown[Enums::_Current];
	_DPadLeft[Enums::_Previous] = _DPadLeft[Enums::_Current];
	_DPadRight[Enums::_Previous] = _DPadRight[Enums::_Current];
	_DPadUp[Enums::_Previous] = _DPadUp[Enums::_Current];
	_DPadDown[Enums::_Previous] = _DPadDown[Enums::_Current];
	_ShoulderUpLeft[Enums::_Previous] = _ShoulderUpLeft[Enums::_Current];
	_ShoulderUpRight[Enums::_Previous] = _ShoulderUpRight[Enums::_Current];
	_ShoulderDownLeft[Enums::_Previous] = _ShoulderDownLeft[Enums::_Current];
	_ShoulderDownRight[Enums::_Previous] = _ShoulderDownRight[Enums::_Current];

	_Start[Enums::_Current] = ((State.Gamepad.wButtons & XINPUT_GAMEPAD_START) != 0);
	_Select[Enums::_Current] = ((State.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) != 0);
	_XLeft[Enums::_Current] = State.Gamepad.sThumbLX * (!DeadZone) + State.Gamepad.sThumbLX * DeadZone * (State.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) + State.Gamepad.sThumbLX * DeadZone * (State.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
	_YLeft[Enums::_Current] = State.Gamepad.sThumbLY * (!DeadZone) + State.Gamepad.sThumbLY * DeadZone * (State.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) + State.Gamepad.sThumbLY * DeadZone * (State.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
	_XRight[Enums::_Current] = State.Gamepad.sThumbRX * (!DeadZone) + State.Gamepad.sThumbRX * DeadZone * (State.Gamepad.sThumbRX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) + State.Gamepad.sThumbRX * DeadZone * (State.Gamepad.sThumbRX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
	_YRight[Enums::_Current] = State.Gamepad.sThumbRY * (!DeadZone) + State.Gamepad.sThumbRY * DeadZone * (State.Gamepad.sThumbRY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) + State.Gamepad.sThumbRY * DeadZone * (State.Gamepad.sThumbRY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
	_ThumbLeft[Enums::_Current] = ((State.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) != 0);
	_ThumbRight[Enums::_Current] = ((State.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) != 0);
	_BtnLeft[Enums::_Current] = ((State.Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0);
	_BtnRight[Enums::_Current] = ((State.Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0);
	_BtnUp[Enums::_Current] = ((State.Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0);
	_BtnDown[Enums::_Current] = ((State.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0);
	_DPadLeft[Enums::_Current] = ((State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0);
	_DPadRight[Enums::_Current] = ((State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0);
	_DPadUp[Enums::_Current] = ((State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0);
	_DPadDown[Enums::_Current] = ((State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0);
	_ShoulderUpLeft[Enums::_Current] = ((State.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0);
	_ShoulderUpRight[Enums::_Current] = ((State.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0);
	_ShoulderDownLeft[Enums::_Current] = State.Gamepad.bLeftTrigger * (!ThresHold) + State.Gamepad.bLeftTrigger * ThresHold * (State.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
	_ShoulderDownRight[Enums::_Current] = State.Gamepad.bRightTrigger * (!ThresHold) + State.Gamepad.bRightTrigger * ThresHold * (State.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD);

	return true;
}

void BFW::Input::Controller::DeleteState()
{
	_Start[Enums::_Previous] = false; _Start[Enums::_Current] = false;
	_Select[Enums::_Previous] = false; _Select[Enums::_Current] = false;
	_XLeft[Enums::_Previous] = 0; _XLeft[Enums::_Current] = 0;
	_YLeft[Enums::_Previous] = 0; _YLeft[Enums::_Current] = 0;
	_XRight[Enums::_Previous] = 0; _XRight[Enums::_Current] = 0;
	_YRight[Enums::_Previous] = 0; _YRight[Enums::_Current] = 0;
	_ThumbLeft[Enums::_Previous] = false; _ThumbLeft[Enums::_Current] = false;
	_ThumbRight[Enums::_Previous] = false; _ThumbRight[Enums::_Current] = false;
	_BtnLeft[Enums::_Previous] = false; _BtnLeft[Enums::_Current] = false;
	_BtnRight[Enums::_Previous] = false; _BtnRight[Enums::_Current] = false;
	_BtnUp[Enums::_Previous] = false; _BtnUp[Enums::_Current] = false;
	_BtnDown[Enums::_Previous] = false; _BtnDown[Enums::_Current] = false;
	_DPadLeft[Enums::_Previous] = false; _DPadLeft[Enums::_Current] = false;
	_DPadRight[Enums::_Previous] = false; _DPadRight[Enums::_Current] = false;
	_DPadUp[Enums::_Previous] = false; _DPadUp[Enums::_Current] = false;
	_DPadDown[Enums::_Previous] = false; _DPadDown[Enums::_Current] = false;
	_ShoulderUpLeft[Enums::_Previous] = false; _ShoulderUpLeft[Enums::_Current] = false;
	_ShoulderUpRight[Enums::_Previous] = false; _ShoulderUpRight[Enums::_Current] = false;
	_ShoulderDownLeft[Enums::_Previous] = 0; _ShoulderDownLeft[Enums::_Current] = 0;
	_ShoulderDownRight[Enums::_Previous] = 0; _ShoulderDownRight[Enums::_Current] = 0;
}

void BFW::Input::Controller::SetID(const unsigned long _ID)
{
	ID = _ID;
	Connected = ValidID(_ID);
	DeleteState();
	SetRumbleSpeed(0, 0);
}

const unsigned long BFW::Input::Controller::GetID() const
{
	return ID;
}

const bool BFW::Input::Controller::CheckConnected() const
{
	return Connected;
}

void BFW::Input::Controller::SetThresHold(const bool _ThresHold)
{
	ThresHold = _ThresHold;
}

const bool BFW::Input::Controller::GetThresHold() const
{
	return ThresHold;
}

void BFW::Input::Controller::SetDeadZone(const bool _DeadZone)
{
	DeadZone = _DeadZone;
}

const bool BFW::Input::Controller::GetDeadZone() const
{
	return DeadZone;
}

bool BFW::Input::Controller::SetRumbleSpeed(const unsigned short _RumbleSpeedLeft, const unsigned short _RumbleSpeedRight)
{
	RumbleSpeedLeft = _RumbleSpeedLeft;
	RumbleSpeedRight = _RumbleSpeedRight;

	XINPUT_VIBRATION VibClass;

	VibClass.wLeftMotorSpeed = RumbleSpeedLeft;
	VibClass.wRightMotorSpeed = RumbleSpeedRight;

	if (XInputSetState(ID, &VibClass) != ERROR_SUCCESS)
	{
		Connected = false;
		RumbleSpeedLeft = 0;
		RumbleSpeedRight = 0;
		return false;
	}

	Connected = true;

	return true;
}

void BFW::Input::Controller::GetRumbleSpeed(unsigned short& _RumbleSpeedLeft, unsigned short& _RumbleSpeedRight) const
{
	_RumbleSpeedLeft = RumbleSpeedLeft;
	_RumbleSpeedRight = RumbleSpeedRight;
}

const bool BFW::Input::Controller::ValidID() const
{
	XINPUT_STATE State = { 0 };
	return (XInputGetState(ID, &State) == ERROR_SUCCESS);
}

bool BFW::Input::Controller::ValidID(const unsigned long _ID)
{
	XINPUT_STATE State = { 0 };
	return (XInputGetState(_ID, &State) == ERROR_SUCCESS);
}



#endif
