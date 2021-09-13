#ifndef BFW_ARDUINO_Dependencies_hpp

#define BFW_ARDUINO_Dependencies_hpp



#ifndef F_CPU

#define F_CPU 16000000L

#endif



#ifndef ARDUINO

#define ARDUINO 10815

#endif



#ifndef ARDUINO_AVR_UNO

#define ARDUINO_AVR_UNO

#endif



#ifndef ARDUINO_ARCH_AVR

#define ARDUINO_ARCH_AVR

#endif



#ifndef UBRRH

#define UBRRH

#endif



#ifndef BFW_ARDUINO_PLATFORM

#define BFW_ARDUINO_PLATFORM

#endif



#ifndef BFW_VENDOR

#define BFW_VENDOR

#endif



#include "..\..\BFW\Headers\BFW.hpp"



#include "BFW_ARDUINO_Macros.hpp"



namespace BFW_ARDUINO
{

	namespace Enums
	{

		typedef const unsigned long _Menus;

	}

	namespace Typedef
	{



	}

	class Application;

	class MainMenu;

}



#endif
