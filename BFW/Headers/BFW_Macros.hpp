#ifndef BFW_Macros_hpp

#define BFW_Macros_hpp



#include "BFW.hpp"



#if !defined BFW_WINDOWS_PLATFORM && !defined BFW_LINUX_PLATFORM && !defined BFW_ESP32_PLATFORM

#error You have to specify a target platform.

#endif

#ifdef BFW_WINDOWS_PLATFORM

#if defined BFW_LINUX_PLATFORM || defined BFW_ESP32_PLATFORM

#error You have to specify only one target platform.

#endif

#endif

#ifdef BFW_LINUX_PLATFORM

#if defined BFW_WINDOWS_PLATFORM || defined BFW_ESP32_PLATFORM

#error You have to specify only one target platform.

#endif

#endif

#ifdef BFW_ESP32_PLATFORM

#if defined BFW_WINDOWS_PLATFORM || defined BFW_LINUX_PLATFORM

#error You have to specify only one target platform.

#endif

#endif



#if !defined BFW_BUILD_DYNAMIC && !defined BFW_LINK_DYNAMIC && !defined BFW_BUILD_STATIC && !defined BFW_LINK_STATIC && !defined BFW_VENDOR

#error You have to specify a target preprocessor.

#endif

#ifdef BFW_BUILD_DYNAMIC

#if defined BFW_LINK_DYNAMIC || defined BFW_BUILD_STATIC || defined BFW_LINK_STATIC || defined BFW_VENDOR

#error You have to specify only one target preprocessor.

#endif

#endif

#ifdef BFW_LINK_DYNAMIC

#if defined BFW_BUILD_DYNAMIC || defined BFW_BUILD_STATIC || defined BFW_LINK_STATIC || defined BFW_VENDOR

#error You have to specify only one target preprocessor.

#endif

#endif

#ifdef BFW_BUILD_STATIC

#if defined BFW_BUILD_DYNAMIC || defined BFW_LINK_DYNAMIC || defined BFW_LINK_STATIC || defined BFW_VENDOR

#error You have to specify only one target preprocessor.

#endif

#endif

#ifdef BFW_LINK_STATIC

#if defined BFW_BUILD_DYNAMIC || defined BFW_LINK_DYNAMIC || defined BFW_BUILD_STATIC || defined BFW_VENDOR

#error You have to specify only one target preprocessor.

#endif

#endif

#ifdef BFW_VENDOR

#if defined BFW_BUILD_DYNAMIC || defined BFW_LINK_DYNAMIC || defined BFW_BUILD_STATIC || defined BFW_LINK_STATIC

#error You have to specify only one target preprocessor.

#endif

#endif



#if !defined BFW_X64 && !defined BFW_X86

#error You have to specify a target architecture.

#endif

#if defined BFW_X64 && defined BFW_X86

#error You have to specify only one target architecture.

#endif



#if !defined BFW_LITTLE_ENDIAN && !defined BFW_BIG_ENDIAN

#error You have to specify a target endian.

#endif

#if defined BFW_LITTLE_ENDIAN && defined BFW_BIG_ENDIAN

#error You have to specify only one target endian.

#endif



#if defined BFW_ESP32_PLATFORM && (defined BFW_BUILD_DYNAMIC || defined BFW_LINK_DYNAMIC)

#error Dynamic linking is not supported on this platform.

#endif

#if defined BFW_ESP32_PLATFORM && defined BFW_X64

#error x64 is not supported on this platform.

#endif



#ifdef BFW_WINDOWS_PLATFORM

#define BFW_WINDOWS_PLATFORM_CALL(X) X
#define BFW_LINUX_PLATFORM_CALL(X)
#define BFW_ESP32_PLATFORM_CALL(X)

#endif

#ifdef BFW_LINUX_PLATFORM

#define BFW_WINDOWS_PLATFORM_CALL(X)
#define BFW_LINUX_PLATFORM_CALL(X) X
#define BFW_ESP32_PLATFORM_CALL(X)

#endif

#ifdef BFW_ESP32_PLATFORM

#define BFW_WINDOWS_PLATFORM_CALL(X)
#define BFW_LINUX_PLATFORM_CALL(X)
#define BFW_ESP32_PLATFORM_CALL(X) X

#endif



#if defined BFW_BUILD_DYNAMIC || defined BFW_BUILD_STATIC

#define BFW_BUILD_CALL(X) X
#define BFW_LINK_CALL(X)

#endif

#if defined BFW_LINK_DYNAMIC || defined BFW_LINK_STATIC

#define BFW_BUILD_CALL(X)
#define BFW_LINK_CALL(X) X

#endif

#if defined BFW_BUILD_DYNAMIC || defined BFW_LINK_DYNAMIC

#define BFW_DYNAMIC_CALL(X) X
#define BFW_STATIC_CALL(X)

#endif

#if defined BFW_BUILD_STATIC || defined BFW_LINK_STATIC

#define BFW_DYNAMIC_CALL(X)
#define BFW_STATIC_CALL(X) X

#endif

#ifdef BFW_VENDOR

#define BFW_BUILD_CALL(X)
#define BFW_LINK_CALL(X)
#define BFW_DYNAMIC_CALL(X)
#define BFW_STATIC_CALL(X)
#define BFW_VENDOR_CALL(X) X

#endif

#ifndef BFW_VENDOR

#define BFW_VENDOR_CALL(X)

#endif



#ifdef BFW_DEBUG

#define BFW_DEBUG_CALL(X) X
#define BFW_RELEASE_CALL(X)

#endif

#ifndef BFW_DEBUG

#define BFW_DEBUG_CALL(X)
#define BFW_RELEASE_CALL(X) X

#endif



#ifdef BFW_X64

#define BFW_X64_CALL(X) X
#define BFW_X86_CALL(X)

#endif

#ifdef BFW_X86

#define BFW_X64_CALL(X)
#define BFW_X86_CALL(X) X

#endif



#ifdef BFW_LITTLE_ENDIAN

#define BFW_LITTLE_ENDIAN_CALL(X) X
#define BFW_BIG_ENDIAN_CALL(X)

#endif

#ifdef BFW_BIG_ENDIAN

#define BFW_LITTLE_ENDIAN_CALL(X)
#define BFW_BIG_ENDIAN_CALL(X) X

#endif



#ifdef _UNICODE

#define BFW_UNICODE_CALL(X) X
#define BFW_NON_UNICODE_CALL(X)

#endif

#ifndef _UNICODE

#define BFW_UNICODE_CALL(X)
#define BFW_NON_UNICODE_CALL(X) X

#endif



#define BFW_SWAP_BYTES_16(X) ((((X) & 0xFF) << 8) | (((X) & 0xFF00) >> 8))
#define BFW_SWAP_BYTES_32(X) ((((X) & 0xFF) << 24) | (((X) & 0xFF00) << 8) | (((X) & 0xFF0000) >> 8) | (((X) & 0xFF000000) >> 24))
#define BFW_SWAP_BYTES_64(X) ((((X) & 0xFF) << 56) | (((X) & 0xFF00) << 40) | (((X) & 0xFF0000) << 24) | (((X) & 0xFF000000) << 8) | (((X) & 0xFF00000000) >> 8) | (((X) & 0xFF0000000000) >> 24) | (((X) & 0xFF000000000000) >> 40) | (((X) & 0xFF00000000000000) >> 56))

#ifdef BFW_LITTLE_ENDIAN

#define BFW_LITTLE_ENDIAN_TO_MACHINE_16(X) X
#define BFW_LITTLE_ENDIAN_TO_MACHINE_32(X) X
#define BFW_LITTLE_ENDIAN_TO_MACHINE_64(X) X
#define BFW_MACHINE_TO_LITTLE_ENDIAN_16(X) X
#define BFW_MACHINE_TO_LITTLE_ENDIAN_32(X) X
#define BFW_MACHINE_TO_LITTLE_ENDIAN_64(X) X
#define BFW_BIG_ENDIAN_TO_MACHINE_16(X) BFW_SWAP_BYTES_16(X)
#define BFW_BIG_ENDIAN_TO_MACHINE_32(X) BFW_SWAP_BYTES_32(X)
#define BFW_BIG_ENDIAN_TO_MACHINE_64(X) BFW_SWAP_BYTES_64(X)
#define BFW_MACHINE_TO_BIG_ENDIAN_16(X) BFW_SWAP_BYTES_16(X)
#define BFW_MACHINE_TO_BIG_ENDIAN_32(X) BFW_SWAP_BYTES_32(X)
#define BFW_MACHINE_TO_BIG_ENDIAN_64(X) BFW_SWAP_BYTES_64(X)

#endif

#ifdef BFW_BIG_ENDIAN

#define BFW_LITTLE_ENDIAN_TO_MACHINE_16(X) BFW_SWAP_BYTES_16(X)
#define BFW_LITTLE_ENDIAN_TO_MACHINE_32(X) BFW_SWAP_BYTES_32(X)
#define BFW_LITTLE_ENDIAN_TO_MACHINE_64(X) BFW_SWAP_BYTES_64(X)
#define BFW_MACHINE_TO_LITTLE_ENDIAN_16(X) BFW_SWAP_BYTES_16(X)
#define BFW_MACHINE_TO_LITTLE_ENDIAN_32(X) BFW_SWAP_BYTES_32(X)
#define BFW_MACHINE_TO_LITTLE_ENDIAN_64(X) BFW_SWAP_BYTES_64(X)
#define BFW_BIG_ENDIAN_TO_MACHINE_16(X) X
#define BFW_BIG_ENDIAN_TO_MACHINE_32(X) X
#define BFW_BIG_ENDIAN_TO_MACHINE_64(X) X
#define BFW_MACHINE_TO_BIG_ENDIAN_16(X) X
#define BFW_MACHINE_TO_BIG_ENDIAN_32(X) X
#define BFW_MACHINE_TO_BIG_ENDIAN_64(X) X

#endif



#define BFW_CONCATENATE_HELPER(A, B) A ## B
#define BFW_CONCATENATE(A, B) BFW_CONCATENATE_HELPER(A, B)
#define BFW_CHAR_TYPE_A char
#define BFW_CHAR_TYPE_W wchar_t
#define BFW_STRING_TYPE_A std::string
#define BFW_STRING_TYPE_W std::wstring
#define BFW_STRING_METHOD_A string
#define BFW_STRING_METHOD_W wstring
#define BFW_STRING_VIEW_TYPE_A std::string_view
#define BFW_STRING_VIEW_TYPE_W std::wstring_view
#define BFW_STRING_STREAM_TYPE_A std::stringstream
#define BFW_STRING_STREAM_TYPE_W std::wstringstream
#define BFW_TO_STRING_A(X) std::to_string(X)
#define BFW_TO_STRING_W(X) std::to_wstring(X)
#define BFW_TO_STRING_PTR_A(X) std::to_string(X).c_str()
#define BFW_TO_STRING_PTR_W(X) std::to_wstring(X).c_str()
#define BFW_STRING_PREFIX_A(X) X
#define BFW_STRING_PREFIX_W(X) L ## X

#ifdef _UNICODE

#define BFW_CHAR_TYPE BFW_CHAR_TYPE_W
#define BFW_STRING_TYPE BFW_STRING_TYPE_W
#define BFW_STRING_METHOD BFW_STRING_METHOD_W
#define BFW_STRING_VIEW_TYPE BFW_STRING_VIEW_TYPE_W
#define BFW_STRING_STREAM_TYPE BFW_STRING_STREAM_TYPE_W
#define BFW_TO_STRING(X) BFW_TO_STRING_W(X)
#define BFW_TO_STRING_PTR(X) BFW_TO_STRING_PTR_W(X)
#define BFW_STRING_PREFIX(X) BFW_STRING_PREFIX_W(X)
#define BFW_UNICODE_TO_MACHINE(X, Error) [](const BFW_STRING_VIEW_TYPE_W& _XVal, bool* _Error) -> BFW_STRING_TYPE { if (_Error) { *_Error = false; } return (BFW_STRING_TYPE)(_XVal); }(X, Error)
#define BFW_UTF8_TO_MACHINE(X, Error) BFW::String::FromUTF8ToUnicode(X, Error)
#define BFW_MACHINE_TO_UNICODE(X, Error) [](const BFW_STRING_VIEW_TYPE_W& _XVal, bool* _Error) -> BFW_STRING_TYPE_W { if (_Error) { *_Error = false; } return (BFW_STRING_TYPE_W)(_XVal); }(X, Error)
#define BFW_MACHINE_TO_UTF8(X, Error) BFW::String::FromUnicodeToUTF8(X, Error)

#endif

#ifndef _UNICODE

#define BFW_CHAR_TYPE BFW_CHAR_TYPE_A
#define BFW_STRING_TYPE BFW_STRING_TYPE_A
#define BFW_STRING_METHOD BFW_STRING_METHOD_A
#define BFW_STRING_VIEW_TYPE BFW_STRING_VIEW_TYPE_A
#define BFW_STRING_STREAM_TYPE BFW_STRING_STREAM_TYPE_A
#define BFW_TO_STRING(X) BFW_TO_STRING_A(X)
#define BFW_TO_STRING_PTR(X) BFW_TO_STRING_PTR_A(X)
#define BFW_STRING_PREFIX(X) BFW_STRING_PREFIX_A(X)
#define BFW_UNICODE_TO_MACHINE(X, Error) BFW::String::FromUnicodeToUTF8(X, Error)
#define BFW_UTF8_TO_MACHINE(X, Error) [](const BFW_STRING_VIEW_TYPE_A& _XVal, bool* _Error) -> BFW_STRING_TYPE { if (_Error) { *_Error = false; } return (BFW_STRING_TYPE)(_XVal); }(X, Error)
#define BFW_MACHINE_TO_UNICODE(X, Error) BFW::String::FromUTF8ToUnicode(X, Error)
#define BFW_MACHINE_TO_UTF8(X, Error) [](const BFW_STRING_VIEW_TYPE_A& _XVal, bool* _Error) -> BFW_STRING_TYPE_A { if (_Error) { *_Error = false; } return (BFW_STRING_TYPE_A)(_XVal); }(X, Error)

#endif



#ifdef BFW_DEBUG

#define BFW_LOG_TO_FILE(X) *BFW::Log::LoggingFile << X
#define BFW_LOG_LINE_TO_FILE(X) *BFW::Log::LoggingFile << X << L'\n'

#endif

#ifndef BFW_DEBUG

#define BFW_LOG_TO_FILE(X)
#define BFW_LOG_LINE_TO_FILE(X)

#endif



#ifdef BFW_WINDOWS_PLATFORM



#ifdef BFW_BUILD_DYNAMIC

#define BFW_API __declspec(dllexport)
#define BFW_EXTERN

#endif

#ifdef BFW_LINK_DYNAMIC

#define BFW_API __declspec(dllimport)
#define BFW_EXTERN extern

#endif

#ifdef BFW_BUILD_STATIC

#define BFW_API

#endif

#ifdef BFW_LINK_STATIC

#define BFW_API

#endif

#ifdef BFW_VENDOR

#define BFW_API

#endif



#define BFW_PRINT(X) BFW::Log::SetConsoleAttribute(BFW::Log::GetDefaultAttribute()); std::wcout << X
#define BFW_PRINT_LINE(X) BFW::Log::SetConsoleAttribute(BFW::Log::GetDefaultAttribute()); std::wcout << X << L'\n'

#define BFW_PRINT_ERROR(X) BFW::Log::SetConsoleAttribute(BFW::Log::_TxtRedAttribute | BFW::Log::_BkgBlackAttribute); std::wcout << X
#define BFW_PRINT_ERROR_LINE(X) BFW::Log::SetConsoleAttribute(BFW::Log::_TxtRedAttribute | BFW::Log::_BkgBlackAttribute); std::wcout << X << L'\n'

#define BFW_PRINT_WARNING(X) BFW::Log::SetConsoleAttribute(BFW::Log::_TxtYellowAttribute | BFW::Log::_BkgBlackAttribute); std::wcout << X
#define BFW_PRINT_WARNING_LINE(X) BFW::Log::SetConsoleAttribute(BFW::Log::_TxtYellowAttribute | BFW::Log::_BkgBlackAttribute); std::wcout << X << L'\n'

#define BFW_PRINT_INFO(X) BFW::Log::SetConsoleAttribute(BFW::Log::_TxtGreenAttribute | BFW::Log::_BkgBlackAttribute); std::wcout << X
#define BFW_PRINT_INFO_LINE(X) BFW::Log::SetConsoleAttribute(BFW::Log::_TxtGreenAttribute | BFW::Log::_BkgBlackAttribute); std::wcout << X << L'\n'



#ifdef BFW_DEBUG

#define BFW_LOG(X) BFW::Log::SetConsoleAttribute(BFW::Log::GetDefaultAttribute()); std::wcout << X
#define BFW_LOG_LINE(X) BFW::Log::SetConsoleAttribute(BFW::Log::GetDefaultAttribute()); std::wcout << X << L'\n'

#define BFW_LOG_ERROR(X) BFW::Log::SetConsoleAttribute(BFW::Log::_TxtRedAttribute | BFW::Log::_BkgBlackAttribute); std::wcout << X
#define BFW_LOG_ERROR_LINE(X) BFW::Log::SetConsoleAttribute(BFW::Log::_TxtRedAttribute | BFW::Log::_BkgBlackAttribute); std::wcout << X << L'\n'

#define BFW_LOG_WARNING(X) BFW::Log::SetConsoleAttribute(BFW::Log::_TxtYellowAttribute | BFW::Log::_BkgBlackAttribute); std::wcout << X
#define BFW_LOG_WARNING_LINE(X) BFW::Log::SetConsoleAttribute(BFW::Log::_TxtYellowAttribute | BFW::Log::_BkgBlackAttribute); std::wcout << X << L'\n'

#define BFW_LOG_INFO(X) BFW::Log::SetConsoleAttribute(BFW::Log::_TxtGreenAttribute | BFW::Log::_BkgBlackAttribute); std::wcout << X
#define BFW_LOG_INFO_LINE(X) BFW::Log::SetConsoleAttribute(BFW::Log::_TxtGreenAttribute | BFW::Log::_BkgBlackAttribute); std::wcout << X << L'\n'

#endif

#ifndef BFW_DEBUG

#define BFW_LOG(X)
#define BFW_LOG_LINE(X)

#define BFW_LOG_ERROR(X)
#define BFW_LOG_ERROR_LINE(X)

#define BFW_LOG_WARNING(X)
#define BFW_LOG_WARNING_LINE(X)

#define BFW_LOG_INFO(X)
#define BFW_LOG_INFO_LINE(X)

#endif



#define BFW_PRINT_OUTPUT_DEBUG_STR_A(X) OutputDebugStringA(X)
#define BFW_PRINT_OUTPUT_DEBUG_STR_W(X) OutputDebugStringW(X)
#define BFW_PRINT_OUTPUT_DEBUG_STR_LINE_A(X) OutputDebugStringA(X); OutputDebugStringA("\n")
#define BFW_PRINT_OUTPUT_DEBUG_STR_LINE_W(X) OutputDebugStringW(X); OutputDebugStringW(L"\n")

#ifdef _UNICODE

#define BFW_PRINT_OUTPUT_DEBUG_STR(X) BFW_PRINT_OUTPUT_DEBUG_STR_W(X)
#define BFW_PRINT_OUTPUT_DEBUG_STR_LINE(X) BFW_PRINT_OUTPUT_DEBUG_STR_LINE_W(X)

#endif

#ifndef _UNICODE

#define BFW_PRINT_OUTPUT_DEBUG_STR(X) BFW_PRINT_OUTPUT_DEBUG_STR_A(X)
#define BFW_PRINT_OUTPUT_DEBUG_STR_LINE(X) BFW_PRINT_OUTPUT_DEBUG_STR_LINE_A(X)

#endif



#ifdef BFW_DEBUG

#define BFW_LOG_OUTPUT_DEBUG_STR_A(X) OutputDebugStringA(X)
#define BFW_LOG_OUTPUT_DEBUG_STR_W(X) OutputDebugStringW(X)
#define BFW_LOG_OUTPUT_DEBUG_STR_LINE_A(X) OutputDebugStringA(X); OutputDebugStringA("\n")
#define BFW_LOG_OUTPUT_DEBUG_STR_LINE_W(X) OutputDebugStringW(X); OutputDebugStringW(L"\n")

#ifdef _UNICODE

#define BFW_LOG_OUTPUT_DEBUG_STR(X) BFW_LOG_OUTPUT_DEBUG_STR_W(X)
#define BFW_LOG_OUTPUT_DEBUG_STR_LINE(X) BFW_LOG_OUTPUT_DEBUG_STR_LINE_W(X)

#endif

#ifndef _UNICODE

#define BFW_LOG_OUTPUT_DEBUG_STR(X) BFW_LOG_OUTPUT_DEBUG_STR_A(X)
#define BFW_LOG_OUTPUT_DEBUG_STR_LINE(X) BFW_LOG_OUTPUT_DEBUG_STR_LINE_A(X)

#endif

#endif

#ifndef BFW_DEBUG

#define BFW_LOG_OUTPUT_DEBUG_STR_A(X)
#define BFW_LOG_OUTPUT_DEBUG_STR_W(X)
#define BFW_LOG_OUTPUT_DEBUG_STR_LINE_A(X)
#define BFW_LOG_OUTPUT_DEBUG_STR_LINE_W(X)
#define BFW_LOG_OUTPUT_DEBUG_STR(X)
#define BFW_LOG_OUTPUT_DEBUG_STR_LINE(X)

#endif



#ifdef BFW_DEBUG

#define BFW_DEBUG_BREAK() __debugbreak()
#define BFW_DEBUG_BREAK_MSG_A(Msg) MessageBoxA(NULL, Msg, "Debug break!", MB_OK | MB_ICONERROR); __debugbreak()
#define BFW_DEBUG_BREAK_MSG_W(Msg) MessageBoxW(NULL, Msg, L"Debug break!", MB_OK | MB_ICONERROR); __debugbreak()

#ifdef _UNICODE

#define BFW_DEBUG_BREAK_MSG(Msg) BFW_DEBUG_BREAK_MSG_W(Msg)

#endif

#ifndef _UNICODE

#define BFW_DEBUG_BREAK_MSG(Msg) BFW_DEBUG_BREAK_MSG_A(Msg)

#endif

#endif

#ifndef BFW_DEBUG

#define BFW_DEBUG_BREAK()
#define BFW_DEBUG_BREAK_MSG_A(Msg)
#define BFW_DEBUG_BREAK_MSG_W(Msg)
#define BFW_DEBUG_BREAK_MSG(Msg)

#endif



#define BFW_COM_RELEASE(X) if (X) X->Release(); X = nullptr



#endif



#ifdef BFW_LINUX_PLATFORM



#ifdef BFW_BUILD_DYNAMIC

#define BFW_API
#define BFW_EXTERN

#endif

#ifdef BFW_LINK_DYNAMIC

#define BFW_API
#define BFW_EXTERN extern

#endif

#ifdef BFW_BUILD_STATIC

#define BFW_API

#endif

#ifdef BFW_LINK_STATIC

#define BFW_API

#endif

#ifdef BFW_VENDOR

#define BFW_API

#endif



#define BFW_PRINT(X) BFW::Log::SetConsoleAttribute(BFW::Log::_TxtWhiteAttribute | BFW::Log::_BkgBlackAttribute); std::wcout << X
#define BFW_PRINT_LINE(X) BFW::Log::SetConsoleAttribute(BFW::Log::_TxtWhiteAttribute | BFW::Log::_BkgBlackAttribute); std::wcout << X << L'\n'

#define BFW_PRINT_ERROR(X) BFW::Log::SetConsoleAttribute(BFW::Log::_TxtRedAttribute | BFW::Log::_BkgBlackAttribute); std::wcout << X
#define BFW_PRINT_ERROR_LINE(X) BFW::Log::SetConsoleAttribute(BFW::Log::_TxtRedAttribute | BFW::Log::_BkgBlackAttribute); std::wcout << X << L'\n'

#define BFW_PRINT_WARNING(X) BFW::Log::SetConsoleAttribute(BFW::Log::_TxtYellowAttribute | BFW::Log::_BkgBlackAttribute); std::wcout << X
#define BFW_PRINT_WARNING_LINE(X) BFW::Log::SetConsoleAttribute(BFW::Log::_TxtYellowAttribute | BFW::Log::_BkgBlackAttribute); std::wcout << X << L'\n'

#define BFW_PRINT_INFO(X) BFW::Log::SetConsoleAttribute(BFW::Log::_TxtGreenAttribute | BFW::Log::_BkgBlackAttribute); std::wcout << X
#define BFW_PRINT_INFO_LINE(X) BFW::Log::SetConsoleAttribute(BFW::Log::_TxtGreenAttribute | BFW::Log::_BkgBlackAttribute); std::wcout << X << L'\n'



#ifdef BFW_DEBUG

#define BFW_LOG(X) BFW::Log::SetConsoleAttribute(BFW::Log::_TxtWhiteAttribute | BFW::Log::_BkgBlackAttribute); std::wcout << X
#define BFW_LOG_LINE(X) BFW::Log::SetConsoleAttribute(BFW::Log::_TxtWhiteAttribute | BFW::Log::_BkgBlackAttribute); std::wcout << X << L'\n'

#define BFW_LOG_ERROR(X) BFW::Log::SetConsoleAttribute(BFW::Log::_TxtRedAttribute | BFW::Log::_BkgBlackAttribute); std::wcout << X
#define BFW_LOG_ERROR_LINE(X) BFW::Log::SetConsoleAttribute(BFW::Log::_TxtRedAttribute | BFW::Log::_BkgBlackAttribute); std::wcout << X << L'\n'

#define BFW_LOG_WARNING(X) BFW::Log::SetConsoleAttribute(BFW::Log::_TxtYellowAttribute | BFW::Log::_BkgBlackAttribute); std::wcout << X
#define BFW_LOG_WARNING_LINE(X) BFW::Log::SetConsoleAttribute(BFW::Log::_TxtYellowAttribute | BFW::Log::_BkgBlackAttribute); std::wcout << X << L'\n'

#define BFW_LOG_INFO(X) BFW::Log::SetConsoleAttribute(BFW::Log::_TxtGreenAttribute | BFW::Log::_BkgBlackAttribute); std::wcout << X
#define BFW_LOG_INFO_LINE(X) BFW::Log::SetConsoleAttribute(BFW::Log::_TxtGreenAttribute | BFW::Log::_BkgBlackAttribute); std::wcout << X << L'\n'

#endif

#ifndef BFW_DEBUG

#define BFW_LOG(X)
#define BFW_LOG_LINE(X)

#define BFW_LOG_ERROR(X)
#define BFW_LOG_ERROR_LINE(X)

#define BFW_LOG_WARNING(X)
#define BFW_LOG_WARNING_LINE(X)

#define BFW_LOG_INFO(X)
#define BFW_LOG_INFO_LINE(X)

#endif



#define BFW_PRINT_OUTPUT_DEBUG_STR_A(X) std::wcout << X
#define BFW_PRINT_OUTPUT_DEBUG_STR_W(X) std::wcout << X
#define BFW_PRINT_OUTPUT_DEBUG_STR_LINE_A(X) std::wcout << X << L'\n'
#define BFW_PRINT_OUTPUT_DEBUG_STR_LINE_W(X) std::wcout << X << L'\n'

#ifdef _UNICODE

#define BFW_PRINT_OUTPUT_DEBUG_STR(X) BFW_PRINT_OUTPUT_DEBUG_STR_W(X)
#define BFW_PRINT_OUTPUT_DEBUG_STR_LINE(X) BFW_PRINT_OUTPUT_DEBUG_STR_LINE_W(X)

#endif

#ifndef _UNICODE

#define BFW_PRINT_OUTPUT_DEBUG_STR(X) BFW_PRINT_OUTPUT_DEBUG_STR_A(X)
#define BFW_PRINT_OUTPUT_DEBUG_STR_LINE(X) BFW_PRINT_OUTPUT_DEBUG_STR_LINE_A(X)

#endif



#ifdef BFW_DEBUG

#define BFW_LOG_OUTPUT_DEBUG_STR_A(X) std::wcout << X
#define BFW_LOG_OUTPUT_DEBUG_STR_W(X) std::wcout << X
#define BFW_LOG_OUTPUT_DEBUG_STR_LINE_A(X) std::wcout << X << L'\n'
#define BFW_LOG_OUTPUT_DEBUG_STR_LINE_W(X) std::wcout << X << L'\n'

#ifdef _UNICODE

#define BFW_LOG_OUTPUT_DEBUG_STR(X) BFW_LOG_OUTPUT_DEBUG_STR_W(X)
#define BFW_LOG_OUTPUT_DEBUG_STR_LINE(X) BFW_LOG_OUTPUT_DEBUG_STR_LINE_W(X)

#endif

#ifndef _UNICODE

#define BFW_LOG_OUTPUT_DEBUG_STR(X) BFW_LOG_OUTPUT_DEBUG_STR_A(X)
#define BFW_LOG_OUTPUT_DEBUG_STR_LINE(X) BFW_LOG_OUTPUT_DEBUG_STR_LINE_A(X)

#endif

#endif

#ifndef BFW_DEBUG

#define BFW_LOG_OUTPUT_DEBUG_STR_A(X)
#define BFW_LOG_OUTPUT_DEBUG_STR_W(X)
#define BFW_LOG_OUTPUT_DEBUG_STR_LINE_A(X)
#define BFW_LOG_OUTPUT_DEBUG_STR_LINE_W(X)
#define BFW_LOG_OUTPUT_DEBUG_STR(X)
#define BFW_LOG_OUTPUT_DEBUG_STR_LINE(X)

#endif



#ifdef BFW_DEBUG

#define BFW_DEBUG_BREAK() __builtin_trap()
#define BFW_DEBUG_BREAK_MSG_A(Msg) std::wcout << L"Debug break! " << Msg << L'\n'; __builtin_trap()
#define BFW_DEBUG_BREAK_MSG_W(Msg) std::wcout << L"Debug break! " << Msg << L'\n'; __builtin_trap()

#ifdef _UNICODE

#define BFW_DEBUG_BREAK_MSG(Msg) BFW_DEBUG_BREAK_MSG_W(Msg)

#endif

#ifndef _UNICODE

#define BFW_DEBUG_BREAK_MSG(Msg) BFW_DEBUG_BREAK_MSG_A(Msg)

#endif

#endif

#ifndef BFW_DEBUG

#define BFW_DEBUG_BREAK()
#define BFW_DEBUG_BREAK_MSG_A(Msg)
#define BFW_DEBUG_BREAK_MSG_W(Msg)
#define BFW_DEBUG_BREAK_MSG(Msg)

#endif



#endif



#ifdef BFW_ESP32_PLATFORM



#ifdef BFW_BUILD_STATIC

#define BFW_API

#endif

#ifdef BFW_LINK_STATIC

#define BFW_API

#endif

#ifdef BFW_VENDOR

#define BFW_API

#endif



#define BFW_PRINT(X) Serial.print(X)
#define BFW_PRINT_LINE(X) Serial.println(X)

#define BFW_PRINT_ERROR(X) Serial.print(X)
#define BFW_PRINT_ERROR_LINE(X) Serial.println(X)

#define BFW_PRINT_WARNING(X) Serial.print(X)
#define BFW_PRINT_WARNING_LINE(X) Serial.println(X)

#define BFW_PRINT_INFO(X) Serial.print(X)
#define BFW_PRINT_INFO_LINE(X) Serial.println(X)



#ifdef BFW_DEBUG

#define BFW_LOG(X) Serial.print(X)
#define BFW_LOG_LINE(X) Serial.println(X)

#define BFW_LOG_ERROR(X) Serial.print(X)
#define BFW_LOG_ERROR_LINE(X) Serial.println(X)

#define BFW_LOG_WARNING(X) Serial.print(X)
#define BFW_LOG_WARNING_LINE(X) Serial.println(X)

#define BFW_LOG_INFO(X) Serial.print(X)
#define BFW_LOG_INFO_LINE(X) Serial.println(X)

#endif

#ifndef BFW_DEBUG

#define BFW_LOG(X)
#define BFW_LOG_LINE(X)

#define BFW_LOG_ERROR(X)
#define BFW_LOG_ERROR_LINE(X)

#define BFW_LOG_WARNING(X)
#define BFW_LOG_WARNING_LINE(X)

#define BFW_LOG_INFO(X)
#define BFW_LOG_INFO_LINE(X)

#endif



#define BFW_PRINT_OUTPUT_DEBUG_STR_A(X) Serial.print(X)
#define BFW_PRINT_OUTPUT_DEBUG_STR_W(X) Serial.print(X)
#define BFW_PRINT_OUTPUT_DEBUG_STR_LINE_A(X) Serial.println(X)
#define BFW_PRINT_OUTPUT_DEBUG_STR_LINE_W(X) Serial.println(X)

#ifdef _UNICODE

#define BFW_PRINT_OUTPUT_DEBUG_STR(X) BFW_PRINT_OUTPUT_DEBUG_STR_W(X)
#define BFW_PRINT_OUTPUT_DEBUG_STR_LINE(X) BFW_PRINT_OUTPUT_DEBUG_STR_LINE_W(X)

#endif

#ifndef _UNICODE

#define BFW_PRINT_OUTPUT_DEBUG_STR(X) BFW_PRINT_OUTPUT_DEBUG_STR_A(X)
#define BFW_PRINT_OUTPUT_DEBUG_STR_LINE(X) BFW_PRINT_OUTPUT_DEBUG_STR_LINE_A(X)

#endif



#ifdef BFW_DEBUG

#define BFW_LOG_OUTPUT_DEBUG_STR_A(X) Serial.print(X)
#define BFW_LOG_OUTPUT_DEBUG_STR_W(X) Serial.print(X)
#define BFW_LOG_OUTPUT_DEBUG_STR_LINE_A(X) Serial.println(X)
#define BFW_LOG_OUTPUT_DEBUG_STR_LINE_W(X) Serial.println(X)

#ifdef _UNICODE

#define BFW_LOG_OUTPUT_DEBUG_STR(X) BFW_LOG_OUTPUT_DEBUG_STR_W(X)
#define BFW_LOG_OUTPUT_DEBUG_STR_LINE(X) BFW_LOG_OUTPUT_DEBUG_STR_LINE_W(X)

#endif

#ifndef _UNICODE

#define BFW_LOG_OUTPUT_DEBUG_STR(X) BFW_LOG_OUTPUT_DEBUG_STR_A(X)
#define BFW_LOG_OUTPUT_DEBUG_STR_LINE(X) BFW_LOG_OUTPUT_DEBUG_STR_LINE_A(X)

#endif

#endif

#ifndef BFW_DEBUG

#define BFW_LOG_OUTPUT_DEBUG_STR_A(X)
#define BFW_LOG_OUTPUT_DEBUG_STR_W(X)
#define BFW_LOG_OUTPUT_DEBUG_STR_LINE_A(X)
#define BFW_LOG_OUTPUT_DEBUG_STR_LINE_W(X)
#define BFW_LOG_OUTPUT_DEBUG_STR(X)
#define BFW_LOG_OUTPUT_DEBUG_STR_LINE(X)

#endif



#ifdef BFW_DEBUG

#define BFW_DEBUG_BREAK() BFW::Log::Mutex->lock(); BFW_LOG("Debug break! "); BFW_LOG("\""); BFW_LOG(__FILE__); BFW_LOG("\" "); BFW_LOG("("); BFW_LOG(__LINE__); BFW_LOG(") "); BFW_LOG_LINE(__FUNCTION__); BFW::Log::Mutex->unlock()
#define BFW_DEBUG_BREAK_MSG_A(Msg) BFW::Log::Mutex->lock(); BFW_LOG("Debug break! "); BFW_LOG("\""); BFW_LOG(__FILE__); BFW_LOG("\" "); BFW_LOG("("); BFW_LOG(__LINE__); BFW_LOG(") "); BFW_LOG(__FUNCTION__); BFW_LOG(" "); BFW_LOG_LINE(Msg); BFW::Log::Mutex->unlock()
#define BFW_DEBUG_BREAK_MSG_W(Msg) BFW::Log::Mutex->lock(); BFW_LOG("Debug break! "); BFW_LOG("\""); BFW_LOG(__FILE__); BFW_LOG("\" "); BFW_LOG("("); BFW_LOG(__LINE__); BFW_LOG(") "); BFW_LOG(__FUNCTION__); BFW_LOG(" "); BFW_LOG_LINE(Msg); BFW::Log::Mutex->unlock()

#ifdef _UNICODE

#define BFW_DEBUG_BREAK_MSG(Msg) BFW_DEBUG_BREAK_MSG_W(Msg)

#endif

#ifndef _UNICODE

#define BFW_DEBUG_BREAK_MSG(Msg) BFW_DEBUG_BREAK_MSG_A(Msg)

#endif

#endif

#ifndef BFW_DEBUG

#define BFW_DEBUG_BREAK()
#define BFW_DEBUG_BREAK_MSG_A(Msg)
#define BFW_DEBUG_BREAK_MSG_W(Msg)
#define BFW_DEBUG_BREAK_MSG(Msg)

#endif



#endif



#ifdef BFW_DEBUG

#define BFW_PROFILE_FUNCTION() BFW::Time::ScopeTimer BFW_CONCATENATE(_ScopeTimer, __LINE__)([](const BFW::Time::Timer& _ScopeTimer, const BFW_CHAR_TYPE* _File, const size_t _Line, const BFW_CHAR_TYPE* _Name) { BFW::Log::ProfilingFileMutex->lock(); BFW::Assets::Json& _Element = BFW::Log::ProfilingJson->GetObjectData().Object[1].GetArray().EmplaceBack(BFW::Assets::Json()); _Element.SetObject(); _Element.GetObjectData().Tags.PushBack("name"); _Element.GetObjectData().Object.EmplaceBack(BFW::Assets::Json()).SetString(BFW_MACHINE_TO_UTF8(_Name, nullptr)); _Element.GetObjectData().Tags.PushBack("cat"); _Element.GetObjectData().Object.EmplaceBack(BFW::Assets::Json()).SetString("function"); _Element.GetObjectData().Tags.PushBack("ph"); _Element.GetObjectData().Object.EmplaceBack(BFW::Assets::Json()).SetString("X"); _Element.GetObjectData().Tags.PushBack("ts"); _Element.GetObjectData().Object.EmplaceBack(BFW::Assets::Json()).SetNumber((float)(BFW::Time::GetTimeStamp(_ScopeTimer.GetBegin()) - BFW::Log::ProfilingStart) / 1000.0f); _Element.GetObjectData().Tags.PushBack("dur"); _Element.GetObjectData().Object.EmplaceBack(BFW::Assets::Json()).SetNumber(_ScopeTimer * 1000000.0f); _Element.GetObjectData().Tags.PushBack("pid"); _Element.GetObjectData().Object.EmplaceBack(BFW::Assets::Json()).SetNumber((float)(BFW_WINDOWS_PLATFORM_CALL(BFW::MultiProcessing::Process::GetCurrentPid()) BFW_LINUX_PLATFORM_CALL(BFW::MultiProcessing::Process::GetCurrentPid()) BFW_ESP32_PLATFORM_CALL(0))); _Element.GetObjectData().Tags.PushBack("tid"); _Element.GetObjectData().Object.EmplaceBack(BFW::Assets::Json()).SetNumber((float)(std::hash<std::thread::id>()(std::this_thread::get_id()))); _Element.GetObjectData().Tags.PushBack("args"); BFW::Assets::Json& _Args = _Element.GetObjectData().Object.EmplaceBack(BFW::Assets::Json()); _Args.SetObject(); _Args.GetObjectData().Tags.PushBack("File"); _Args.GetObjectData().Object.EmplaceBack(BFW::Assets::Json()).SetString(BFW_MACHINE_TO_UTF8(_File, nullptr)); _Args.GetObjectData().Tags.PushBack("Line"); _Args.GetObjectData().Object.EmplaceBack(BFW::Assets::Json()).SetNumber((float)(_Line)); BFW::Log::ProfilingFileMutex->unlock(); }, BFW_STRING_PREFIX(__FILE__), __LINE__, BFW_STRING_PREFIX(__FUNCTION__))
#define BFW_PROFILE_SCOPE(Name) BFW::Time::ScopeTimer BFW_CONCATENATE(_ScopeTimer, __LINE__)([](const BFW::Time::Timer& _ScopeTimer, const BFW_CHAR_TYPE* _File, const size_t _Line, const BFW_CHAR_TYPE* _Name) { BFW::Log::ProfilingFileMutex->lock(); BFW::Assets::Json& _Element = BFW::Log::ProfilingJson->GetObjectData().Object[1].GetArray().EmplaceBack(BFW::Assets::Json()); _Element.SetObject(); _Element.GetObjectData().Tags.PushBack("name"); _Element.GetObjectData().Object.EmplaceBack(BFW::Assets::Json()).SetString(BFW_MACHINE_TO_UTF8(_Name, nullptr)); _Element.GetObjectData().Tags.PushBack("cat"); _Element.GetObjectData().Object.EmplaceBack(BFW::Assets::Json()).SetString("scope"); _Element.GetObjectData().Tags.PushBack("ph"); _Element.GetObjectData().Object.EmplaceBack(BFW::Assets::Json()).SetString("X"); _Element.GetObjectData().Tags.PushBack("ts"); _Element.GetObjectData().Object.EmplaceBack(BFW::Assets::Json()).SetNumber((float)(BFW::Time::GetTimeStamp(_ScopeTimer.GetBegin()) - BFW::Log::ProfilingStart) / 1000.0f); _Element.GetObjectData().Tags.PushBack("dur"); _Element.GetObjectData().Object.EmplaceBack(BFW::Assets::Json()).SetNumber(_ScopeTimer * 1000000.0f); _Element.GetObjectData().Tags.PushBack("pid"); _Element.GetObjectData().Object.EmplaceBack(BFW::Assets::Json()).SetNumber((float)(BFW_WINDOWS_PLATFORM_CALL(BFW::MultiProcessing::Process::GetCurrentPid()) BFW_LINUX_PLATFORM_CALL(BFW::MultiProcessing::Process::GetCurrentPid()) BFW_ESP32_PLATFORM_CALL(0))); _Element.GetObjectData().Tags.PushBack("tid"); _Element.GetObjectData().Object.EmplaceBack(BFW::Assets::Json()).SetNumber((float)(std::hash<std::thread::id>()(std::this_thread::get_id()))); _Element.GetObjectData().Tags.PushBack("args"); BFW::Assets::Json& _Args = _Element.GetObjectData().Object.EmplaceBack(BFW::Assets::Json()); _Args.SetObject(); _Args.GetObjectData().Tags.PushBack("File"); _Args.GetObjectData().Object.EmplaceBack(BFW::Assets::Json()).SetString(BFW_MACHINE_TO_UTF8(_File, nullptr)); _Args.GetObjectData().Tags.PushBack("Line"); _Args.GetObjectData().Object.EmplaceBack(BFW::Assets::Json()).SetNumber((float)(_Line)); BFW::Log::ProfilingFileMutex->unlock(); }, BFW_STRING_PREFIX(__FILE__), __LINE__, Name)
#define BFW_HEAP_PROFILE_PUSH(Pointer, Size) BFW::Debug::HeapProfile.Push(Size, Pointer, BFW_STRING_PREFIX(__FILE__), __LINE__, BFW_STRING_PREFIX(__FUNCTION__))
#define BFW_HEAP_PROFILE_POP(Pointer) BFW::Debug::HeapProfile.Pop(Pointer)

#endif

#ifndef BFW_DEBUG

#define BFW_PROFILE_FUNCTION()
#define BFW_PROFILE_SCOPE(Name)
#define BFW_HEAP_PROFILE_PUSH(Pointer, Size)
#define BFW_HEAP_PROFILE_POP(Pointer)

#endif



#ifdef BFW_DEBUG

#define BFW_ASSERT(Condition) if (!(Condition)) { BFW_DEBUG_BREAK(); }
#define BFW_ASSERT_MSG_A(Condition, Msg) if (!(Condition)) { BFW_DEBUG_BREAK_MSG_A(Msg); }
#define BFW_ASSERT_MSG_W(Condition, Msg) if (!(Condition)) { BFW_DEBUG_BREAK_MSG_W(Msg); }

#ifdef _UNICODE

#define BFW_ASSERT_MSG(Condition, Msg) BFW_ASSERT_MSG_W(Condition, Msg)

#endif

#ifndef _UNICODE

#define BFW_ASSERT_MSG(Condition, Msg) BFW_ASSERT_MSG_A(Condition, Msg)

#endif

#endif

#ifndef BFW_DEBUG

#define BFW_ASSERT(Condition)
#define BFW_ASSERT_MSG_A(Condition, Msg)
#define BFW_ASSERT_MSG_W(Condition, Msg)
#define BFW_ASSERT_MSG(Condition, Msg)

#endif



#endif
