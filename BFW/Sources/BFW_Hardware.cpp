#include "..\Headers\BFW.hpp"



#ifdef BFW_WINDOWS_PLATFORM



BFW::Hardware::SerialPort::SerialPort() : FileHandle(NULL), Status({ 0 }), PortName(nullptr), Connected(false), BaudRate(0)
{

}

BFW::Hardware::SerialPort::SerialPort(SerialPort&& _Other) noexcept :
	FileHandle(_Other.FileHandle), Status(_Other.Status), PortName(_Other.PortName), Connected(_Other.Connected), BaudRate(_Other.BaudRate)
{
	_Other.FileHandle = NULL;
	_Other.Status = { 0 };
	_Other.PortName = nullptr;
	_Other.Connected = false;
	_Other.BaudRate = 0;
}

BFW::Hardware::SerialPort::~SerialPort()
{
	if (Connected)
	{
		Close();
	}
}

bool BFW::Hardware::SerialPort::Open(const wchar_t* _PortName, const unsigned long _BaudRate)
{
	Close();

	if (!_PortName || !_BaudRate)
	{
		BFW_DEBUG_BREAK_MSG(L"Invalid parameters!");
		return false;
	}

	PortName = _PortName;
	BaudRate = _BaudRate;

	FileHandle = CreateFile(PortName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (FileHandle == INVALID_HANDLE_VALUE || FileHandle == NULL)
	{
		Connected = false;
		Status = { 0 };
		return false;
	}

	DCB dcbSerialParameters = { 0 };

	if (!GetCommState(FileHandle, &dcbSerialParameters))
	{
		CloseHandle(FileHandle);
		FileHandle = NULL;
		Connected = false;
		Status = { 0 };
		return false;
	}

	dcbSerialParameters.BaudRate = BaudRate;
	dcbSerialParameters.ByteSize = 8;
	dcbSerialParameters.StopBits = ONESTOPBIT;
	dcbSerialParameters.Parity = NOPARITY;
	dcbSerialParameters.fDtrControl = DTR_CONTROL_ENABLE;

	if (!SetCommState(FileHandle, &dcbSerialParameters))
	{
		CloseHandle(FileHandle);
		FileHandle = NULL;
		Connected = false;
		Status = { 0 };
		return false;
	}

	Connected = true;

	return true;
}

bool BFW::Hardware::SerialPort::Update()
{
	if (Connected)
	{
		unsigned long _Error;

		if (!ClearCommError(FileHandle, &_Error, &Status))
		{
			if (FileHandle != NULL && FileHandle != INVALID_HANDLE_VALUE)
			{
				CloseHandle(FileHandle);
				FileHandle = NULL;
			}
			Connected = false;
			Status = { 0 };

			return false;
		}

		return true;
	}

	if (FileHandle != NULL && FileHandle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(FileHandle);
		FileHandle = NULL;
	}
	Connected = false;
	Status = { 0 };

	return Open(PortName, BaudRate);
}

void BFW::Hardware::SerialPort::Close()
{
	if (FileHandle != NULL && FileHandle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(FileHandle);
		FileHandle = NULL;
	}
	Connected = false;
	Status = { 0 };
	PortName = nullptr;
	BaudRate = 0;
}

unsigned long BFW::Hardware::SerialPort::Read(char* _Buff, const unsigned long _Size)
{
	if (!Connected)
	{
		return 0;
	}

	unsigned long _Error = 0;

	if (!ClearCommError(FileHandle, &_Error, &Status))
	{
		if (FileHandle != NULL && FileHandle != INVALID_HANDLE_VALUE)
		{
			CloseHandle(FileHandle);
			FileHandle = NULL;
		}
		Connected = false;
		Status = { 0 };

		return 0;
	}

	unsigned long _BytesRead = 0;

	if (!ReadFile(FileHandle, _Buff, _Size * (Status.cbInQue > _Size) + Status.cbInQue * (Status.cbInQue <= _Size), &_BytesRead, NULL))
	{
		if (!ClearCommError(FileHandle, &_Error, &Status))
		{
			if (FileHandle != NULL && FileHandle != INVALID_HANDLE_VALUE)
			{
				CloseHandle(FileHandle);
				FileHandle = NULL;
			}
			Connected = false;
			Status = { 0 };
		}
		return 0;
	}

	return _BytesRead;
}

unsigned long BFW::Hardware::SerialPort::Write(const unsigned char* _Buff, const unsigned long _Size)
{
	if (!Connected)
	{
		return 0;
	}

	unsigned long _Error = 0;

	if (!ClearCommError(FileHandle, &_Error, &Status))
	{
		if (FileHandle != NULL && FileHandle != INVALID_HANDLE_VALUE)
		{
			CloseHandle(FileHandle);
			FileHandle = NULL;
		}
		Connected = false;
		Status = { 0 };

		return 0;
	}

	unsigned long _BytesSent = 0;

	if (!WriteFile(FileHandle, _Buff, _Size, &_BytesSent, 0))
	{
		if (!ClearCommError(FileHandle, &_Error, &Status))
		{
			if (FileHandle != NULL && FileHandle != INVALID_HANDLE_VALUE)
			{
				CloseHandle(FileHandle);
				FileHandle = NULL;
			}
			Connected = false;
			Status = { 0 };
		}
		return 0;
	}

	return _BytesSent;
}

const bool BFW::Hardware::SerialPort::CheckConnected() const
{
	return Connected;
}

const wchar_t* BFW::Hardware::SerialPort::GetPortName() const
{
	return PortName;
}

const unsigned long BFW::Hardware::SerialPort::GetBaudRate() const
{
	return BaudRate;
}

void BFW::Hardware::SerialPort::operator= (SerialPort&& _Other) noexcept
{
	FileHandle = _Other.FileHandle;
	Status = _Other.Status;
	PortName = _Other.PortName;
	Connected = _Other.Connected;
	BaudRate = _Other.BaudRate;

	_Other.FileHandle = NULL;
	_Other.Status = { 0 };
	_Other.PortName = nullptr;
	_Other.Connected = false;
	_Other.BaudRate = 0;
}



#endif



#ifdef BFW_ARDUINO_PLATFORM



BFW::Hardware::DigitalInputPullupPin::DigitalInputPullupPin() : Number((unsigned long)(-1)), HoldTimer(), State()
{
	State[Enums::_Previous] = false;
	State[Enums::_Current] = false;
}

BFW::Hardware::DigitalInputPullupPin::DigitalInputPullupPin(DigitalInputPullupPin&& _Other) noexcept :
	Number(_Other.Number), HoldTimer((Time::Timer&&)(_Other.Number)), State()
{
	State[Enums::_Previous] = _Other.State[Enums::_Previous];
	State[Enums::_Current] = _Other.State[Enums::_Previous];

	_Other.Number = (unsigned long)(-1);
	_Other.State[Enums::_Previous] = false;
	_Other.State[Enums::_Current] = false;
}

BFW::Hardware::DigitalInputPullupPin::~DigitalInputPullupPin()
{

}

void BFW::Hardware::DigitalInputPullupPin::Update()
{
	State[Enums::_Previous] = State[Enums::_Current];
	State[Enums::_Current] = digitalRead(Number);

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

void BFW::Hardware::DigitalInputPullupPin::DeleteState()
{
	State[Enums::_Previous] = false;
	State[Enums::_Current] = false;
	HoldTimer.Reset();
}

void BFW::Hardware::DigitalInputPullupPin::Bind(const unsigned long _Number)
{
	Number = _Number;
	State[Enums::_Previous] = false;
	State[Enums::_Current] = false;
	HoldTimer.Reset();

	if (Number == (unsigned long)(-1))
	{
		return;
	}

	pinMode(Number, INPUT_PULLUP);
}

const unsigned long BFW::Hardware::DigitalInputPullupPin::GetNumber() const
{
	return Number;
}

const BFW::Time::Timer& BFW::Hardware::DigitalInputPullupPin::GetHoldTimer() const
{
	return HoldTimer;
}

const bool BFW::Hardware::DigitalInputPullupPin::operator[] (const unsigned long _Index) const
{
	return State[_Index];
}

void BFW::Hardware::DigitalInputPullupPin::operator= (DigitalInputPullupPin&& _Other) noexcept
{
	Number = _Other.Number;
	HoldTimer = (Time::Timer&&)(_Other.Number);
	State[Enums::_Previous] = _Other.State[Enums::_Previous];
	State[Enums::_Current] = _Other.State[Enums::_Previous];

	_Other.Number = (unsigned long)(-1);
	_Other.State[Enums::_Previous] = false;
	_Other.State[Enums::_Current] = false;
}



BFW::Hardware::DigitalInputPin::DigitalInputPin() : Number((unsigned long)(-1)), HoldTimer(), State()
{
	State[Enums::_Previous] = false;
	State[Enums::_Current] = false;
}

BFW::Hardware::DigitalInputPin::DigitalInputPin(DigitalInputPin&& _Other) noexcept :
	Number(_Other.Number), HoldTimer((Time::Timer&&)(_Other.Number)), State()
{
	State[Enums::_Previous] = _Other.State[Enums::_Previous];
	State[Enums::_Current] = _Other.State[Enums::_Previous];

	_Other.Number = (unsigned long)(-1);
	_Other.State[Enums::_Previous] = false;
	_Other.State[Enums::_Current] = false;
}

BFW::Hardware::DigitalInputPin::~DigitalInputPin()
{

}

void BFW::Hardware::DigitalInputPin::Update()
{
	State[Enums::_Previous] = State[Enums::_Current];
	State[Enums::_Current] = digitalRead(Number);

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

void BFW::Hardware::DigitalInputPin::DeleteState()
{
	State[Enums::_Previous] = false;
	State[Enums::_Current] = false;
	HoldTimer.Reset();
}

void BFW::Hardware::DigitalInputPin::Bind(const unsigned long _Number)
{
	Number = _Number;
	State[Enums::_Previous] = false;
	State[Enums::_Current] = false;
	HoldTimer.Reset();

	if (Number == (unsigned long)(-1))
	{
		return;
	}

	pinMode(Number, INPUT);
}

const unsigned long BFW::Hardware::DigitalInputPin::GetNumber() const
{
	return Number;
}

const BFW::Time::Timer& BFW::Hardware::DigitalInputPin::GetHoldTimer() const
{
	return HoldTimer;
}

const bool BFW::Hardware::DigitalInputPin::operator[] (const unsigned long _Index) const
{
	return State[_Index];
}

void BFW::Hardware::DigitalInputPin::operator= (DigitalInputPin&& _Other) noexcept
{
	Number = _Other.Number;
	HoldTimer = (Time::Timer&&)(_Other.Number);
	State[Enums::_Previous] = _Other.State[Enums::_Previous];
	State[Enums::_Current] = _Other.State[Enums::_Previous];

	_Other.Number = (unsigned long)(-1);
	_Other.State[Enums::_Previous] = false;
	_Other.State[Enums::_Current] = false;
}



BFW::Hardware::DigitalOutputPin::DigitalOutputPin() : Number((unsigned long)(-1)), HoldTimer(), State(false)
{

}

BFW::Hardware::DigitalOutputPin::DigitalOutputPin(DigitalOutputPin&& _Other) noexcept :
	Number(_Other.Number), HoldTimer((Time::Timer&&)(_Other.HoldTimer)), State(_Other.State)
{
	_Other.Number = (unsigned long)(-1);
	_Other.State = false;
}

BFW::Hardware::DigitalOutputPin::~DigitalOutputPin()
{

}

void BFW::Hardware::DigitalOutputPin::Write(const bool _State)
{
	if (Number == (unsigned long)(-1))
	{
		return;
	}
	digitalWrite(Number, _State);
	State = _State;
}

const bool BFW::Hardware::DigitalOutputPin::Read() const
{
	return digitalRead(Number);
}

void BFW::Hardware::DigitalOutputPin::Bind(const unsigned long _Number)
{
	Number = _Number;
	State = false;
	HoldTimer.Reset();

	if (Number == (unsigned long)(-1))
	{
		return;
	}

	pinMode(Number, OUTPUT);
}

const unsigned long BFW::Hardware::DigitalOutputPin::GetNumber() const
{
	return Number;
}

const BFW::Time::Timer& BFW::Hardware::DigitalOutputPin::GetHoldTimer() const
{
	return HoldTimer;
}

const bool BFW::Hardware::DigitalOutputPin::GetState() const
{
	return State;
}

void BFW::Hardware::DigitalOutputPin::operator= (DigitalOutputPin&& _Other) noexcept
{
	Number = _Other.Number;
	HoldTimer = (Time::Timer&&)(_Other.HoldTimer);
	State = _Other.State;

	_Other.Number = (unsigned long)(-1);
	_Other.State = false;
}



BFW::Hardware::AnalogInputPin::AnalogInputPin() : Number((unsigned long)(-1)), State()
{
	State[Enums::_Previous] = 0;
	State[Enums::_Current] = 0;
}

BFW::Hardware::AnalogInputPin::AnalogInputPin(AnalogInputPin&& _Other) noexcept : Number(_Other.Number), State()
{
	State[Enums::_Previous] = _Other.State[Enums::_Previous];
	State[Enums::_Current] = _Other.State[Enums::_Current];

	_Other.Number = (unsigned long)(-1);
	_Other.State[Enums::_Previous] = 0;
	_Other.State[Enums::_Current] = 0;
}

BFW::Hardware::AnalogInputPin::~AnalogInputPin()
{

}

void BFW::Hardware::AnalogInputPin::Update()
{
	State[Enums::_Previous] = State[Enums::_Current];
	State[Enums::_Current] = analogRead(Number);
}

void BFW::Hardware::AnalogInputPin::DeleteState()
{
	State[Enums::_Previous] = 0;
	State[Enums::_Current] = 0;
}

void BFW::Hardware::AnalogInputPin::Bind(const unsigned long _Number)
{
	Number = _Number;
	State[Enums::_Previous] = 0;
	State[Enums::_Current] = 0;
}

const unsigned long BFW::Hardware::AnalogInputPin::GetNumber() const
{
	return Number;
}

const unsigned long BFW::Hardware::AnalogInputPin::operator[] (const unsigned long _Index) const
{
	return State[_Index];
}

void BFW::Hardware::AnalogInputPin::operator= (AnalogInputPin&& _Other) noexcept
{
	Number = _Other.Number;
	State[Enums::_Previous] = _Other.State[Enums::_Previous];
	State[Enums::_Current] = _Other.State[Enums::_Current];

	_Other.Number = (unsigned long)(-1);
	_Other.State[Enums::_Previous] = 0;
	_Other.State[Enums::_Current] = 0;
}



BFW::Hardware::AnalogOutputPin::AnalogOutputPin() : Number((unsigned long)(-1)), HoldTimer(), State(0)
{

}

BFW::Hardware::AnalogOutputPin::AnalogOutputPin(AnalogOutputPin&& _Other) noexcept :
	Number(_Other.Number), HoldTimer((Time::Timer&&)(_Other.HoldTimer)), State(_Other.State)
{
	_Other.Number = (unsigned long)(-1);
	_Other.State = 0;
}

BFW::Hardware::AnalogOutputPin::~AnalogOutputPin()
{

}

void BFW::Hardware::AnalogOutputPin::Write(const unsigned char _State)
{
	if (Number == (unsigned long)(-1))
	{
		return;
	}
	analogWrite(Number, _State);
	State = _State;
}

void BFW::Hardware::AnalogOutputPin::Bind(const unsigned long _Number)
{
	Number = _Number;
	State = 0;
	HoldTimer.Reset();

	if (Number == (unsigned long)(-1))
	{
		return;
	}

	pinMode(Number, OUTPUT);
}

const unsigned long BFW::Hardware::AnalogOutputPin::GetNumber() const
{
	return Number;
}

const BFW::Time::Timer& BFW::Hardware::AnalogOutputPin::GetHoldTimer() const
{
	return HoldTimer;
}

const unsigned char BFW::Hardware::AnalogOutputPin::GetState() const
{
	return State;
}

void BFW::Hardware::AnalogOutputPin::operator= (AnalogOutputPin&& _Other) noexcept
{
	Number = _Other.Number;
	HoldTimer = (Time::Timer&&)(_Other.HoldTimer);
	State = _Other.State;

	_Other.Number = (unsigned long)(-1);
	_Other.State = 0;
}



#endif
