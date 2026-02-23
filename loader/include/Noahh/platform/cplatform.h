#pragma once

#ifdef _MSC_VER
    #pragma warning(disable : 4099) // type first seen as class
    #pragma warning(default : 4067)
    #pragma warning(disable : 4251) // dll-interface
    #pragma warning(disable : 4244) // narrowing conversion
#endif

// Set dllexport/dllimport to noahh classes & functions

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__) || defined(WIN64) || defined(_WIN64) || defined(__WIN64) && !defined(__CYGWIN__)
    #define NOAHH_WINDOWS(...) __VA_ARGS__
    #define NOAHH_DESKTOP(...) __VA_ARGS__
    #define NOAHH_MOBILE(...)
    #define NOAHH_IS_WINDOWS
    #define NOAHH_IS_DESKTOP
    #define NOAHH_PLATFORM_NAME "Windows"
    #define NOAHH_PLATFORM_EXTENSION ".dll"
    #define NOAHH_PLATFORM_SHORT_IDENTIFIER "win"
    #define NOAHH_PLATFORM_SHORT_IDENTIFIER_NOARCH "win"
    #define CC_TARGET_OS_WIN32

    #if defined(WIN64) || defined(_WIN64) || defined(__WIN64) && !defined(__CYGWIN__)
        #define NOAHH_IS_WINDOWS64
        #define NOAHH_WINDOWS64(...) __VA_ARGS__
        #define NOAHH_WINDOWS32(...)
        #define NOAHH_CALL
    #else
        #define NOAHH_IS_WINDOWS32
        #define NOAHH_WINDOWS32(...) __VA_ARGS__
        #define NOAHH_WINDOWS64(...)
        #define NOAHH_CALL __stdcall
    #endif
#else
    #define NOAHH_WINDOWS(...)
    #define NOAHH_WINDOWS32(...)
    #define NOAHH_WINDOWS64(...)
#endif

#if defined(__APPLE__)
    #include <TargetConditionals.h>
    #if TARGET_OS_IPHONE
        #define NOAHH_MACOS(...)
        #define NOAHH_INTEL_MAC(...)
        #define NOAHH_ARM_MAC(...)
        #define NOAHH_IOS(...) __VA_ARGS__
        #define NOAHH_DESKTOP(...)
        #define NOAHH_MOBILE(...) __VA_ARGS__
        #define NOAHH_IS_IOS
        #define NOAHH_IS_MOBILE
        #define NOAHH_PLATFORM_NAME "iOS"
        #define NOAHH_PLATFORM_EXTENSION ".ios.dylib"
        #define NOAHH_PLATFORM_SHORT_IDENTIFIER "ios"
        #define NOAHH_PLATFORM_SHORT_IDENTIFIER_NOARCH "ios"
        #define CC_TARGET_OS_IPHONE
    #else
        #define NOAHH_IOS(...)
        #define NOAHH_MACOS(...) __VA_ARGS__
        #define NOAHH_DESKTOP(...) __VA_ARGS__
        #define NOAHH_MOBILE(...)
        #define NOAHH_IS_MACOS
        #define NOAHH_IS_DESKTOP
        #define NOAHH_PLATFORM_EXTENSION ".dylib"
        #define NOAHH_PLATFORM_SHORT_IDENTIFIER_NOARCH "mac"
        #define CC_TARGET_OS_MAC

        #if TARGET_CPU_ARM64
            #define NOAHH_PLATFORM_NAME "MacArm"
            #define NOAHH_IS_ARM_MAC
            #define NOAHH_PLATFORM_SHORT_IDENTIFIER "mac-arm"
            #define NOAHH_ARM_MAC(...) __VA_ARGS__
            #define NOAHH_INTEL_MAC(...)
        #else
            #define NOAHH_PLATFORM_NAME "MacIntel"
            #define NOAHH_IS_INTEL_MAC
            #define NOAHH_PLATFORM_SHORT_IDENTIFIER "mac-intel"
            #define NOAHH_ARM_MAC(...)
            #define NOAHH_INTEL_MAC(...) __VA_ARGS__
        #endif
    #endif
    #define NOAHH_CALL
#else
    #define NOAHH_MACOS(...)
    #define NOAHH_IOS(...)
    #define NOAHH_INTEL_MAC(...)
    #define NOAHH_ARM_MAC(...)
#endif

// Android
#if defined(__ANDROID__)
    #define NOAHH_ANDROID(...) __VA_ARGS__
    #define NOAHH_MOBILE(...) __VA_ARGS__
    #define NOAHH_DESKTOP(...)
    #define NOAHH_IS_ANDROID
    #define NOAHH_IS_MOBILE
    #define NOAHH_CALL
    #define CC_TARGET_OS_ANDROID
    #define NOAHH_PLATFORM_SHORT_IDENTIFIER_NOARCH "android"

    #if defined(__arm__)
        #define NOAHH_ANDROID32(...) __VA_ARGS__
		#define NOAHH_ANDROID64(...)
        #define NOAHH_IS_ANDROID32
		#define NOAHH_PLATFORM_NAME "Android32"
        #define NOAHH_PLATFORM_EXTENSION ".android32.so"
        #define NOAHH_PLATFORM_SHORT_IDENTIFIER "android32"
	#elif defined(__aarch64__)
        #define NOAHH_ANDROID32(...)
		#define NOAHH_ANDROID64(...) __VA_ARGS__
        #define NOAHH_IS_ANDROID64
        #define NOAHH_PLATFORM_NAME "Android64"
        #define NOAHH_PLATFORM_EXTENSION ".android64.so"
        #define NOAHH_PLATFORM_SHORT_IDENTIFIER "android64"
    #else
        #define NOAHH_ANDROID32(...)
        #define NOAHH_ANDROID64(...)
	#endif
#else
    #define NOAHH_ANDROID(...)
    #define NOAHH_ANDROID32(...)
    #define NOAHH_ANDROID64(...)
#endif

#ifndef NOAHH_PLATFORM_NAME
    #error "Unsupported PlatformID!"
#endif

