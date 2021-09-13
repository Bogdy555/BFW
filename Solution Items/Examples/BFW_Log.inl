#if !defined BFW_DLL_LINK && !defined BFW_STATIC_LINK && !defined BFW_VENDOR

#define BFW_VENDOR

#endif

#if !defined BFW_WINDOWS_PLATFORM && !defined BFW_ARDUINO_PLATFORM

#define BFW_WINDOWS_PLATFORM

#endif



#include "..\..\BFW\Headers\BFW.hpp"



void BFW_Log_Example()
{
	BFW_PRINT(BFW_STRING("Regular print\n"));
	BFW_LOG(BFW_STRING("Debug print\n"));

	BFW::Log::Init();

	BFW::Log::Tree Log(BFW_STRING("Log"));

	BFW::Log::Tree Log1(BFW_STRING("Log1"));
	BFW::Log::Tree Log2(BFW_STRING("Log2"));
	BFW::Log::Tree Log3(BFW_STRING("Log3"));

	BFW::Log::Tree Log11(BFW_STRING("Log11"));
	BFW::Log::Tree Log21(BFW_STRING("Log21"));
	BFW::Log::Tree Log31(BFW_STRING("Log31"));

	Log.GetKids().MoveBack(&Log1);
	Log.GetKids().MoveBack(&Log2);
	Log.GetKids().MoveBack(&Log3);

	Log1.GetKids().MoveBack(&Log11);
	Log2.GetKids().MoveBack(&Log21);
	Log3.GetKids().MoveBack(&Log31);

	BFW_WINDOWS_CALL(Log.LogToConsole());

	BFW_ARDUINO_CALL(Log.LogToSerialPort());

	BFW::Log::Stop();
}
