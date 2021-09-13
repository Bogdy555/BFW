#include "..\Headers\BFW.hpp"



#ifdef BFW_WINDOWS_PLATFORM



#ifdef BFW_DLL_BUILD



BOOL WINAPI DllMain(HINSTANCE _hInstance, DWORD _CallReason, LPVOID _Reserved)
{
	switch (_CallReason)
	{
	case DLL_PROCESS_ATTACH:
	{
		break;
	}
	case DLL_THREAD_ATTACH:
	{
		break;
	}
	case DLL_PROCESS_DETACH:
	{
		break;
	}
	case DLL_THREAD_DETACH:
	{
		break;
	}
	default:
	{
		return FALSE;
	}
	}
	return TRUE;
}



#endif



#endif
