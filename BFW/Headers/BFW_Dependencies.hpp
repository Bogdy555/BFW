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
#include <sys/file.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <linux/joystick.h>

#endif

#ifdef BFW_ESP32_PLATFORM

#include <Arduino.h>

#endif

#include <type_traits>
#include <cstdint>
#include <limits>
#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <sstream>
#include <cctype>
#include <locale>
#include <thread>
#include <mutex>
#include <cstdlib>
#include <functional>
#include <cmath>
#include <random>
#include <chrono>
#include <ctime>
#include <filesystem>



#include "BFW_Macros.hpp"



namespace BFW
{

	enum BFW_API States : const size_t
	{
		_PreviousState = 0,
		_CurrentState = 1
	};

	template <typename T> class Vector;

	template <typename T> class UniquePointer;

	template <typename T> class SharedPointer;

	template <typename T> class WeakPointer;

	template <typename T, typename CharT> requires (!std::is_const_v<CharT>) class Trie;

	template <typename T, typename ValueT, const bool (*Rule)(const ValueT _Parent, const ValueT _Child)> requires (!std::is_const_v<ValueT>) class Heap;

	template <typename T> struct AnimationState;

	template <typename T> class Animation;

	template <typename T> class StepAnimation;

	template <typename T, std::add_const_t<T> (*Lerper)(std::add_const_t<T>&, std::add_const_t<T>&, const float)> class LinearAnimation;

	namespace String
	{



	}

	namespace GUID
	{



	}

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

	namespace Cryptography
	{



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

		class BFW_API RandomUInt64;

		class BFW_API RandomFloat;

	}

	namespace Time
	{

		class BFW_API Timer;

		typedef void (*LogScopeTimeFnc)(const Timer& _ScopeTimer, const BFW_CHAR_TYPE* _File, const size_t _Line, const BFW_CHAR_TYPE* _Name);

		class BFW_API ScopeTimer;

	}

	namespace FileSystem
	{

		class BFW_API FileContent;

		class BFW_API File;

		class BFW_API Directory;

		class BFW_API DirectoryDiff;

#ifdef BFW_WINDOWS_PLATFORM

		typedef HANDLE LockedDirectoryHandle;

#endif

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

#if defined BFW_WINDOWS_PLATFORM || defined BFW_LINUX_PLATFORM

		enum BFW_API KeyIds : const uint8_t;

#endif

		class BFW_API Key;

		struct BFW_API ClickEvent;

		struct BFW_API WheelEvent;

#if defined BFW_WINDOWS_PLATFORM || defined BFW_LINUX_PLATFORM

		class BFW_API Controller;

#endif

	}

	namespace GUI
	{

#if defined BFW_WINDOWS_PLATFORM

		class BFW_API Window;

		typedef const bool (*ThreadInitFnc)(void* _UserData);
		typedef void (*ThreadCleanUpFnc)(void* _UserData);
		typedef const bool (*WndInitFnc)(Window* _Wnd);
		typedef void (*WndCleanUpFnc)(Window* _Wnd);

#endif

		enum BFW_API PopUpIds : const uint64_t;

		enum BFW_API PanelTypes : const uint8_t;

		struct BFW_API RenderingDescriptor;

		class BFW_API SafePopUpPointer;

		class BFW_API PopUp;

		typedef void* (*GenerateUserDataFnc)(const uint64_t _PopUpId, void* _Global);
		typedef void (*ReleaseUserDataFnc)(void* _PopUpUserData);
		typedef void (*SetupRenderDataFnc)(PopUp& _Wnd, PopUp& _Parent, void* _Global);
		typedef void (*CleanUpRenderDataFnc)(PopUp& _Wnd, void* _Global);
		typedef void (*RenderFnc)(PopUp& _Wnd, void* _Global);
		typedef void (*CompositFnc)(PopUp& _Parent, PopUp& _ChildWnd, void* _Global);
		typedef const bool (*HitBoxFnc)(const intptr_t _PositionX, const intptr_t _PositionY, const size_t _Width, const size_t _Height);
		typedef const size_t (*GetMinFnc)(const PopUp& _PopUp);
		typedef const bool (*IgnoreScrollFnc)(const uint64_t _PopUpId);
		typedef const bool (*ForceScrollFnc)(const uint64_t _PopUpId);
		typedef const bool (*IsMovableFnc)(const uint64_t _PopUpId);
		typedef const bool (*IsScrollableFnc)(const uint64_t _PopUpId);
		typedef const HitBoxFnc (*GetHitBoxFnc)(const uint64_t _PopUpId);
		typedef const RenderingDescriptor& (*GetRenderingDescriptorFnc)(const uint64_t _PopUpId);
		typedef void (*ResizePopUpLayerFnc)(PopUp& _Parent, const size_t _Layer, const GetMinFnc _GetMinX, const GetMinFnc _GetMinY, const size_t _ResizeSize, const ForceScrollFnc _ForceHScroll, const ForceScrollFnc _ForceVScroll, const size_t _ScrollSize, const size_t _ScrollTopPadding, const size_t _ScrollPadding, const GetRenderingDescriptorFnc _GetRenderingDescriptor, const GetHitBoxFnc _GetHitBox, const GenerateUserDataFnc _GenerateUserData, const ReleaseUserDataFnc _ReleaseUserData, void* _Global);

	}

	namespace Assets
	{

		class BFW_API BitMap;

		struct BFW_API WaveFormat;

		class BFW_API Wave;

		enum BFW_API JsonTypes : const uint8_t;

		struct BFW_API JsonObjectData;

		class BFW_API Json;

	}

}



#include "BFW_Templates.hpp"



#endif
