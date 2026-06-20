#include "../Headers/BFW.hpp"



BFW::Input::Key::Key() : State(), HoldTime()
{
	State[_PreviousState] = false;
	State[_CurrentState] = false;
}

BFW::Input::Key::Key(const Key& _Other) : State(), HoldTime(_Other.HoldTime)
{
	State[_PreviousState] = _Other.State[_PreviousState];
	State[_CurrentState] = _Other.State[_CurrentState];
}

BFW::Input::Key::Key(Key&& _Other) noexcept : State(), HoldTime((Time::Timer&&)(_Other.HoldTime))
{
	State[_PreviousState] = _Other.State[_PreviousState];
	State[_CurrentState] = _Other.State[_CurrentState];

	_Other.State[_PreviousState] = false;
	_Other.State[_CurrentState] = false;
}

BFW::Input::Key::~Key()
{

}

void BFW::Input::Key::UpdateState(const bool _NewState)
{
	State[_PreviousState] = State[_CurrentState];
	State[_CurrentState] = _NewState;

	if (JustPressed())
	{
		HoldTime.Start();
	}

	if (WasPressed() && IsPressed())
	{
		HoldTime.Stop();
	}

	if (JustReleased())
	{
		HoldTime.Reset();
	}
}

void BFW::Input::Key::CleanState()
{
	State[_PreviousState] = false;
	State[_CurrentState] = false;
	HoldTime.Reset();
}

const bool BFW::Input::Key::IsPressed() const
{
	return State[_CurrentState];
}

const bool BFW::Input::Key::WasPressed() const
{
	return State[_PreviousState];
}

const bool BFW::Input::Key::JustPressed() const
{
	return !State[_PreviousState] && State[_CurrentState];
}

const bool BFW::Input::Key::JustReleased() const
{
	return State[_PreviousState] && !State[_CurrentState];
}

const float BFW::Input::Key::GetHoldTime() const
{
	return HoldTime;
}

BFW::Input::Key& BFW::Input::Key::operator= (const Key& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	State[_PreviousState] = _Other.State[_PreviousState];
	State[_CurrentState] = _Other.State[_CurrentState];
	HoldTime = _Other.HoldTime;

	return *this;
}

BFW::Input::Key& BFW::Input::Key::operator= (Key&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	State[_PreviousState] = _Other.State[_PreviousState];
	State[_CurrentState] = _Other.State[_CurrentState];
	HoldTime = (Time::Timer&&)(_Other.HoldTime);

	_Other.State[_PreviousState] = false;
	_Other.State[_CurrentState] = false;

	return *this;
}



#if defined BFW_WINDOWS_PLATFORM || defined BFW_LINUX_PLATFORM

BFW::Input::ClickEvent::ClickEvent() : X(0), Y(0), Control(false), Shift(false)
{

}

BFW::Input::ClickEvent::ClickEvent(const intptr_t _X, const intptr_t _Y, const bool _Control, const bool _Shift) : X(_X), Y(_Y), Control(_Control), Shift(_Shift)
{

}

BFW::Input::ClickEvent::ClickEvent(ClickEvent&& _Other) noexcept : X(_Other.X), Y(_Other.Y), Control(_Other.Control), Shift(_Other.Shift)
{
	_Other.X = 0;
	_Other.Y = 0;
	_Other.Control = false;
	_Other.Shift = false;
}

BFW::Input::ClickEvent& BFW::Input::ClickEvent::operator= (ClickEvent&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	X = _Other.X;
	Y = _Other.Y;
	Control = _Other.Control;
	Shift = _Other.Shift;

	_Other.X = 0;
	_Other.Y = 0;
	_Other.Control = false;
	_Other.Shift = false;

	return *this;
}



BFW::Input::WheelEvent::WheelEvent() : Delta(0), X(0), Y(0), Control(false), Shift(false)
{

}

BFW::Input::WheelEvent::WheelEvent(const intptr_t _Delta, const intptr_t _X, const intptr_t _Y, const bool _Control, const bool _Shift) : Delta(_Delta), X(_X), Y(_Y), Control(_Control), Shift(_Shift)
{

}

BFW::Input::WheelEvent::WheelEvent(WheelEvent&& _Other) noexcept : Delta(_Other.Delta), X(_Other.X), Y(_Other.Y), Control(_Other.Control), Shift(_Other.Shift)
{
	_Other.Delta = 0;
	_Other.X = 0;
	_Other.Y = 0;
	_Other.Control = false;
	_Other.Shift = false;
}

BFW::Input::WheelEvent& BFW::Input::WheelEvent::operator= (WheelEvent&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Delta = _Other.Delta;
	X = _Other.X;
	Y = _Other.Y;
	Control = _Other.Control;
	Shift = _Other.Shift;

	_Other.Delta = 0;
	_Other.X = 0;
	_Other.Y = 0;
	_Other.Control = false;
	_Other.Shift = false;

	return *this;
}



#ifdef BFW_WINDOWS_PLATFORM

BFW::Input::Controller::Controller() : Connected(false), XLeft(0.0f), YLeft(0.0f), XRight(0.0f), YRight(0.0f), TriggerLeft(0.0f), TriggerRight(0.0f), Start(), Back(), ThumbLeft(), ThumbRight(), ButtonA(), ButtonB(), ButtonX(), ButtonY(), ButtonLeft(), ButtonRight(), ButtonUp(), ButtonDown(), ShoulderLeft(), ShoulderRight()
{

}

BFW::Input::Controller::Controller(const Controller& _Other) : Connected(_Other.Connected), XLeft(_Other.XLeft), YLeft(_Other.YLeft), XRight(_Other.XRight), YRight(_Other.YRight), TriggerLeft(_Other.TriggerLeft), TriggerRight(_Other.TriggerRight), Start(_Other.Start), Back(_Other.Back), ThumbLeft(_Other.ThumbLeft), ThumbRight(_Other.ThumbRight), ButtonA(_Other.ButtonA), ButtonB(_Other.ButtonB), ButtonX(_Other.ButtonX), ButtonY(_Other.ButtonY), ButtonLeft(_Other.ButtonLeft), ButtonRight(_Other.ButtonRight), ButtonUp(_Other.ButtonUp), ButtonDown(_Other.ButtonDown), ShoulderLeft(_Other.ShoulderLeft), ShoulderRight(_Other.ShoulderRight)
{

}

BFW::Input::Controller::Controller(Controller&& _Other) noexcept : Connected(_Other.Connected), XLeft(_Other.XLeft), YLeft(_Other.YLeft), XRight(_Other.XRight), YRight(_Other.YRight), TriggerLeft(_Other.TriggerLeft), TriggerRight(_Other.TriggerRight), Start((Key&&)(_Other.Start)), Back((Key&&)(_Other.Back)), ThumbLeft((Key&&)(_Other.ThumbLeft)), ThumbRight((Key&&)(_Other.ThumbRight)), ButtonA((Key&&)(_Other.ButtonA)), ButtonB((Key&&)(_Other.ButtonB)), ButtonX((Key&&)(_Other.ButtonX)), ButtonY((Key&&)(_Other.ButtonY)), ButtonLeft((Key&&)(_Other.ButtonLeft)), ButtonRight((Key&&)(_Other.ButtonRight)), ButtonUp((Key&&)(_Other.ButtonUp)), ButtonDown((Key&&)(_Other.ButtonDown)), ShoulderLeft((Key&&)(_Other.ShoulderLeft)), ShoulderRight((Key&&)(_Other.ShoulderRight))
{
	_Other.Connected = false;
	_Other.XLeft = 0.0f;
	_Other.YLeft = 0.0f;
	_Other.XRight = 0.0f;
	_Other.YRight = 0.0f;
	_Other.TriggerLeft = 0.0f;
	_Other.TriggerRight = 0.0f;
}

BFW::Input::Controller::~Controller()
{

}

#endif

#ifdef BFW_LINUX_PLATFORM

BFW::Input::Controller::Controller() : Connected(false), XLeft(0.0f), YLeft(0.0f), XRight(0.0f), YRight(0.0f), TriggerLeft(0.0f), TriggerRight(0.0f), Start(), Back(), ThumbLeft(), ThumbRight(), ButtonA(), ButtonB(), ButtonX(), ButtonY(), ButtonLeft(), ButtonRight(), ButtonUp(), ButtonDown(), ShoulderLeft(), ShoulderRight(), File(-1)
{

}

BFW::Input::Controller::Controller(const Controller& _Other) : Connected(_Other.Connected), XLeft(_Other.XLeft), YLeft(_Other.YLeft), XRight(_Other.XRight), YRight(_Other.YRight), TriggerLeft(_Other.TriggerLeft), TriggerRight(_Other.TriggerRight), Start(_Other.Start), Back(_Other.Back), ThumbLeft(_Other.ThumbLeft), ThumbRight(_Other.ThumbRight), ButtonA(_Other.ButtonA), ButtonB(_Other.ButtonB), ButtonX(_Other.ButtonX), ButtonY(_Other.ButtonY), ButtonLeft(_Other.ButtonLeft), ButtonRight(_Other.ButtonRight), ButtonUp(_Other.ButtonUp), ButtonDown(_Other.ButtonDown), ShoulderLeft(_Other.ShoulderLeft), ShoulderRight(_Other.ShoulderRight), File(-1)
{

}

BFW::Input::Controller::Controller(Controller&& _Other) noexcept : Connected(_Other.Connected), XLeft(_Other.XLeft), YLeft(_Other.YLeft), XRight(_Other.XRight), YRight(_Other.YRight), TriggerLeft(_Other.TriggerLeft), TriggerRight(_Other.TriggerRight), Start((Key&&)(_Other.Start)), Back((Key&&)(_Other.Back)), ThumbLeft((Key&&)(_Other.ThumbLeft)), ThumbRight((Key&&)(_Other.ThumbRight)), ButtonA((Key&&)(_Other.ButtonA)), ButtonB((Key&&)(_Other.ButtonB)), ButtonX((Key&&)(_Other.ButtonX)), ButtonY((Key&&)(_Other.ButtonY)), ButtonLeft((Key&&)(_Other.ButtonLeft)), ButtonRight((Key&&)(_Other.ButtonRight)), ButtonUp((Key&&)(_Other.ButtonUp)), ButtonDown((Key&&)(_Other.ButtonDown)), ShoulderLeft((Key&&)(_Other.ShoulderLeft)), ShoulderRight((Key&&)(_Other.ShoulderRight)), File(_Other.File)
{
	_Other.Connected = false;
	_Other.XLeft = 0.0f;
	_Other.YLeft = 0.0f;
	_Other.XRight = 0.0f;
	_Other.YRight = 0.0f;
	_Other.TriggerLeft = 0.0f;
	_Other.TriggerRight = 0.0f;
	_Other.File = -1;
}

BFW::Input::Controller::~Controller()
{
	if (File != -1)
	{
		close(File);
	}
}

#endif

#ifdef BFW_WINDOWS_PLATFORM

void BFW::Input::Controller::UpdateState(const uint8_t _ControllerIndex, const bool _DeadZone, const bool _Threshold)
{
	if (_ControllerIndex > 3)
	{
		BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Controllers range from 0 to 3!"));
		Connected = false;
		CleanState();
		return;
	}

	Connected = true;

	XINPUT_STATE _XInputState = { 0 };

	if (XInputGetState(_ControllerIndex, &_XInputState) != ERROR_SUCCESS)
	{
		Connected = false;
		CleanState();
		return;
	}

	XLeft = BFW::Math::Clamp((float)(_XInputState.Gamepad.sThumbLX), -32767.0f, 32767.0f) / 32767.0f;
	YLeft = BFW::Math::Clamp((float)(_XInputState.Gamepad.sThumbLY), -32767.0f, 32767.0f) / 32767.0f;
	XRight = BFW::Math::Clamp((float)(_XInputState.Gamepad.sThumbRX), -32767.0f, 32767.0f) / 32767.0f;
	YRight = BFW::Math::Clamp((float)(_XInputState.Gamepad.sThumbRY), -32767.0f, 32767.0f) / 32767.0f;
	TriggerLeft = (float)(_XInputState.Gamepad.bLeftTrigger) / 255.0f;
	TriggerRight = (float)(_XInputState.Gamepad.bRightTrigger) / 255.0f;
	Start.UpdateState((_XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_START) != 0);
	Back.UpdateState((_XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) != 0);
	ThumbLeft.UpdateState((_XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) != 0);
	ThumbRight.UpdateState((_XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) != 0);
	ButtonA.UpdateState((_XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0);
	ButtonB.UpdateState((_XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0);
	ButtonX.UpdateState((_XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0);
	ButtonY.UpdateState((_XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0);
	ButtonLeft.UpdateState((_XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0);
	ButtonRight.UpdateState((_XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0);
	ButtonUp.UpdateState((_XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0);
	ButtonDown.UpdateState((_XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0);
	ShoulderLeft.UpdateState((_XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0);
	ShoulderRight.UpdateState((_XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0);

	if (_DeadZone)
	{
		if (-XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE < _XInputState.Gamepad.sThumbLX && _XInputState.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			XLeft = 0.0f;
		}

		if (-XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE < _XInputState.Gamepad.sThumbLY && _XInputState.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			YLeft = 0.0f;
		}

		if (-XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE < _XInputState.Gamepad.sThumbRX && _XInputState.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		{
			XRight = 0.0f;
		}

		if (-XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE < _XInputState.Gamepad.sThumbRY && _XInputState.Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		{
			YRight = 0.0f;
		}
	}

	if (_Threshold)
	{
		if (_XInputState.Gamepad.bLeftTrigger < XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			TriggerLeft = 0.0f;
		}

		if (_XInputState.Gamepad.bRightTrigger < XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			TriggerRight = 0.0f;
		}
	}
}

#endif

#ifdef BFW_LINUX_PLATFORM

void BFW::Input::Controller::UpdateState(const uint8_t _ControllerIndex, const bool _DeadZone, const bool _Threshold)
{
	if (_ControllerIndex > 3)
	{
		BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Controllers range from 0 to 3!"));
		Connected = false;
		CleanState();
		return;
	}

	Connected = true;

	if (File == -1)
	{
		File = open((BFW_STRING_TYPE(BFW_STRING_PREFIX("/dev/input/js")) + BFW_TO_STRING(_ControllerIndex)).c_str(), O_RDONLY | O_NONBLOCK);
	}

	if (File < 0)
	{
		Connected = false;
		CleanState();
		return;
	}

	js_event _Event = { 0 };

	while (true)
	{
		int64_t _Size = read(File, &_Event, sizeof(js_event));

		if (_Size == 0)
		{
			break;
		}

		if (_Size == -1 || _Size != sizeof(js_event))
		{
			if (errno == EAGAIN)
			{
				break;
			}

			close(File);
			File = -1;
			Connected = false;
			CleanState();
			break;
		}

		switch (_Event.type & ~JS_EVENT_INIT)
		{
		case JS_EVENT_AXIS:
		{
			switch (_Event.number)
			{
			case 0:
			{
				XLeft = BFW::Math::Clamp((float)(_Event.value), -32767.0f, 32767.0f) / 32767.0f;
				break;
			}
			case 1:
			{
				YLeft = -BFW::Math::Clamp((float)(_Event.value), -32767.0f, 32767.0f) / 32767.0f;
				break;
			}
			case 3:
			{
				XRight = BFW::Math::Clamp((float)(_Event.value), -32767.0f, 32767.0f) / 32767.0f;
				break;
			}
			case 4:
			{
				YRight = -BFW::Math::Clamp((float)(_Event.value), -32767.0f, 32767.0f) / 32767.0f;
				break;
			}
			case 2:
			{
				TriggerLeft = BFW::Math::Clamp((float)(_Event.value), -32767.0f, 32767.0f) / 32767.0f;
				break;
			}
			case 5:
			{
				TriggerRight = BFW::Math::Clamp((float)(_Event.value), -32767.0f, 32767.0f) / 32767.0f;
				break;
			}
			default:
			{
				break;
			}
			}
			break;
		}
		case JS_EVENT_BUTTON:
		{
			switch (_Event.number)
			{
			case 9:
			{
				Start.UpdateState(_Event.value != 0);
				break;
			}
			case 8:
			{
				Back.UpdateState(_Event.value != 0);
				break;
			}
			case 11:
			{
				ThumbLeft.UpdateState(_Event.value != 0);
				break;
			}
			case 12:
			{
				ThumbRight.UpdateState(_Event.value != 0);
				break;
			}
			case 0:
			{
				ButtonA.UpdateState(_Event.value != 0);
				break;
			}
			case 1:
			{
				ButtonB.UpdateState(_Event.value != 0);
				break;
			}
			case 3:
			{
				ButtonX.UpdateState(_Event.value != 0);
				break;
			}
			case 2:
			{
				ButtonY.UpdateState(_Event.value != 0);
				break;
			}
			case 13:
			{
				ButtonUp.UpdateState(_Event.value != 0);
				break;
			}
			case 14:
			{
				ButtonDown.UpdateState(_Event.value != 0);
				break;
			}
			case 15:
			{
				ButtonLeft.UpdateState(_Event.value != 0);
				break;
			}
			case 16:
			{
				ButtonRight.UpdateState(_Event.value != 0);
				break;
			}
			case 4:
			{
				ShoulderLeft.UpdateState(_Event.value != 0);
				break;
			}
			case 5:
			{
				ShoulderRight.UpdateState(_Event.value != 0);
				break;
			}
			default:
			{
				break;
			}
			}
			break;
		}
		default:
		{
			break;
		}
		}
	}

	if (_DeadZone)
	{
		if (-0.05f < XLeft && XLeft < 0.05f)
		{
			XLeft = 0.0f;
		}

		if (-0.05f < YLeft && YLeft < 0.05f)
		{
			YLeft = 0.0f;
		}

		if (-0.05f < XRight && XRight < 0.05f)
		{
			XRight = 0.0f;
		}

		if (-0.05f < YRight && YRight < 0.05f)
		{
			YRight = 0.0f;
		}
	}

	if (_Threshold)
	{
		if (TriggerLeft < 0.05f)
		{
			TriggerLeft = 0.0f;
		}

		if (TriggerRight < 0.05f)
		{
			TriggerRight = 0.0f;
		}
	}
}

#endif

void BFW::Input::Controller::CleanState()
{
	XLeft = 0.0f;
	YLeft = 0.0f;
	XRight = 0.0f;
	YRight = 0.0f;
	TriggerLeft = 0.0f;
	TriggerRight = 0.0f;
	Start.CleanState();
	Back.CleanState();
	ThumbLeft.CleanState();
	ThumbRight.CleanState();
	ButtonA.CleanState();
	ButtonB.CleanState();
	ButtonX.CleanState();
	ButtonY.CleanState();
	ButtonLeft.CleanState();
	ButtonRight.CleanState();
	ButtonUp.CleanState();
	ButtonDown.CleanState();
	ShoulderLeft.CleanState();
	ShoulderRight.CleanState();
}

const bool BFW::Input::Controller::CheckConnected() const
{
	return Connected;
}

const float BFW::Input::Controller::GetXLeft() const
{
	return XLeft;
}

const float BFW::Input::Controller::GetYLeft() const
{
	return YLeft;
}

const float BFW::Input::Controller::GetXRight() const
{
	return XRight;
}

const float BFW::Input::Controller::GetYRight() const
{
	return YRight;
}

const float BFW::Input::Controller::GetTriggerLeft() const
{
	return TriggerLeft;
}

const float BFW::Input::Controller::GetTriggerRight() const
{
	return TriggerRight;
}

const BFW::Input::Key& BFW::Input::Controller::GetStart() const
{
	return Start;
}

const BFW::Input::Key& BFW::Input::Controller::GetBack() const
{
	return Back;
}

const BFW::Input::Key& BFW::Input::Controller::GetThumbLeft() const
{
	return ThumbLeft;
}

const BFW::Input::Key& BFW::Input::Controller::GetThumbRight() const
{
	return ThumbRight;
}

const BFW::Input::Key& BFW::Input::Controller::GetButtonA() const
{
	return ButtonA;
}

const BFW::Input::Key& BFW::Input::Controller::GetButtonB() const
{
	return ButtonB;
}

const BFW::Input::Key& BFW::Input::Controller::GetButtonX() const
{
	return ButtonX;
}

const BFW::Input::Key& BFW::Input::Controller::GetButtonY() const
{
	return ButtonY;
}

const BFW::Input::Key& BFW::Input::Controller::GetButtonLeft() const
{
	return ButtonLeft;
}

const BFW::Input::Key& BFW::Input::Controller::GetButtonRight() const
{
	return ButtonRight;
}

const BFW::Input::Key& BFW::Input::Controller::GetButtonUp() const
{
	return ButtonUp;
}

const BFW::Input::Key& BFW::Input::Controller::GetButtonDown() const
{
	return ButtonDown;
}

const BFW::Input::Key& BFW::Input::Controller::GetShoulderLeft() const
{
	return ShoulderLeft;
}

const BFW::Input::Key& BFW::Input::Controller::GetShoulderRight() const
{
	return ShoulderRight;
}

#ifdef BFW_WINDOWS_PLATFORM

BFW::Input::Controller& BFW::Input::Controller::operator= (const Controller& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	Connected = _Other.Connected;
	XLeft = _Other.XLeft;
	YLeft = _Other.YLeft;
	XRight = _Other.XRight;
	YRight = _Other.YRight;
	TriggerLeft = _Other.TriggerLeft;
	TriggerRight = _Other.TriggerRight;
	Start = _Other.Start;
	Back = _Other.Back;
	ThumbLeft = _Other.ThumbLeft;
	ThumbRight = _Other.ThumbRight;
	ButtonA = _Other.ButtonA;
	ButtonB = _Other.ButtonB;
	ButtonX = _Other.ButtonX;
	ButtonY = _Other.ButtonY;
	ButtonLeft = _Other.ButtonLeft;
	ButtonRight = _Other.ButtonRight;
	ButtonUp = _Other.ButtonUp;
	ButtonDown = _Other.ButtonDown;
	ShoulderLeft = _Other.ShoulderLeft;
	ShoulderRight = _Other.ShoulderRight;

	return *this;
}

BFW::Input::Controller& BFW::Input::Controller::operator= (Controller&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Connected = _Other.Connected;
	XLeft = _Other.XLeft;
	YLeft = _Other.YLeft;
	XRight = _Other.XRight;
	YRight = _Other.YRight;
	TriggerLeft = _Other.TriggerLeft;
	TriggerRight = _Other.TriggerRight;
	Start = (Key&&)(_Other.Start);
	Back = (Key&&)(_Other.Back);
	ThumbLeft = (Key&&)(_Other.ThumbLeft);
	ThumbRight = (Key&&)(_Other.ThumbRight);
	ButtonA = (Key&&)(_Other.ButtonA);
	ButtonB = (Key&&)(_Other.ButtonB);
	ButtonX = (Key&&)(_Other.ButtonX);
	ButtonY = (Key&&)(_Other.ButtonY);
	ButtonLeft = (Key&&)(_Other.ButtonLeft);
	ButtonRight = (Key&&)(_Other.ButtonRight);
	ButtonUp = (Key&&)(_Other.ButtonUp);
	ButtonDown = (Key&&)(_Other.ButtonDown);
	ShoulderLeft = (Key&&)(_Other.ShoulderLeft);
	ShoulderRight = (Key&&)(_Other.ShoulderRight);

	_Other.Connected = false;
	_Other.XLeft = 0.0f;
	_Other.YLeft = 0.0f;
	_Other.XRight = 0.0f;
	_Other.YRight = 0.0f;
	_Other.TriggerLeft = 0.0f;
	_Other.TriggerRight = 0.0f;

	return *this;
}

#endif

#ifdef BFW_LINUX_PLATFORM

BFW::Input::Controller& BFW::Input::Controller::operator= (const Controller& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	if (File != -1)
	{
		close(File);
	}

	Connected = _Other.Connected;
	XLeft = _Other.XLeft;
	YLeft = _Other.YLeft;
	XRight = _Other.XRight;
	YRight = _Other.YRight;
	TriggerLeft = _Other.TriggerLeft;
	TriggerRight = _Other.TriggerRight;
	Start = _Other.Start;
	Back = _Other.Back;
	ThumbLeft = _Other.ThumbLeft;
	ThumbRight = _Other.ThumbRight;
	ButtonA = _Other.ButtonA;
	ButtonB = _Other.ButtonB;
	ButtonX = _Other.ButtonX;
	ButtonY = _Other.ButtonY;
	ButtonLeft = _Other.ButtonLeft;
	ButtonRight = _Other.ButtonRight;
	ButtonUp = _Other.ButtonUp;
	ButtonDown = _Other.ButtonDown;
	ShoulderLeft = _Other.ShoulderLeft;
	ShoulderRight = _Other.ShoulderRight;
	File = -1;

	return *this;
}

BFW::Input::Controller& BFW::Input::Controller::operator= (Controller&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	if (File != -1)
	{
		close(File);
	}

	Connected = _Other.Connected;
	XLeft = _Other.XLeft;
	YLeft = _Other.YLeft;
	XRight = _Other.XRight;
	YRight = _Other.YRight;
	TriggerLeft = _Other.TriggerLeft;
	TriggerRight = _Other.TriggerRight;
	Start = (Key&&)(_Other.Start);
	Back = (Key&&)(_Other.Back);
	ThumbLeft = (Key&&)(_Other.ThumbLeft);
	ThumbRight = (Key&&)(_Other.ThumbRight);
	ButtonA = (Key&&)(_Other.ButtonA);
	ButtonB = (Key&&)(_Other.ButtonB);
	ButtonX = (Key&&)(_Other.ButtonX);
	ButtonY = (Key&&)(_Other.ButtonY);
	ButtonLeft = (Key&&)(_Other.ButtonLeft);
	ButtonRight = (Key&&)(_Other.ButtonRight);
	ButtonUp = (Key&&)(_Other.ButtonUp);
	ButtonDown = (Key&&)(_Other.ButtonDown);
	ShoulderLeft = (Key&&)(_Other.ShoulderLeft);
	ShoulderRight = (Key&&)(_Other.ShoulderRight);
	File = _Other.File;

	_Other.Connected = false;
	_Other.XLeft = 0.0f;
	_Other.YLeft = 0.0f;
	_Other.XRight = 0.0f;
	_Other.YRight = 0.0f;
	_Other.TriggerLeft = 0.0f;
	_Other.TriggerRight = 0.0f;
	_Other.File = -1;

	return *this;
}

#endif

#ifdef BFW_WINDOWS_PLATFORM

const bool BFW::Input::Controller::SetRumble(const uint8_t _ControllerIndex, const float _RumbleLeft, const float _RumbleRight)
{
	if (_ControllerIndex > 3)
	{
		BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Controllers range from 0 to 3!"));
		return false;
	}

	XINPUT_VIBRATION _Vibration = { 0 };

	_Vibration.wLeftMotorSpeed = (uint16_t)(Math::Clamp(_RumbleLeft, 0.0f, 1.0f) * 65535.0f);
	_Vibration.wRightMotorSpeed = (uint16_t)(Math::Clamp(_RumbleRight, 0.0f, 1.0f) * 65535.0f);

	if (XInputSetState(_ControllerIndex, &_Vibration) != ERROR_SUCCESS)
	{
		return false;
	}

	return true;
}

#endif

#endif
