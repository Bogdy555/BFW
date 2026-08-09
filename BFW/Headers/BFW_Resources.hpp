#ifndef BFW_Resources_hpp

#define BFW_Resources_hpp



#define BFW_VERSION_LIST 1, 0, 0, 0



#define BFW_VERSION_STRING_A "1.0.0.0"
#define BFW_VERSION_STRING_W L"1.0.0.0"

#ifdef _UNICODE

#define BFW_VERSION_STRING BFW_VERSION_STRING_W

#endif

#ifndef _UNICODE

#define BFW_VERSION_STRING BFW_VERSION_STRING_A

#endif



#define BFW_APP_NAME_A "BFW"
#define BFW_APP_NAME_W L"BFW"

#ifdef _UNICODE

#define BFW_APP_NAME BFW_APP_NAME_W

#endif

#ifndef _UNICODE

#define BFW_APP_NAME BFW_APP_NAME_A

#endif



#if defined BFW_BUILD_DYNAMIC || defined BFW_LINK_DYNAMIC

#ifdef BFW_WINDOWS_PLATFORM

#define BFW_FILE_NAME_A "BFW_DYNAMIC.dll"
#define BFW_FILE_NAME_W L"BFW_DYNAMIC.dll"

#ifdef _UNICODE

#define BFW_FILE_NAME BFW_FILE_NAME_W

#endif

#ifndef _UNICODE

#define BFW_FILE_NAME BFW_FILE_NAME_A

#endif

#endif

#ifdef BFW_LINUX_PLATFORM

#define BFW_FILE_NAME_A "libBFW_DYNAMIC.so"
#define BFW_FILE_NAME_W L"libBFW_DYNAMIC.so"

#ifdef _UNICODE

#define BFW_FILE_NAME BFW_FILE_NAME_W

#endif

#ifndef _UNICODE

#define BFW_FILE_NAME BFW_FILE_NAME_A

#endif

#endif

#endif

#if defined BFW_BUILD_STATIC || defined BFW_LINK_STATIC

#ifdef BFW_WINDOWS_PLATFORM

#define BFW_FILE_NAME_A "BFW_STATIC.lib"
#define BFW_FILE_NAME_W L"BFW_STATIC.lib"

#ifdef _UNICODE

#define BFW_FILE_NAME BFW_FILE_NAME_W

#endif

#ifndef _UNICODE

#define BFW_FILE_NAME BFW_FILE_NAME_A

#endif

#endif

#ifdef BFW_LINUX_PLATFORM

#define BFW_FILE_NAME_A "libBFW_STATIC.a"
#define BFW_FILE_NAME_W L"libBFW_STATIC.a"

#ifdef _UNICODE

#define BFW_FILE_NAME BFW_FILE_NAME_W

#endif

#ifndef _UNICODE

#define BFW_FILE_NAME BFW_FILE_NAME_A

#endif

#endif

#ifdef BFW_ESP32_PLATFORM

#define BFW_FILE_NAME_A "BFW_STATIC.a"
#define BFW_FILE_NAME_W L"BFW_STATIC.a"

#ifdef _UNICODE

#define BFW_FILE_NAME BFW_FILE_NAME_W

#endif

#ifndef _UNICODE

#define BFW_FILE_NAME BFW_FILE_NAME_A

#endif

#endif

#endif

#ifdef BFW_VENDOR

#define BFW_FILE_NAME_A "BFW"
#define BFW_FILE_NAME_W L"BFW"

#ifdef _UNICODE

#define BFW_FILE_NAME BFW_FILE_NAME_W

#endif

#ifndef _UNICODE

#define BFW_FILE_NAME BFW_FILE_NAME_A

#endif

#endif



#define BFW_COMPANY_NAME_A "BSW"
#define BFW_COMPANY_NAME_W L"BSW"

#ifdef _UNICODE

#define BFW_COMPANY_NAME BFW_COMPANY_NAME_W

#endif

#ifndef _UNICODE

#define BFW_COMPANY_NAME BFW_COMPANY_NAME_A

#endif



#define BFW_COPY_RIGHT_EN_US_A "Copyright \xC2\xA9 BSW\xE2\x84\xA2. All rights reserved."
#define BFW_COPY_RIGHT_EN_US_W L"Copyright \x00A9 BSW\x2122. All rights reserved."

#ifdef _UNICODE

#define BFW_COPY_RIGHT_EN_US BFW_COPY_RIGHT_EN_US_W

#endif

#ifndef _UNICODE

#define BFW_COPY_RIGHT_EN_US BFW_COPY_RIGHT_EN_US_A

#endif



#ifdef BFW_WINDOWS_PLATFORM

#define BFW_BMP_RESOURCE 256

#define BFW_HDR_RESOURCE 257

#define BFW_WAV_RESOURCE 258

#define BFW_WFOBJ_RESOURCE 259

#define BFW_MTL_RESOURCE 260

#define BFW_GLSL_RESOURCE 261

#define BFW_JSON_RESOURCE 262

#if defined BFW_BUILD_DYNAMIC || defined BFW_LINK_DYNAMIC

#define BFW_IDI_MAIN_ICON 1

#define BFW_IDM_MAIN_MANIFEST 1

#endif

#endif



#endif
