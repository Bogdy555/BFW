#ifndef BFW_Log_hpp

#define BFW_Log_hpp



#include "BFW.hpp"



namespace BFW
{

	namespace Log
	{

#if defined BFW_WINDOWS_PLATFORM || defined BFW_LINUX_PLATFORM

		enum BFW_API Attributes : const uint16_t
		{
			_TxtBlackAttribute = 0,
			_TxtBlueAttribute = 1,
			_TxtGreenAttribute = 2,
			_TxtAquaAttribute = 3,
			_TxtRedAttribute = 4,
			_TxtPurpleAttribute = 5,
			_TxtYellowAttribute = 6,
			_TxtLightGrayAttribute = 7,
			_TxtGrayAttribute = 8,
			_TxtLightBlueAttribute = 9,
			_TxtLightGreenAttribute = 10,
			_TxtTurquoiseAttribute = 11,
			_TxtPinkAttribute = 12,
			_TxtLightPurpleAttribute = 13,
			_TxtLightYellowAttribute = 14,
			_TxtWhiteAttribute = 15,
			_BkgBlackAttribute = 0,
			_BkgBlueAttribute = 16,
			_BkgGreenAttribute = 32,
			_BkgAquaAttribute = 48,
			_BkgRedAttribute = 64,
			_BkgPurpleAttribute = 80,
			_BkgYellowAttribute = 96,
			_BkgLightGrayAttribute = 112,
			_BkgGrayAttribute = 128,
			_BkgLightBlueAttribute = 144,
			_BkgLightGreenAttribute = 160,
			_BkgTurquoiseAttribute = 176,
			_BkgPinkAttribute = 192,
			_BkgLightPurpleAttribute = 208,
			_BkgLightYellowAttribute = 224,
			_BkgWhiteAttribute = 240
		};

#endif

		extern BFW_API std::mutex* Mutex;

		BFW_DEBUG_CALL(extern std::ofstream BFW_API LoggingFile);
		BFW_DEBUG_CALL(extern BFW_API std::mutex* LoggingFileMutex);

		BFW_DEBUG_CALL(extern std::ofstream BFW_API ProfilingFile);
		BFW_DEBUG_CALL(extern BFW_API std::mutex* ProfilingFileMutex);
		BFW_DEBUG_CALL(extern BFW_API Assets::Json* ProfilingJson);
		BFW_DEBUG_CALL(extern BFW_API const uint64_t& ProfilingStart);

#if defined BFW_WINDOWS_PLATFORM || defined BFW_LINUX_PLATFORM

		const bool BFW_API Init();
		void BFW_API Stop();

#endif

#ifdef BFW_ESP32_PLATFORM

		const bool BFW_API Init(const size_t _BaudRate = 115200, const BFW_STRING_TYPE& _SDCardPath = "/sdcard");
		void BFW_API Stop();

#endif

#if defined BFW_WINDOWS_PLATFORM || defined BFW_LINUX_PLATFORM

		const bool BFW_API SetConsoleAttribute(const uint16_t _Attribute);

#endif

#ifdef BFW_WINDOWS_PLATFORM

		const bool BFW_API GetConsoleAttribute(uint16_t& _Attribute);

		const HANDLE BFW_API GetConsoleHandle();
		const uint16_t BFW_API GetDefaultAttribute();

#endif

	}

}



#endif
