#ifndef BFW_Typedef_hpp

#define BFW_Typedef_hpp



#include "BFW.hpp"



namespace BFW
{

	namespace Typedef
	{

		typedef const unsigned short& UnsignedShortRef;

		typedef const unsigned long& UnsignedLongRef;

		typedef const bool& BoolRef;

		typedef const bool* BoolPtr;

		typedef const short* ShortPtr;

		typedef const unsigned char* UnsignedCharPtr;

#ifdef BFW_WINDOWS_PLATFORM

		typedef const HANDLE& HandleRef;

		typedef const tm& TimeRef;

		typedef const TIMECAPS& TimeCapsRef;

		typedef const POINT& PointRef;

#endif

#ifdef BFW_ARDUINO_PLATFORM



#endif

	}

}



#endif
