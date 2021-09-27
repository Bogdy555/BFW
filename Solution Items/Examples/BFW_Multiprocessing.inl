#if !defined BFW_DLL_LINK && !defined BFW_STATIC_LINK && !defined BFW_VENDOR

#define BFW_VENDOR

#endif

#if !defined BFW_WINDOWS_PLATFORM && !defined BFW_ARDUINO_PLATFORM

#define BFW_WINDOWS_PLATFORM

#endif



#include "..\..\BFW\Headers\BFW.hpp"



#ifdef BFW_WINDOWS_PLATFORM



long BFW_Multiprocessing_Example()
{
	BFW::Multiprocessing::SharedMemory SharedMemory;

	SharedMemory.Create(L"SharedMemoryName", 1);

	(*SharedMemory)++;

	if (*SharedMemory == 1)
	{
		BFW::Multiprocessing::Process Proc;

		Proc.Create(L"C:\\Windows\\system32\\notepad.exe");

		if (!Proc.CheckCreated())
		{
			BFW_PRINT("Process creation failed\n");
			std::cin.get();
		}

		while (Proc.CheckCreated())
		{
			Proc.UpdateStatus();
		}
	}
	if (*SharedMemory == 2)
	{
		BFW_PRINT(L"Process already running\n");
		std::cin.get();
	}

	(*SharedMemory)--;

	return BFW::Enums::_ReturnNoError;
}



#endif
