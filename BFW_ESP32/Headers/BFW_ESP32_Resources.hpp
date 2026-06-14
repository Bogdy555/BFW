#ifndef BFW_ESP32_Resources_hpp

#define BFW_ESP32_Resources_hpp



#define BFW_ESP32_VERSION_LIST 1, 0, 0, 0



#define BFW_ESP32_VERSION_STRING_A "1.0.0.0"
#define BFW_ESP32_VERSION_STRING_W L"1.0.0.0"

#ifdef _UNICODE

#define BFW_ESP32_VERSION_STRING BFW_ESP32_VERSION_STRING_W

#endif

#ifndef _UNICODE

#define BFW_ESP32_VERSION_STRING BFW_ESP32_VERSION_STRING_A

#endif



#define BFW_ESP32_APP_NAME_A "BFW_ESP32"
#define BFW_ESP32_APP_NAME_W L"BFW_ESP32"

#ifdef _UNICODE

#define BFW_ESP32_APP_NAME BFW_ESP32_APP_NAME_W

#endif

#ifndef _UNICODE

#define BFW_ESP32_APP_NAME BFW_ESP32_APP_NAME_A

#endif



#define BFW_ESP32_FILE_NAME_A "BFW_ESP32.elf"
#define BFW_ESP32_FILE_NAME_W L"BFW_ESP32.elf"

#ifdef _UNICODE

#define BFW_ESP32_FILE_NAME BFW_ESP32_FILE_NAME_W

#endif

#ifndef _UNICODE

#define BFW_ESP32_FILE_NAME BFW_ESP32_FILE_NAME_A

#endif



#define BFW_ESP32_COMPANY_NAME_A "BSW"
#define BFW_ESP32_COMPANY_NAME_W L"BSW"

#ifdef _UNICODE

#define BFW_ESP32_COMPANY_NAME BFW_ESP32_COMPANY_NAME_W

#endif

#ifndef _UNICODE

#define BFW_ESP32_COMPANY_NAME BFW_ESP32_COMPANY_NAME_A

#endif



#define BFW_ESP32_COPY_RIGHT_EN_US_A "Copyright (C) BSW (TM). All rights reserved."
#define BFW_ESP32_COPY_RIGHT_EN_US_W L"Copyright © BSW™. All rights reserved."

#ifdef _UNICODE

#define BFW_ESP32_COPY_RIGHT_EN_US BFW_ESP32_COPY_RIGHT_EN_US_W

#endif

#ifndef _UNICODE

#define BFW_ESP32_COPY_RIGHT_EN_US BFW_ESP32_COPY_RIGHT_EN_US_A

#endif



#endif
