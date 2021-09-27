#if !defined BFW_DLL_LINK && !defined BFW_STATIC_LINK && !defined BFW_VENDOR

#define BFW_VENDOR

#endif

#if !defined BFW_WINDOWS_PLATFORM && !defined BFW_ARDUINO_PLATFORM

#define BFW_WINDOWS_PLATFORM

#endif



#include "..\..\BFW\Headers\BFW.hpp"



long BFW_Log_Example()
{
	BFW::Log::Init();

	BFW_PRINT(BFW_STRING("Regular print\n"));
	BFW_LOG(BFW_STRING("Debug print\n"));
	BFW_PRINT(BFW_STRING('\n'));

	BFW::Log::Tree Log(BFW_STRING("BFW"));

	BFW::Log::Tree Log1(BFW_STRING("BFW"));
	BFW_WINDOWS_CALL(Log1.SetAttribute(BFW::Enums::_ConsoleTxtPurple));
	BFW::Log::Tree Log2(BFW_STRING("BFW_APP"));
	BFW_WINDOWS_CALL(Log2.SetAttribute(BFW::Enums::_ConsoleTxtPurple));
	BFW::Log::Tree Log3(BFW_STRING("BFW_ARDUINO"));
	BFW_WINDOWS_CALL(Log3.SetAttribute(BFW::Enums::_ConsoleTxtPurple));

	BFW::Log::Tree Log11(BFW_STRING("BFW_DLL"));
	BFW_WINDOWS_CALL(Log11.SetAttribute(BFW::Enums::_ConsoleTxtLightYellow));
	BFW::Log::Tree Log12(BFW_STRING("BFW_STATIC"));
	BFW_WINDOWS_CALL(Log12.SetAttribute(BFW::Enums::_ConsoleTxtLightYellow));
	BFW::Log::Tree Log21(BFW_STRING("BFW_APP_DLL"));
	BFW_WINDOWS_CALL(Log21.SetAttribute(BFW::Enums::_ConsoleTxtLightYellow));
	BFW::Log::Tree Log22(BFW_STRING("BFW_APP_STATIC"));
	BFW_WINDOWS_CALL(Log22.SetAttribute(BFW::Enums::_ConsoleTxtLightYellow));

	Log.GetKids().MoveBack(&Log1);
	Log.GetKids().MoveBack(&Log2);
	Log.GetKids().MoveBack(&Log3);

	Log1.GetKids().MoveBack(&Log11);
	Log1.GetKids().MoveBack(&Log12);
	Log2.GetKids().MoveBack(&Log21);
	Log2.GetKids().MoveBack(&Log22);

	BFW_WINDOWS_CALL(Log.LogToConsole(2));

	BFW_ARDUINO_CALL(Log.LogToSerialPort(2));

	BFW::Log::Stop();

	return BFW::Enums::_ReturnNoError;
}
