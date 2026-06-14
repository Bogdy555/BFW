#include "../Headers/BFW.hpp"



#ifdef BFW_BUILD_DYNAMIC

#ifdef BFW_WINDOWS_PLATFORM

BOOL WINAPI DllMain(HINSTANCE _hInstance, DWORD _CallReason, LPVOID _Reserved)
{
	switch (_CallReason)
	{
	case DLL_PROCESS_ATTACH:
	{
		break;
	}
	case DLL_PROCESS_DETACH:
	{
		break;
	}
	case DLL_THREAD_ATTACH:
	{
		break;
	}
	case DLL_THREAD_DETACH:
	{
		break;
	}
	default:
	{
		return false;
	}
	}

	return true;
}

#endif

#endif
