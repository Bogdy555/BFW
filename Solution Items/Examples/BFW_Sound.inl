#if !defined BFW_DLL_LINK && !defined BFW_STATIC_LINK && !defined BFW_VENDOR

#define BFW_VENDOR

#endif

#if !defined BFW_WINDOWS_PLATFORM && !defined BFW_ARDUINO_PLATFORM

#define BFW_WINDOWS_PLATFORM

#endif



#include "..\..\BFW\Headers\BFW.hpp"



#ifdef BFW_WINDOWS_PLATFORM



long BFW_Sound_Example()
{
	return BFW::Enums::_ReturnNoError;
}



#endif
