#include "..\Headers\BFW.hpp"



const float BFW_API BFW::Time::MicroToMilli = 0.001f;
const float BFW_API BFW::Time::MicroToSec = 0.000001f;

const float BFW_API BFW::Time::MilliToMicro = 1000.0f;
const float BFW_API BFW::Time::MilliToSec = 0.001f;

const float BFW_API BFW::Time::SecToMicro = 1000000.0f;
const float BFW_API BFW::Time::SecToMilli = 1000.0f;



float BFW_API BFW::Time::FramesPerMicroSec(const float _MicroSecPerFrame, bool* _Error)
{
	if (!_MicroSecPerFrame)
	{
		if (_Error)
		{
			*_Error = true;
		}
		return 0.0f;
	}
	if (_Error)
	{
		*_Error = false;
	}
	return 1.0f / _MicroSecPerFrame;
}

float BFW_API BFW::Time::FramesPerMilliSec(const float _MilliSecPerFrame, bool* _Error)
{
	if (!_MilliSecPerFrame)
	{
		if (_Error)
		{
			*_Error = true;
		}
		return 0.0f;
	}
	if (_Error)
	{
		*_Error = false;
	}
	return 1.0f / _MilliSecPerFrame;
}

float BFW_API BFW::Time::FramesPerSec(const float _SecPerFrame, bool* _Error)
{
	if (!_SecPerFrame)
	{
		if (_Error)
		{
			*_Error = true;
		}
		return 0.0f;
	}
	if (_Error)
	{
		*_Error = false;
	}
	return 1.0f / _SecPerFrame;
}



#ifdef BFW_WINDOWS_PLATFORM



BFW::Time::Timer::Timer(const long _MicroSec, const bool _Feature) : Begin(), End()
{
	SetMicroSec(_MicroSec, _Feature);
}

BFW::Time::Timer::Timer(const Timer& _Other) : Begin(_Other.Begin), End(_Other.End)
{

}

BFW::Time::Timer::Timer(Timer&& _Other) noexcept : Begin(_Other.Begin), End(_Other.End)
{
	_Other.Reset();
}

BFW::Time::Timer::~Timer()
{

}

void BFW::Time::Timer::Start()
{
	std::chrono::time_point<std::chrono::system_clock> _Now = std::chrono::system_clock::now();
	Begin = _Now;
	End = _Now;
}

void BFW::Time::Timer::Stop()
{
	End = std::chrono::system_clock::now();
}

void BFW::Time::Timer::Reset()
{
	std::chrono::time_point<std::chrono::system_clock> _Now = std::chrono::system_clock::now();
	Begin = _Now;
	End = _Now;
}

void BFW::Time::Timer::SetMicroSec(const long _MicroSec, const bool _Feature)
{
	std::chrono::time_point<std::chrono::system_clock> _Now = std::chrono::system_clock::now();
	Begin = _Now - std::chrono::microseconds(_MicroSec * (!_Feature));
	End = _Now + std::chrono::microseconds(_MicroSec * _Feature);
}

void BFW::Time::Timer::SetMilliSec(const long _MilliSec, const bool _Feature)
{
	std::chrono::time_point<std::chrono::system_clock> _Now = std::chrono::system_clock::now();
	Begin = _Now - std::chrono::milliseconds(_MilliSec * (!_Feature));
	End = _Now + std::chrono::milliseconds(_MilliSec * _Feature);
}

void BFW::Time::Timer::SetSec(const long _Sec, const bool _Feature)
{
	std::chrono::time_point<std::chrono::system_clock> _Now = std::chrono::system_clock::now();
	Begin = _Now - std::chrono::seconds(_Sec * (!_Feature));
	End = _Now + std::chrono::seconds(_Sec * _Feature);
}

void BFW::Time::Timer::AddMicroSec(const long _MicroSec, const bool _Feature)
{
	Begin -= std::chrono::microseconds(_MicroSec * (!_Feature));
	End += std::chrono::microseconds(_MicroSec * _Feature);
}

void BFW::Time::Timer::AddMilliSec(const long _MilliSec, const bool _Feature)
{
	Begin -= std::chrono::milliseconds(_MilliSec * (!_Feature));
	End += std::chrono::milliseconds(_MilliSec * _Feature);
}

void BFW::Time::Timer::AddSec(const long _Sec, const bool _Feature)
{
	Begin -= std::chrono::seconds(_Sec * (!_Feature));
	End += std::chrono::seconds(_Sec * _Feature);
}

const tm BFW::Time::Timer::GetUTCBegin() const
{
	tm _ReturnTm;
	time_t _Time = std::chrono::system_clock::to_time_t(Begin);
	gmtime_s(&_ReturnTm, &_Time);
	return _ReturnTm;
}

const tm BFW::Time::Timer::GetUTCEnd() const
{
	tm _ReturnTm;
	time_t _Time = std::chrono::system_clock::to_time_t(End);
	gmtime_s(&_ReturnTm, &_Time);
	return _ReturnTm;
}

const tm BFW::Time::Timer::GetLocalBegin() const
{
	tm _ReturnTm;
	time_t _Time = std::chrono::system_clock::to_time_t(Begin);
	localtime_s(&_ReturnTm, &_Time);
	return _ReturnTm;
}

const tm BFW::Time::Timer::GetLocalEnd() const
{
	tm _ReturnTm;
	time_t _Time = std::chrono::system_clock::to_time_t(End);
	localtime_s(&_ReturnTm, &_Time);
	return _ReturnTm;
}

BFW::Time::Timer::operator const float() const
{
	return std::chrono::duration<float>(End - Begin).count();
}

void BFW::Time::Timer::operator= (const Timer& _Other)
{
	Begin = _Other.Begin;
	End = _Other.End;
}

void BFW::Time::Timer::operator= (Timer&& _Other) noexcept
{
	Begin = _Other.Begin;
	End = _Other.End;

	_Other.Reset();
}



static tm _UtcTime = { 0 };
static tm _LocalTime = { 0 };

const BFW::Typedef::TimeRef BFW_API BFW::Time::UtcTime = _UtcTime;
const BFW::Typedef::TimeRef BFW_API BFW::Time::LocalTime = _LocalTime;

static bool _Initialized = false;
static TIMECAPS _TimeCaps = { 0 };

const BFW::Typedef::BoolRef BFW_API BFW::Time::Initialized = _Initialized;
const BFW::Typedef::TimeCapsRef BFW_API BFW::Time::TimeCaps = _TimeCaps;



bool BFW_API BFW::Time::Init()
{
	if (Initialized)
	{
		return true;
	}

	if (timeGetDevCaps(&_TimeCaps, sizeof(TIMECAPS)) != MMSYSERR_NOERROR)
	{
		return false;
	}

	if (timeBeginPeriod(_TimeCaps.wPeriodMin) != TIMERR_NOERROR)
	{
		_TimeCaps = { 0 };
		return false;
	}

	_Initialized = true;

	return true;
}

void BFW_API BFW::Time::Stop()
{
	if (!Initialized)
	{
		return;
	}

	if (timeEndPeriod(_TimeCaps.wPeriodMin) != TIMERR_NOERROR)
	{
		return;
	}

	_TimeCaps = { 0 };
	_Initialized = false;
}

void BFW_API BFW::Time::GetTime()
{
	time_t _Time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	gmtime_s(&_UtcTime, &_Time);
	localtime_s(&_LocalTime, &_Time);
}

void BFW_API BFW::Time::GetUtcTime()
{
	time_t _Time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	gmtime_s(&_UtcTime, &_Time);
}

void BFW_API BFW::Time::GetLocalTime()
{
	time_t _Time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	localtime_s(&_LocalTime, &_Time);
}

void BFW_API BFW::Time::SleepMicroSec(const unsigned long _MicroSec)
{
	std::this_thread::sleep_for(std::chrono::microseconds(_MicroSec));
}

void BFW_API BFW::Time::SleepMilliSec(const unsigned long _MilliSec)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(_MilliSec));
}

void BFW_API BFW::Time::SleepSec(const unsigned long _Sec)
{
	std::this_thread::sleep_for(std::chrono::seconds(_Sec));
}



#endif



#ifdef BFW_ARDUINO_PLATFORM



BFW::Time::Timer::Timer(const long _MicroSec, const bool _Feature) : Begin(), End()
{
	SetMicroSec(_MicroSec, _Feature);
}

BFW::Time::Timer::Timer(const Timer& _Other) : Begin(_Other.Begin), End(_Other.End)
{

}

BFW::Time::Timer::Timer(Timer&& _Other) noexcept : Begin(_Other.Begin), End(_Other.End)
{
	_Other.Reset();
}

BFW::Time::Timer::~Timer()
{

}

void BFW::Time::Timer::Start()
{
	unsigned long _Now = micros();
	Begin = _Now;
	End = _Now;
}

void BFW::Time::Timer::Stop()
{
	End = micros();
}

void BFW::Time::Timer::Reset()
{
	unsigned long _Now = micros();
	Begin = _Now;
	End = _Now;
}

void BFW::Time::Timer::SetMicroSec(const long _MicroSec, const bool _Feature)
{
	unsigned long _Now = micros();
	Begin = _Now - (_MicroSec * (!_Feature));
	End = _Now + (_MicroSec * _Feature);
}

void BFW::Time::Timer::SetMilliSec(const long _MilliSec, const bool _Feature)
{
	unsigned long _Now = micros();
	Begin = _Now - MilliToMicro * (_MilliSec * (!_Feature));
	End = _Now + MilliToMicro * (_MilliSec * _Feature);
}

void BFW::Time::Timer::SetSec(const long _Sec, const bool _Feature)
{
	unsigned long _Now = micros();
	Begin = _Now - SecToMicro * (_Sec * (!_Feature));
	End = _Now + SecToMicro * (_Sec * _Feature);
}

void BFW::Time::Timer::AddMicroSec(const long _MicroSec, const bool _Feature)
{
	Begin -= (_MicroSec * (!_Feature));
	End += (_MicroSec * _Feature);
}

void BFW::Time::Timer::AddMilliSec(const long _MilliSec, const bool _Feature)
{
	Begin -= MilliToMicro* (_MilliSec * (!_Feature));
	End += MilliToMicro * (_MilliSec * _Feature);
}

void BFW::Time::Timer::AddSec(const long _Sec, const bool _Feature)
{
	Begin -= SecToMicro * (_Sec * (!_Feature));
	End += SecToMicro * (_Sec * _Feature);
}

const unsigned long BFW::Time::Timer::GetBeginMicroSec() const
{
	return Begin;
}

const unsigned long BFW::Time::Timer::GetBeginMilliSec() const
{
	return Begin * MicroToMilli;
}

const unsigned long BFW::Time::Timer::GetBeginSec() const
{
	return Begin * MicroToSec;
}

const unsigned long BFW::Time::Timer::GetEndMicroSec() const
{
	return End;
}

const unsigned long BFW::Time::Timer::GetEndMilliSec() const
{
	return End * MicroToMilli;
}

const unsigned long BFW::Time::Timer::GetEndSec() const
{
	return End * MicroToSec;
}

BFW::Time::Timer::operator const float() const
{
	return (const float)((const float)(End - Begin) * MicroToSec);
}

void BFW::Time::Timer::operator= (const Timer& _Other)
{
	Begin = _Other.Begin;
	End = _Other.End;
}

void BFW::Time::Timer::operator= (Timer&& _Other) noexcept
{
	Begin = _Other.Begin;
	End = _Other.End;

	_Other.Reset();
}



void BFW_API BFW::Time::SleepMicroSec(const unsigned long _MicroSec)
{
	delay(_MicroSec * MicroToMilli);
	delayMicroseconds(_MicroSec - (_MicroSec * MicroToMilli) * MilliToMicro);
}

void BFW_API BFW::Time::SleepMilliSec(const unsigned long _MilliSec)
{
	delay(_MilliSec);
}

void BFW_API BFW::Time::SleepSec(const unsigned long _Sec)
{
	delay(_Sec * SecToMilli);
}



#endif
