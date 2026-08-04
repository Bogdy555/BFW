#include "../Headers/BFW.hpp"



static bool Initialized = false;

#ifdef BFW_WINDOWS_PLATFORM

static TIMECAPS TimeCaps = { 0 };

#endif



BFW::Time::Timer::Timer() : Begin(std::chrono::system_clock::now()), End(Begin)
{

}

BFW::Time::Timer::Timer(const Timer& _Other) : Begin(_Other.Begin), End(_Other.End)
{

}

BFW::Time::Timer::Timer(Timer&& _Other) noexcept : Begin(_Other.Begin), End(_Other.End)
{
	_Other.Begin = std::chrono::system_clock::now();
	_Other.End = _Other.Begin;
}

BFW::Time::Timer::~Timer()
{

}

void BFW::Time::Timer::Start()
{
	Begin = std::chrono::system_clock::now();
	End = Begin;
}

void BFW::Time::Timer::Stop()
{
	End = std::chrono::system_clock::now();
}

void BFW::Time::Timer::Reset()
{
	Begin = std::chrono::system_clock::now();
	End = Begin;
}

void BFW::Time::Timer::SetBeginFromEnd(const uint64_t _MicroSeconds)
{
	Begin = End - std::chrono::microseconds(_MicroSeconds);
}

void BFW::Time::Timer::SetEndFromBegin(const uint64_t _MicroSeconds)
{
	End = Begin + std::chrono::microseconds(_MicroSeconds);
}

void BFW::Time::Timer::AddMicroSecondsToBegin(const uint64_t _MicroSeconds)
{
	Begin += std::chrono::microseconds(_MicroSeconds);
}

void BFW::Time::Timer::AddMicroSecondsToEnd(const uint64_t _MicroSeconds)
{
	End += std::chrono::microseconds(_MicroSeconds);
}

void BFW::Time::Timer::SubtractMicroSecondsFromBegin(const uint64_t _MicroSeconds)
{
	Begin -= std::chrono::microseconds(_MicroSeconds);
}

void BFW::Time::Timer::SubtractMicroSecondsFromEnd(const uint64_t _MicroSeconds)
{
	End -= std::chrono::microseconds(_MicroSeconds);
}

const time_t BFW::Time::Timer::GetBegin() const
{
	return std::chrono::system_clock::to_time_t(Begin);
}

const time_t BFW::Time::Timer::GetEnd() const
{
	return std::chrono::system_clock::to_time_t(End);
}

BFW::Time::Timer::operator const float () const
{
	return std::chrono::duration<float>(End - Begin).count();
}

BFW::Time::Timer& BFW::Time::Timer::operator= (const Timer& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	Begin = _Other.Begin;
	End = _Other.End;

	return *this;
}

BFW::Time::Timer& BFW::Time::Timer::operator= (Timer&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Begin = _Other.Begin;
	End = _Other.End;

	_Other.Begin = std::chrono::system_clock::now();
	_Other.End = _Other.Begin;

	return *this;
}



BFW::Time::ScopeTimer::ScopeTimer(const LogScopeTimeFnc _LogFnc) : ScopeTime(), LogFnc(_LogFnc)
{

}

BFW::Time::ScopeTimer::ScopeTimer(const ScopeTimer& _Other) : ScopeTime(_Other.ScopeTime), LogFnc(_Other.LogFnc)
{

}

BFW::Time::ScopeTimer::ScopeTimer(ScopeTimer&& _Other) noexcept : ScopeTime((Timer&&)(_Other.ScopeTime)), LogFnc(_Other.LogFnc)
{
	_Other.LogFnc = nullptr;
}

BFW::Time::ScopeTimer::~ScopeTimer()
{
	ScopeTime.Stop();

	if (LogFnc)
	{
		LogFnc(ScopeTime);
	}
}

void BFW::Time::ScopeTimer::SetLogFnc(const LogScopeTimeFnc _LogFnc)
{
	LogFnc = _LogFnc;
}

const BFW::Time::LogScopeTimeFnc BFW::Time::ScopeTimer::GetLogFnc() const
{
	return LogFnc;
}

BFW::Time::ScopeTimer& BFW::Time::ScopeTimer::operator= (const ScopeTimer& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	ScopeTime = _Other.ScopeTime;
	LogFnc = _Other.LogFnc;

	return *this;
}

BFW::Time::ScopeTimer& BFW::Time::ScopeTimer::operator= (ScopeTimer&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	ScopeTime = (Timer&&)(_Other.ScopeTime);
	LogFnc = _Other.LogFnc;

	_Other.LogFnc = nullptr;

	return *this;
}



#ifdef BFW_WINDOWS_PLATFORM

const bool BFW_API BFW::Time::Init()
{
	if (Initialized)
	{
		return true;
	}

	if (timeGetDevCaps(&TimeCaps, sizeof(TIMECAPS)) != MMSYSERR_NOERROR)
	{
		return false;
	}

	if (timeBeginPeriod(TimeCaps.wPeriodMin) != TIMERR_NOERROR)
	{
		TimeCaps = { 0 };
		return false;
	}

	Initialized = true;

	return true;
}

void BFW_API BFW::Time::Stop()
{
	if (!Initialized)
	{
		return;
	}

	timeEndPeriod(TimeCaps.wPeriodMin);

	Initialized = false;
	TimeCaps = { 0 };
}

#endif

#if defined BFW_LINUX_PLATFORM || defined BFW_ESP32_PLATFORM

const bool BFW_API BFW::Time::Init()
{
	if (Initialized)
	{
		return true;
	}

	Initialized = true;

	return true;
}

void BFW_API BFW::Time::Stop()
{
	if (!Initialized)
	{
		return;
	}

	Initialized = false;
}

#endif

void BFW_API BFW::Time::Sleep(const uint64_t _MicroSeconds)
{
	std::this_thread::sleep_for(std::chrono::microseconds(_MicroSeconds));
}

const uint64_t BFW_API BFW::Time::GetTimeStamp()
{
	return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
}

const time_t BFW_API BFW::Time::GetTime()
{
	return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
}

const tm BFW_API BFW::Time::TimeTToUTCTM(const time_t _Time)
{
	tm _ReturnTm = { 0 };

	BFW_WINDOWS_PLATFORM_CALL(gmtime_s(&_ReturnTm, &_Time));
	BFW_LINUX_PLATFORM_CALL(gmtime_r(&_Time, &_ReturnTm));
	BFW_ESP32_PLATFORM_CALL(gmtime_r(&_Time, &_ReturnTm));

	return _ReturnTm;
}

const tm BFW_API BFW::Time::TimeTToLocalTM(const time_t _Time)
{
	tm _ReturnTm = { 0 };

	BFW_WINDOWS_PLATFORM_CALL(localtime_s(&_ReturnTm, &_Time));
	BFW_LINUX_PLATFORM_CALL(localtime_r(&_Time, &_ReturnTm));
	BFW_ESP32_PLATFORM_CALL(localtime_r(&_Time, &_ReturnTm));

	return _ReturnTm;
}

#ifdef BFW_WINDOWS_PLATFORM

const TIMECAPS BFW_API BFW::Time::GetTimeCaps()
{
	return TimeCaps;
}

#endif
