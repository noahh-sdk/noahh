#ifndef LILAC_CORE_META_PREPROC_HPP
#define LILAC_CORE_META_PREPROC_HPP

#if !defined(NOAHH_CALL)
    // Windows
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        #define NOAHH_WINDOWS(...) __VA_ARGS__
        #define NOAHH_IS_WINDOWS
        #define NOAHH_IS_DESKTOP
        #define NOAHH_PLATFORM_NAME "Windows"
        #define NOAHH_PLATFORM_TARGET PlatformID::Windows
        #define NOAHH_CALL __stdcall
        #define NOAHH_PLATFORM_EXTENSION ".dll"
    #else
        #define NOAHH_WINDOWS(...)
    #endif

	// Darwin
	#if defined(__APPLE__)
		#include <TargetConditionals.h>
		#if TARGET_OS_IPHONE
			#define NOAHH_MACOS(...)
			#define NOAHH_IOS(...) __VA_ARGS__
			#define NOAHH_IS_IOS
			#define NOAHH_IS_MOBILE
			#define NOAHH_PLATFORM_NAME "iOS"
			#define NOAHH_PLATFORM_TARGET PlatformID::iOS
			#define NOAHH_PLATFORM_EXTENSION ".dylib"
		#else
			#define NOAHH_IOS(...)
			#define NOAHH_MACOS(...) __VA_ARGS__
			#define NOAHH_IS_MACOS
			#define NOAHH_IS_DESKTOP
			#define NOAHH_PLATFORM_NAME "MacOS"
			#define NOAHH_PLATFORM_TARGET PlatformID::MacOS
			#define NOAHH_PLATFORM_EXTENSION ".dylib"
		#endif
		#define NOAHH_CALL
	#else
		#define NOAHH_MACOS(...)
		#define NOAHH_IOS(...)
	#endif

    // Android
    #if defined(__ANDROID__)
        #define NOAHH_ANDROID(...) __VA_ARGS__
        #define NOAHH_IS_ANDROID
        #define NOAHH_IS_MOBILE
        #define NOAHH_PLATFORM_NAME "Android"
        #define NOAHH_PLATFORM_TARGET PlatformID::Android
        #define NOAHH_CALL
        #define NOAHH_PLATFORM_EXTENSION ".so"
    #else
        #define NOAHH_ANDROID(...)
    #endif

    #ifndef NOAHH_PLATFORM_NAME
        #error "Unsupported PlatformID!"
    #endif

    #ifdef NOAHH_EXPORTING
        #define NOAHH_DLL NOAHH_WINDOWS(__declspec(dllexport))
    #else
        #define NOAHH_DLL NOAHH_WINDOWS(__declspec(dllimport))
    #endif
    #define NOAHH_API NOAHH_WINDOWS() // idk where this is
#endif

#endif /* LILAC_CORE_META_PREPROC_HPP */