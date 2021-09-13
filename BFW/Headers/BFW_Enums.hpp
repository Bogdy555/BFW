#ifndef BFW_Enums_hpp

#define BFW_Enums_hpp



#include "BFW.hpp"



namespace BFW
{

	namespace Enums
	{

#ifdef BFW_WINDOWS_PLATFORM

		enum BFW_API _States : const unsigned long
		{
			_Previous = 0,
			_Current = 1
		};

		enum BFW_API _ReturnValues : const long
		{
			_ReturnError = -1,
			_ReturnNoError = 0,
			_ReturnStillRunning = 259
		};

		enum BFW_API _Menus : const unsigned long
		{
			_NullMenu = 0
		};

		enum BFW_API _ConsoleTxtColor : const unsigned short
		{
			_ConsoleTxtBlack = 0,
			_ConsoleTxtBlue = 1,
			_ConsoleTxtGreen = 2,
			_ConsoleTxtAqua = 3,
			_ConsoleTxtRed = 4,
			_ConsoleTxtPurple = 5,
			_ConsoleTxtYellow = 6,
			_ConsoleTxtLightGrey = 7,
			_ConsoleTxtGrey = 8,
			_ConsoleTxtLightBlue = 9,
			_ConsoleTxtLightGreen = 10,
			_ConsoleTxtTurquoise = 11,
			_ConsoleTxtPink = 12,
			_ConsoleTxtLightPurple = 13,
			_ConsoleTxtLightYellow = 14,
			_ConsoleTxtWhite = 15
		};

		enum BFW_API _ConsoleBkgColor : const unsigned short
		{
			_ConsoleBkgBlack = 0,
			_ConsoleBkgBlue = 16,
			_ConsoleBkgGreen = 32,
			_ConsoleBkgAqua = 48,
			_ConsoleBkgRed = 64,
			_ConsoleBkgPurple = 80,
			_ConsoleBkgYellow = 96,
			_ConsoleBkgLightGrey = 112,
			_ConsoleBkgGrey = 128,
			_ConsoleBkgLightBlue = 144,
			_ConsoleBkgLightGreen = 160,
			_ConsoleBkgTurquoise = 176,
			_ConsoleBkgPink = 192,
			_ConsoleBkgLightPurple = 208,
			_ConsoleBkgLightYellow = 224,
			_ConsoleBkgWhite = 240
		};

		enum BFW_API _VKCodes : unsigned char
		{
			_NullVKCode = (unsigned char)(0xFF)
		};

		enum BFW_API _Controller : long long
		{
			_ControllerIDCount = 4,
			_ControllerMaxRumble = 65535,
			_ControllerMaxShoulder = 255,
			_ControllerMinThumb = -32768,
			_ControllerMaxThumb = 32767,
			_ControllerThresHold = 30,
			_ControllerDeadZoneLeft = 7849,
			_ControllerDeadZoneRight = 8689
		};

		enum BFW_API _Axis : unsigned long
		{
			_x = 0,
			_y = 1,
			_z = 2,
			_w = 3
		};

#endif

#ifdef BFW_ARDUINO_PLATFORM

		typedef const unsigned long _States;

		static constexpr _States _Previous = 0;
		static constexpr _States _Current = 1;



		typedef const long _ReturnValues;

		static constexpr _ReturnValues _ReturnError = -1;
		static constexpr _ReturnValues _ReturnNoError = 0;
		static constexpr _ReturnValues _ReturnStillRunning = 259;



		typedef const unsigned long _Menus;

		static constexpr _Menus _NullMenu = 0;



		typedef const unsigned long _Axis;

		static constexpr _Axis _x = 0;
		static constexpr _Axis _y = 0;
		static constexpr _Axis _z = 0;
		static constexpr _Axis _w = 0;

#endif

	}

}



#endif
