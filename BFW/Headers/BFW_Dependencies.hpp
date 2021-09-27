#ifndef BFW_Dependencies_hpp

#define BFW_Dependencies_hpp



#ifdef BFW_WINDOWS_PLATFORM



#if defined BFW_DLL_BUILD || defined BFW_STATIC_BUILD || defined BFW_STATIC_LINK || defined BFW_VENDOR

#pragma comment(lib, "WinMM.lib")
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "strmiids.lib")
#pragma comment(lib, "Xinput9_1_0.lib")

#endif



#ifdef BFW_DLL_LINK

#pragma comment(lib, "BFW_DLL.lib")

#endif



#ifdef BFW_STATIC_LINK

#pragma comment(lib, "BFW_STATIC.lib")

#endif



#include "BFW_WinTargetVer.hpp"
#include <Windows.h>
#include <shellapi.h>
#include <commdlg.h>
#include <Xinput.h>
#include <dsound.h>
#include <dshow.h>

interface ISampleGrabberCB : public IUnknown
{
	virtual STDMETHODIMP SampleCB(double SampleTime, IMediaSample* pSample) = 0;
	virtual STDMETHODIMP BufferCB(double SampleTime, BYTE* pBuffer, long BufferLen) = 0;
};

interface ISampleGrabber : public IUnknown
{
	virtual HRESULT STDMETHODCALLTYPE SetOneShot(BOOL OneShot) = 0;
	virtual HRESULT STDMETHODCALLTYPE SetMediaType(const AM_MEDIA_TYPE* pType) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetConnectedMediaType(AM_MEDIA_TYPE* pType) = 0;
	virtual HRESULT STDMETHODCALLTYPE SetBufferSamples(BOOL BufferThem) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetCurrentBuffer(long* pBufferSize, long* pBuffer) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetCurrentSample(IMediaSample** ppSample) = 0;
	virtual HRESULT STDMETHODCALLTYPE SetCallback(ISampleGrabberCB* pCallback, long WhichMethodToCallback) = 0;
};

static constexpr IID IID_ISampleGrabberCB = { 0x0579154A, 0x2B53, 0x4994, { 0xB0, 0xD0, 0xE7, 0x73, 0x14, 0x8E, 0xFF, 0x85 } };
static constexpr IID IID_ISampleGrabber = { 0x6B652FFF, 0x11FE, 0x4fce, { 0x92, 0xAD, 0x02, 0x66, 0xB5, 0xD7, 0xC7, 0x8F } };
static constexpr CLSID CLSID_SampleGrabber = { 0xC1F400A0, 0x3F08, 0x11d3, { 0x9F, 0x0B, 0x00, 0x60, 0x08, 0x03, 0x9E, 0x37 } };
static constexpr CLSID CLSID_NullRenderer = { 0xC1F400A4, 0x3F08, 0x11d3, { 0x9F, 0x0B, 0x00, 0x60, 0x08, 0x03, 0x9E, 0x37 } };
static constexpr CLSID CLSID_VideoEffects1Category = { 0xcc7bfb42, 0xf175, 0x11d1, { 0xa3, 0x92, 0x0, 0xe0, 0x29, 0x1f, 0x39, 0x59 } };
static constexpr CLSID CLSID_VideoEffects2Category = { 0xcc7bfb43, 0xf175, 0x11d1, { 0xa3, 0x92, 0x0, 0xe0, 0x29, 0x1f, 0x39, 0x59 } };
static constexpr CLSID CLSID_AudioEffects1Category = { 0xcc7bfb44, 0xf175, 0x11d1, { 0xa3, 0x92, 0x0, 0xe0, 0x29, 0x1f, 0x39, 0x59 } };
static constexpr CLSID CLSID_AudioEffects2Category = { 0xcc7bfb45, 0xf175, 0x11d1, { 0xa3, 0x92, 0x0, 0xe0, 0x29, 0x1f, 0x39, 0x59 } };



#include <iostream>
#include <fstream>

#include <cstring>
#include <string>

#include <vector>

#include <chrono>

#include <thread>
#include <future>
#include <mutex>
#include <atomic>

#define _USE_MATH_DEFINES
#include <math.h>
#include <random>



#if defined BFW_DLL_BUILD || defined BFW_STATIC_BUILD || defined BFW_VENDOR

#include "..\Vendor\Glad\Headers\glad.hpp"

#endif



#endif



#ifdef BFW_ARDUINO_PLATFORM



#include "..\..\BFW_ARDUINO\Vendor\Arduino\Headers\Arduino.h"

#include <math.h>



#endif



#include "BFW_Macros.hpp"



namespace BFW
{

	namespace Enums
	{

#ifdef BFW_WINDOWS_PLATFORM

		enum BFW_API _States : const unsigned long;

		enum BFW_API _ReturnValues : const long;

		enum BFW_API _Menus : const unsigned long;

		enum BFW_API _ConsoleTxtColor : const unsigned short;

		enum BFW_API _ConsoleBkgColor : const unsigned short;

		enum BFW_API _VKCodes : unsigned char;

		enum BFW_API _Controller : long long;

		enum BFW_API _Axis : unsigned long;

#endif

#ifdef BFW_ARDUINO_PLATFORM

		typedef const unsigned long _States;

		typedef const long _ReturnValues;

		typedef const unsigned long _Menus;

		typedef const unsigned long _Axis;

#endif

	}

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

	namespace Debug
	{

		class BFW_API HeapPointer;

		class BFW_API HeapTracker;

	}

	namespace Log
	{

		class BFW_API Tree;

	}

	namespace Multiprocessing
	{

#ifdef BFW_WINDOWS_PLATFORM

		class BFW_API SharedMemory;

		class BFW_API Process;

#endif

	}

	namespace Time
	{

		class BFW_API Timer;

	}

	namespace Input
	{

#ifdef BFW_WINDOWS_PLATFORM

		class BFW_API Key;

		namespace Cursor
		{



		}

		class BFW_API RumbleState;

		class BFW_API RumbleSequence;

		class BFW_API Controller;

#endif

	}

	namespace Hardware
	{

#ifdef BFW_WINDOWS_PLATFORM

		class BFW_API SerialPort;

		class BFW_API Webcam;

		class BFW_API Microphone;

#endif

#ifdef BFW_ARDUINO_PLATFORM

		class BFW_API DigitalInputPullupPin;

		class BFW_API DigitalInputPin;

		class BFW_API DigitalOutputPin;

		class BFW_API AnalogInputPin;

		class BFW_API AnalogOutputPin;

#endif

	}

	namespace Math
	{

#ifdef BFW_WINDOWS_PLATFORM

		class BFW_API RandomLong;

		class BFW_API RandomLongLong;

		class BFW_API RandomFloat;

		class BFW_API RandomDouble;

		class BFW_API NoiseFloat;

		class BFW_API NoiseDouble;

		class BFW_API Crypt;

#endif

		class BFW_API Vec2f;

		class BFW_API Vec3f;

		class BFW_API Vec4f;

		class BFW_API Vec2d;

		class BFW_API Vec3d;

		class BFW_API Vec4d;

		class BFW_API Mat2f;

		class BFW_API Mat3f;

		class BFW_API Mat4f;

		class BFW_API Mat2d;

		class BFW_API Mat3d;

		class BFW_API Mat4d;

	}

	namespace Sound
	{

#ifdef BFW_WINDOWS_PLATFORM



#endif

	}

	template <typename T> class Vector;

	class BFW_API Application;

	class BFW_API Menu;

}



#include "BFW_Vector.hpp"



#ifdef BFW_WINDOWS_PLATFORM



#include "BFW_Templates.hpp"



#endif



#endif
