#ifndef BFW_Macros_hpp

#define BFW_Macros_hpp



#if defined BFW_WINDOWS_PLATFORM && defined BFW_ARDUINO_PLATFORM

#error You have to specifie just one platform

#endif



#if !defined BFW_WINDOWS_PLATFORM && !defined BFW_ARDUINO_PLATFORM

#error No platform specified

#endif



#if !defined BFW_DLL_BUILD && !defined BFW_DLL_LINK && !defined BFW_STATIC_BUILD && !defined BFW_STATIC_LINK && !defined BFW_VENDOR

#error No target specified

#endif



#ifdef BFW_DLL_BUILD

#if defined BFW_DLL_LINK || defined BFW_STATIC_BUILD || defined BFW_STATIC_LINK || defined BFW_VENDOR

#error You have to specifie just one target

#endif

#define BFW_API _declspec(dllexport)
#define BFW_EXTERN

#endif



#ifdef BFW_DLL_LINK

#if defined BFW_DLL_BUILD || defined BFW_STATIC_BUILD || defined BFW_STATIC_LINK || defined BFW_VENDOR

#error You have to specifie just one target

#endif

#define BFW_API _declspec(dllimport)
#define BFW_EXTERN extern

#endif



#ifdef BFW_STATIC_BUILD

#if defined BFW_DLL_BUILD || defined BFW_DLL_LINK || defined BFW_STATIC_LINK || defined BFW_VENDOR

#error You have to specifie just one target

#endif

#define BFW_API

#endif



#ifdef BFW_STATIC_LINK

#if defined BFW_DLL_BUILD || defined BFW_DLL_LINK || defined BFW_STATIC_BUILD || defined BFW_VENDOR

#error You have to specifie just one target

#endif

#define BFW_API

#endif



#ifdef BFW_VENDOR

#if defined BFW_DLL_BUILD || defined BFW_DLL_LINK || defined BFW_STATIC_BUILD || defined BFW_STATIC_LINK

#error You have to specifie just one target

#endif

#define BFW_API

#endif



#ifdef BFW_WINDOWS_PLATFORM

#define BFW_WINDOWS_CALL(X) X

#define BFW_ARDUINO_CALL(X)

#endif



#ifdef BFW_ARDUINO_PLATFORM

#define BFW_WINDOWS_CALL(X)

#define BFW_ARDUINO_CALL(X) X

#endif



#ifndef BFW_DEBUG

#define BFW_DEBUG_CALL(X)

#define BFW_RELEASE_CALL(X) X

#endif



#ifdef BFW_DEBUG

#define BFW_DEBUG_CALL(X) X

#define BFW_RELEASE_CALL(X)

#endif



#ifdef BFW_WINDOWS_PLATFORM

#define BFW_COM_RELEASE(X) if(X)\
{\
	X->Release();\
	X = nullptr;\
}

#endif



#endif
