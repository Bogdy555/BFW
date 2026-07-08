#ifndef BFW_Dependencies_hpp

#define BFW_Dependencies_hpp



#ifdef BFW_WINDOWS_PLATFORM

#pragma comment(lib, "WinMM.Lib")
#pragma comment(lib, "Xinput9_1_0.lib")

#endif



#ifdef BFW_WINDOWS_PLATFORM

#include "BFW_WinTargetVer.hpp"
#include <Windows.h>
#include <Xinput.h>

#endif

#ifdef BFW_LINUX_PLATFORM

#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <linux/joystick.h>

#endif

#ifdef BFW_ESP32_PLATFORM

#include <Arduino.h>

#endif

#include <type_traits>
#include <iostream>
#include <string>
#include <cmath>
#include <chrono>
#include <ctime>
#include <cstdint>
#include <thread>
#include <mutex>



#include "BFW_Macros.hpp"



namespace BFW
{

	enum BFW_API States : const size_t
	{
		_PreviousState = 0,
		_CurrentState = 1
	};

	namespace Debug
	{

		struct BFW_API HeapPointer;

		class BFW_API HeapTracker;

	}

	namespace Log
	{

#if defined BFW_WINDOWS_PLATFORM || defined BFW_LINUX_PLATFORM

		enum BFW_API Attributes : const uint16_t;

#endif

	}

	namespace Math
	{

		class BFW_API Vec2;

		class BFW_API Vec3;

		class BFW_API Vec4;

		class BFW_API Mat2;

		class BFW_API Mat3;

		class BFW_API Mat4;

		class BFW_API Quat;

	}

	namespace Time
	{

		class BFW_API Timer;

		typedef void (*LogScopeTimeFnc)(const float _ScopeTime);

		class BFW_API ScopeTimer;

	}

	namespace MultiProcessing
	{

		enum BFW_API ReturnValues : const int32_t;

#if defined BFW_WINDOWS_PLATFORM || defined BFW_LINUX_PLATFORM

		class BFW_API Process;

		class BFW_API SharedMemory;

		class BFW_API SharedMutex;

#endif

	}

	namespace RunTime
	{

		class BFW_API Application;

		enum BFW_API Menus : const uint64_t;

		class BFW_API Menu;

	}

	namespace Input
	{

		class BFW_API Key;

		struct BFW_API ClickEvent;

		struct BFW_API WheelEvent;

#if defined BFW_WINDOWS_PLATFORM || defined BFW_LINUX_PLATFORM

		class BFW_API Controller;

#endif

	}

	namespace GUI
	{

#if defined BFW_WINDOWS_PLATFORM || defined BFW_LINUX_PLATFORM

		class BFW_API Window;

#endif

		enum BFW_API PopUpIds : const uint64_t;

		enum BFW_API PanelTypes : const uint8_t;

		class BFW_API SafePopUpPointer;

		class BFW_API PopUp;

		typedef void* (*GenerateUserDataFnc)(PopUp& _ParentWnd, void* _Global);
		typedef void (*ReleaseUserDataFnc)(PopUp& _Wnd, void* _Global);
		typedef void (*SetupRenderDataFnc)(PopUp& _Wnd, PopUp& _ParentWnd, void* _Global);
		typedef void (*CleanUpRenderDataFnc)(PopUp& _Wnd, void* _Global);
		typedef void (*RenderFnc)(PopUp& _Wnd, void* _Global);
		typedef void (*CompositFnc)(PopUp& _ParentWnd, PopUp& _ChildWnd, void* _Global);
		typedef const size_t (*GetMinFnc)(const uint64_t _PopUpId);
		typedef const bool (*IgnoreScrollFnc)(const uint64_t _PopUpId);
		typedef const bool (*ForceScrollFnc)(const uint64_t _PopUpId);
		typedef void (*ResizePopUpLayerFnc)(PopUp& _Parent, const size_t _Layer, const GetMinFnc _GetMinX, const GetMinFnc _GetMinY, const size_t _ResizeSize, const ForceScrollFnc _ForceHScroll, const ForceScrollFnc _ForceVScroll, const size_t _ScrollSize, const size_t _ScrollTopPadding, const size_t _ScrollPadding, const SetupRenderDataFnc _SetupData, const CleanUpRenderDataFnc _CleanUpData, const RenderFnc _RenderBottomWindow, const RenderFnc _RenderMiddleWindow, const RenderFnc _RenderTopWindow, const RenderFnc _RenderBottomButton, const RenderFnc _RenderMiddleButton, const RenderFnc _RenderTopButton, const CompositFnc _Composit, const GenerateUserDataFnc _GenerateUserData, const ReleaseUserDataFnc _ReleaseUserData, void* _Global);

	}

}



#include "BFW_Templates.hpp"



#endif
