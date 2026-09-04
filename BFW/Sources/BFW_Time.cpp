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

const std::chrono::system_clock::time_point& BFW::Time::Timer::GetBegin() const
{
	return Begin;
}

const std::chrono::system_clock::time_point& BFW::Time::Timer::GetEnd() const
{
	return End;
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



BFW::Time::ScopeTimer::ScopeTimer(const LogScopeTimeFnc _LogFnc, const BFW_CHAR_TYPE* _File, const size_t _Line, const BFW_CHAR_TYPE* _Name) : ScopeTime(), LogFnc(_LogFnc), File(_File), Line(_Line), Name(BFW_STRING_PREFIX(""))
{
	if (_Name)
	{
		Name = _Name;
	}
}

BFW::Time::ScopeTimer::ScopeTimer(const ScopeTimer& _Other) : ScopeTime(_Other.ScopeTime), LogFnc(_Other.LogFnc), File(_Other.File), Line(_Other.Line), Name(_Other.Name)
{

}

BFW::Time::ScopeTimer::ScopeTimer(ScopeTimer&& _Other) noexcept : ScopeTime((Timer&&)(_Other.ScopeTime)), LogFnc(_Other.LogFnc), File(_Other.File), Line(_Other.Line), Name(_Other.Name)
{
	_Other.LogFnc = nullptr;
	_Other.File = nullptr;
	_Other.Line = 0;
	_Other.Name = BFW_STRING_PREFIX("");
}

BFW::Time::ScopeTimer::~ScopeTimer()
{
	ScopeTime.Stop();

	if (LogFnc)
	{
		LogFnc(ScopeTime, File, Line, Name.c_str());
	}
}

void BFW::Time::ScopeTimer::SetLogFnc(const LogScopeTimeFnc _LogFnc)
{
	LogFnc = _LogFnc;
}

void BFW::Time::ScopeTimer::SetFile(const BFW_CHAR_TYPE* _File)
{
	File = _File;
}

void BFW::Time::ScopeTimer::SetLine(const size_t _Line)
{
	Line = _Line;
}

void BFW::Time::ScopeTimer::SetName(const BFW_CHAR_TYPE* _Name)
{
	if (!_Name)
	{
		Name = BFW_STRING_PREFIX("");
		return;
	}

	Name = _Name;
}

const BFW::Time::LogScopeTimeFnc BFW::Time::ScopeTimer::GetLogFnc() const
{
	return LogFnc;
}

const BFW_CHAR_TYPE* BFW::Time::ScopeTimer::GetFile() const
{
	return File;
}

const size_t BFW::Time::ScopeTimer::GetLine() const
{
	return Line;
}

const BFW_CHAR_TYPE* BFW::Time::ScopeTimer::GetName() const
{
	return Name.c_str();
}

BFW::Time::ScopeTimer& BFW::Time::ScopeTimer::operator= (const ScopeTimer& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	ScopeTime = _Other.ScopeTime;
	LogFnc = _Other.LogFnc;
	File = _Other.File;
	Line = _Other.Line;
	Name = _Other.Name;

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
	File = _Other.File;
	Line = _Other.Line;
	Name = _Other.Name;

	_Other.LogFnc = nullptr;
	_Other.File = nullptr;
	_Other.Line = 0;
	_Other.Name = BFW_STRING_PREFIX("");

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

const uint64_t BFW_API BFW::Time::GetTimeStamp(const std::chrono::system_clock::time_point& _Time)
{
	return (uint64_t)(std::chrono::duration_cast<std::chrono::nanoseconds>(_Time.time_since_epoch()).count());
}

const tm BFW_API BFW::Time::TimePointToUTC(const std::chrono::system_clock::time_point& _Time)
{
	tm _ReturnTm = { 0 };

	time_t _TimeT = std::chrono::system_clock::to_time_t(_Time);

	BFW_WINDOWS_PLATFORM_CALL(gmtime_s(&_ReturnTm, &_TimeT));
	BFW_LINUX_PLATFORM_CALL(gmtime_r(&_TimeT, &_ReturnTm));
	BFW_ESP32_PLATFORM_CALL(gmtime_r(&_TimeT, &_ReturnTm));

	return _ReturnTm;
}

const tm BFW_API BFW::Time::TimePointToLocal(const std::chrono::system_clock::time_point& _Time)
{
	tm _ReturnTm = { 0 };

	time_t _TimeT = std::chrono::system_clock::to_time_t(_Time);

	BFW_WINDOWS_PLATFORM_CALL(localtime_s(&_ReturnTm, &_TimeT));
	BFW_LINUX_PLATFORM_CALL(localtime_r(&_TimeT, &_ReturnTm));
	BFW_ESP32_PLATFORM_CALL(localtime_r(&_TimeT, &_ReturnTm));

	return _ReturnTm;
}

#ifdef BFW_WINDOWS_PLATFORM

const TIMECAPS BFW_API BFW::Time::GetTimeCaps()
{
	return TimeCaps;
}

#endif
