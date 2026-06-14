#ifndef BFW_WINDOWS_Dependencies_hpp

#define BFW_WINDOWS_Dependencies_hpp



#ifdef BFW_LINK_DYNAMIC

#pragma comment(lib, "BFW_DYNAMIC.lib")

#endif

#ifdef BFW_LINK_STATIC

#pragma comment(lib, "BFW_STATIC.lib")

#endif



#include <BFW.hpp>



#include "BFW_WINDOWS_Macros.hpp"



namespace BFW_WINDOWS
{

	namespace RunTime
	{

		class Application;

		enum Menus : const uint64_t;

		class MainMenu;

	}

}



#endif
