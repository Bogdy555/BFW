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



#define BFW_CHAR_TYPE_A char
#define BFW_CHAR_TYPE_W wchar_t
#define BFW_STRING_TYPE_A std::string
#define BFW_STRING_TYPE_W std::wstring
#define BFW_TO_STRING_A(X) std::to_string(X)
#define BFW_TO_STRING_W(X) std::to_wstring(X)
#define BFW_TO_STRING_PTR_A(X) std::to_string(X).c_str()
#define BFW_TO_STRING_PTR_W(X) std::to_wstring(X).c_str()
#define BFW_STRING_PREFIX_A(X) X
#define BFW_STRING_PREFIX_W(X) L ## X

#ifdef _UNICODE

#define BFW_CHAR_TYPE BFW_CHAR_TYPE_W
#define BFW_STRING_TYPE BFW_STRING_TYPE_W
#define BFW_TO_STRING(X) BFW_TO_STRING_W(X)
#define BFW_TO_STRING_PTR(X) BFW_TO_STRING_PTR_W(X)
#define BFW_STRING_PREFIX(X) BFW_STRING_PREFIX_W(X)

#endif

#ifndef _UNICODE

#define BFW_CHAR_TYPE BFW_CHAR_TYPE_A
#define BFW_STRING_TYPE BFW_STRING_TYPE_A
#define BFW_TO_STRING(X) BFW_TO_STRING_A(X)
#define BFW_TO_STRING_PTR(X) BFW_TO_STRING_PTR_A(X)
#define BFW_STRING_PREFIX(X) BFW_STRING_PREFIX_A(X)

#endif



#define BFW_PRINT(X) std::wcout << X
#define BFW_PRINT_LINE(X) std::wcout << X << L'\n'



#ifdef BFW_DEBUG

#define BFW_LOG(X) std::wcout << X
#define BFW_LOG_LINE(X) std::wcout << X << L'\n'

#endif

#ifndef BFW_DEBUG

#define BFW_LOG(X)
#define BFW_LOG_LINE(X)

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

#define BFW_PROFILE_SCOPE() BFW_LOG("Push "); BFW_LOG("\""); BFW_LOG(__FILE__); BFW_LOG("\" "); BFW_LOG("("); BFW_LOG(__LINE__); BFW_LOG(") "); BFW_LOG_LINE(__FUNCTION__); BFW::Time::ScopeTimer _ScopeTimer([](const float _ScopeTime) { BFW_LOG("Pop "); BFW_LOG_LINE(_ScopeTime); })
#define BFW_HEAP_PROFILE_PUSH(Size, Pointer) BFW::Debug::HeapProfile.Push(Size, Pointer)
#define BFW_HEAP_PROFILE_POP(Pointer) BFW::Debug::HeapProfile.Pop(Pointer)

#endif

#ifndef BFW_DEBUG

#define BFW_PROFILE_SCOPE()
#define BFW_HEAP_PROFILE_PUSH(Size, Pointer)
#define BFW_HEAP_PROFILE_POP(Pointer)

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



#define BFW_CHAR_TYPE_A char
#define BFW_CHAR_TYPE_W wchar_t
#define BFW_STRING_TYPE_A std::string
#define BFW_STRING_TYPE_W std::wstring
#define BFW_TO_STRING_A(X) std::to_string(X)
#define BFW_TO_STRING_W(X) std::to_wstring(X)
#define BFW_TO_STRING_PTR_A(X) std::to_string(X).c_str()
#define BFW_TO_STRING_PTR_W(X) std::to_wstring(X).c_str()
#define BFW_STRING_PREFIX_A(X) X
#define BFW_STRING_PREFIX_W(X) L ## X

#ifdef _UNICODE

#define BFW_CHAR_TYPE BFW_CHAR_TYPE_W
#define BFW_STRING_TYPE BFW_STRING_TYPE_W
#define BFW_TO_STRING(X) BFW_TO_STRING_W(X)
#define BFW_TO_STRING_PTR(X) BFW_TO_STRING_PTR_W(X)
#define BFW_STRING_PREFIX(X) BFW_STRING_PREFIX_W(X)

#endif

#ifndef _UNICODE

#define BFW_CHAR_TYPE BFW_CHAR_TYPE_A
#define BFW_STRING_TYPE BFW_STRING_TYPE_A
#define BFW_TO_STRING(X) BFW_TO_STRING_A(X)
#define BFW_TO_STRING_PTR(X) BFW_TO_STRING_PTR_A(X)
#define BFW_STRING_PREFIX(X) BFW_STRING_PREFIX_A(X)

#endif



#define BFW_PRINT(X) std::wcout << X
#define BFW_PRINT_LINE(X) std::wcout << X << L'\n'



#ifdef BFW_DEBUG

#define BFW_LOG(X) std::wcout << X
#define BFW_LOG_LINE(X) std::wcout << X << L'\n'

#endif

#ifndef BFW_DEBUG

#define BFW_LOG(X)
#define BFW_LOG_LINE(X)

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

#define BFW_PROFILE_SCOPE() BFW_LOG("Push "); BFW_LOG("\""); BFW_LOG(__FILE__); BFW_LOG("\" "); BFW_LOG("("); BFW_LOG(__LINE__); BFW_LOG(") "); BFW_LOG_LINE(__FUNCTION__); BFW::Time::ScopeTimer _ScopeTimer([](const float _ScopeTime) { BFW_LOG("Pop "); BFW_LOG_LINE(_ScopeTime); })
#define BFW_HEAP_PROFILE_PUSH(Size, Pointer) BFW::Debug::HeapProfile.Push(Size, Pointer)
#define BFW_HEAP_PROFILE_POP(Pointer) BFW::Debug::HeapProfile.Pop(Pointer)

#endif

#ifndef BFW_DEBUG

#define BFW_PROFILE_SCOPE()
#define BFW_HEAP_PROFILE_PUSH(Size, Pointer)
#define BFW_HEAP_PROFILE_POP(Pointer)

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



#define BFW_CHAR_TYPE_A char
#define BFW_CHAR_TYPE_W wchar_t
#define BFW_STRING_TYPE_A std::string
#define BFW_STRING_TYPE_W std::wstring
#define BFW_TO_STRING_A(X) std::to_string(X)
#define BFW_TO_STRING_W(X) std::to_wstring(X)
#define BFW_TO_STRING_PTR_A(X) std::to_string(X).c_str()
#define BFW_TO_STRING_PTR_W(X) std::to_wstring(X).c_str()
#define BFW_STRING_PREFIX_A(X) X
#define BFW_STRING_PREFIX_W(X) L ## X

#ifdef _UNICODE

#define BFW_CHAR_TYPE BFW_CHAR_TYPE_W
#define BFW_STRING_TYPE BFW_STRING_TYPE_W
#define BFW_TO_STRING(X) BFW_TO_STRING_W(X)
#define BFW_TO_STRING_PTR(X) BFW_TO_STRING_PTR_W(X)
#define BFW_STRING_PREFIX(X) BFW_STRING_PREFIX_W(X)

#endif

#ifndef _UNICODE

#define BFW_CHAR_TYPE BFW_CHAR_TYPE_A
#define BFW_STRING_TYPE BFW_STRING_TYPE_A
#define BFW_TO_STRING(X) BFW_TO_STRING_A(X)
#define BFW_TO_STRING_PTR(X) BFW_TO_STRING_PTR_A(X)
#define BFW_STRING_PREFIX(X) BFW_STRING_PREFIX_A(X)

#endif



#define BFW_PRINT(X) Serial.print(X)
#define BFW_PRINT_LINE(X) Serial.println(X)



#ifdef BFW_DEBUG

#define BFW_LOG(X) Serial.print(X)
#define BFW_LOG_LINE(X) Serial.println(X)

#endif

#ifndef BFW_DEBUG

#define BFW_LOG(X)
#define BFW_LOG_LINE(X)

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

#define BFW_PROFILE_SCOPE() BFW_LOG("Push "); BFW_LOG("\""); BFW_LOG(__FILE__); BFW_LOG("\" "); BFW_LOG("("); BFW_LOG(__LINE__); BFW_LOG(") "); BFW_LOG_LINE(__FUNCTION__); BFW::Time::ScopeTimer _ScopeTimer([](const float _ScopeTime) { BFW_LOG("Pop "); BFW_LOG_LINE(_ScopeTime); })
#define BFW_HEAP_PROFILE_PUSH(Size, Pointer) BFW::Debug::HeapProfile.Push(Size, Pointer)
#define BFW_HEAP_PROFILE_POP(Pointer) BFW::Debug::HeapProfile.Pop(Pointer)

#endif

#ifndef BFW_DEBUG

#define BFW_PROFILE_SCOPE()
#define BFW_HEAP_PROFILE_PUSH(Size, Pointer)
#define BFW_HEAP_PROFILE_POP(Pointer)

#endif



#ifdef BFW_DEBUG

#define BFW_DEBUG_BREAK() BFW_LOG("Debug break! "); BFW_LOG("\""); BFW_LOG(__FILE__); BFW_LOG("\" "); BFW_LOG("("); BFW_LOG(__LINE__); BFW_LOG(") "); BFW_LOG_LINE(__FUNCTION__)
#define BFW_DEBUG_BREAK_MSG_A(Msg) BFW_LOG("Debug break! "); BFW_LOG("\""); BFW_LOG(__FILE__); BFW_LOG("\" "); BFW_LOG("("); BFW_LOG(__LINE__); BFW_LOG(") "); BFW_LOG(__FUNCTION__); BFW_LOG(" "); BFW_LOG_LINE(Msg)
#define BFW_DEBUG_BREAK_MSG_W(Msg) BFW_LOG("Debug break! "); BFW_LOG("\""); BFW_LOG(__FILE__); BFW_LOG("\" "); BFW_LOG("("); BFW_LOG(__LINE__); BFW_LOG(") "); BFW_LOG(__FUNCTION__); BFW_LOG(" "); BFW_LOG_LINE(Msg)

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



#endif
