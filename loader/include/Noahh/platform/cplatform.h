#pragma once

#define NOAHH_C_DLL
#define NOAHH_C_API

#ifdef _MSC_VER
#pragma warning(disable: 4099) // type first seen as class
#pragma warning(default: 4067)
#pragma warning(disable: 4251) // dll-interface
#pragma warning(disable: 4244) // narrowing conversion
#endif


// Set dllexport/dllimport to noahh classes & functions

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	#define NOAHH_WINDOWS(...) __VA_ARGS__
	#define NOAHH_IS_WINDOWS
	#define NOAHH_IS_DESKTOP
	#define NOAHH_PLATFORM_NAME "Windows"
	#define NOAHH_CALL __stdcall
	#define NOAHH_PLATFORM_EXTENSION ".dll"
	
	#ifdef NOAHH_EXPORTING
		#undef NOAHH_C_DLL
	    #define NOAHH_C_DLL  __declspec(dllexport)
	#else
		#undef NOAHH_C_DLL
	    #define NOAHH_C_DLL  __declspec(dllimport)
	#endif
	#undef NOAHH_C_API
	#define NOAHH_C_API __declspec(dllexport) __stdcall
#else
	#define NOAHH_WINDOWS(...)
#endif

#if defined(__APPLE__)
	#include <TargetConditionals.h>
	#if TARGET_OS_IPHONE
		#define NOAHH_MACOS(...)
		#define NOAHH_IOS(...) __VA_ARGS__
		#define NOAHH_IS_IOS
		#define NOAHH_IS_MOBILE
		#define NOAHH_PLATFORM_NAME "iOS"
		#define NOAHH_PLATFORM_EXTENSION ".dylib"
	#else
		#define NOAHH_IOS(...)
		#define NOAHH_MACOS(...) __VA_ARGS__
		#define NOAHH_IS_MACOS
		#define NOAHH_IS_DESKTOP
		#define NOAHH_PLATFORM_NAME "MacOS"
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
	#define NOAHH_CALL
	#define NOAHH_PLATFORM_EXTENSION ".so"
#else
	#define NOAHH_ANDROID(...)
#endif

#ifndef NOAHH_PLATFORM_NAME
	#error "Unsupported PlatformID!"
#endif