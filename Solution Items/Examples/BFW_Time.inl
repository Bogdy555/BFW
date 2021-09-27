#if !defined BFW_DLL_LINK && !defined BFW_STATIC_LINK && !defined BFW_VENDOR

#define BFW_VENDOR

#endif

#if !defined BFW_WINDOWS_PLATFORM && !defined BFW_ARDUINO_PLATFORM

#define BFW_WINDOWS_PLATFORM

#endif



#include "..\..\BFW\Headers\BFW.hpp"



long BFW_Time_Example()
{
	BFW::Log::Init();

	BFW_WINDOWS_CALL(BFW::Time::Init());

	BFW::Time::Timer Tmr;

	Tmr.Start();

	BFW::Time::SleepMilliSec(100);

	Tmr.Stop();

	BFW_PRINT(Tmr * BFW::Time::SecToMicro);
	BFW_PRINT(' ');
	BFW_PRINT(Tmr * BFW::Time::SecToMilli);
	BFW_PRINT(' ');
	BFW_PRINT(Tmr);
	BFW_PRINT('\n');

	BFW_WINDOWS_CALL(BFW::Time::Stop());

	BFW::Log::Stop();

	return BFW::Enums::_ReturnNoError;
}
