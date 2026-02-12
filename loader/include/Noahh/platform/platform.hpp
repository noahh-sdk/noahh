#pragma once

#include <functional>

#if defined(NOAHH_CALL)
	#undef NOAHH_CALL
#endif

namespace noahh {
	class PlatformID {
	public:
		enum {
			Unknown = -1,
			Windows,
			MacOS,
			iOS,
			Android,
			Linux,
		};
		
		using Type = decltype(Unknown);

		Type m_value;

		PlatformID(Type t) { m_value = t; }
		PlatformID& operator=(Type t) { m_value = t; return *this; }
		bool operator==(int other) const { return m_value == other; }
		bool operator==(PlatformID const& other) const { return m_value == other.m_value; }
		bool operator<(PlatformID const& other) const { return m_value < other.m_value; }
		bool operator>(PlatformID const& other) const { return m_value > other.m_value; }
		operator int() { return m_value; }

		template<class T>
		static Type cast(T t) {
			return static_cast<Type>(t);
		}

		static constexpr const char* toString(Type lp) {
			switch (lp) {
				case Unknown: return "Unknown";
				case Windows: return "Windows";
				case MacOS:   return "MacOS";
				case iOS:     return "iOS";
				case Android: return "Android";
				case Linux:   return "Linux";
				default: break;
			}
			return "Undefined";
		}
	};
}

namespace std {
    template<>
    struct hash<noahh::PlatformID> {
        inline std::size_t operator()(noahh::PlatformID const& id) const {
			return std::hash<noahh::PlatformID::Type>()(id.m_value);
		}
    };
}

// Windows
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

	#define NOAHH_WINDOWS(...) __VA_ARGS__
	#define NOAHH_IS_WINDOWS
	#define NOAHH_IS_DESKTOP
	#define NOAHH_PLATFORM_NAME "Windows"
	#define NOAHH_PLATFORM_TARGET PlatformID::Windows
	#define NOAHH_CALL __stdcall
	#define NOAHH_HIDDEN
	#define NOAHH_DUPABLE __forceinline
	#define NOAHH_VIRTUAL_CONSTEXPR 
	#define NOAHH_NOINLINE __declspec(noinline)
	#define NOAHH_PLATFORM_EXTENSION ".dll"

	#ifdef NOAHH_EXPORTING
	    #define NOAHH_DLL    __declspec(dllexport)
	#else
	    #define NOAHH_DLL    __declspec(dllimport)
	#endif

	#define NOAHH_API extern "C" __declspec(dllexport)
	#define NOAHH_EXPORT __declspec(dllexport)
	
	#include "windows.hpp"

#else
	#define NOAHH_WINDOWS(...)
#endif

// MacOS / iOS
#if defined(__APPLE__)
#include <TargetConditionals.h>

#if TARGET_OS_IPHONE
	#define NOAHH_MACOS(...)

	#define NOAHH_IOS(...) __VA_ARGS__
	#define NOAHH_IS_IOS
	#define NOAHH_IS_MOBILE
	#define NOAHH_PLATFORM_NAME "iOS"
	#define NOAHH_PLATFORM_TARGET PlatformID::iOS
	#define NOAHH_CALL
	#define NOAHH_HIDDEN __attribute__((visibility("hidden")))
	#define NOAHH_DUPABLE __attribute__((always_inline))
	#define NOAHH_VIRTUAL_CONSTEXPR constexpr
	#define NOAHH_NOINLINE __attribute__((noinline))
	#define NOAHH_PLATFORM_EXTENSION ".dylib"

	#ifdef NOAHH_EXPORTING
	    #define NOAHH_DLL    __attribute__((visibility("default")))
	#else
	    #define NOAHH_DLL    
	#endif

	#define NOAHH_API extern "C" __attribute__((visibility("default")))
	#define NOAHH_EXPORT __attribute__((visibility("default")))

	#include "ios.hpp"

#else
	#define NOAHH_IOS(...)

	#define NOAHH_MACOS(...) __VA_ARGS__
	#define NOAHH_IS_MACOS
	#define NOAHH_IS_DESKTOP
	#define NOAHH_PLATFORM_NAME "MacOS"
	#define NOAHH_PLATFORM_TARGET PlatformID::MacOS
	#define NOAHH_CALL
	#define NOAHH_HIDDEN __attribute__((visibility("hidden")))
	#define NOAHH_DUPABLE __attribute__((always_inline))
	#define NOAHH_VIRTUAL_CONSTEXPR constexpr
	#define NOAHH_NOINLINE __attribute__((noinline))
	#define NOAHH_PLATFORM_EXTENSION ".dylib"

	#ifdef NOAHH_EXPORTING
	    #define NOAHH_DLL    __attribute__((visibility("default")))
	#else
	    #define NOAHH_DLL
	#endif

	#define NOAHH_API extern "C" __attribute__((visibility("default")))
	#define NOAHH_EXPORT __attribute__((visibility("default")))

	#include "macos.hpp"
#endif

#else 
	#define NOAHH_IOS(...)
	#define NOAHH_MACOS(...)

#endif

// Android
#if defined(__ANDROID__)
	#define NOAHH_ANDROID(...) __VA_ARGS__
	#define NOAHH_IS_ANDROID
	#define NOAHH_IS_MOBILE
	#define NOAHH_PLATFORM_NAME "Android"
	#define NOAHH_PLATFORM_TARGET PlatformID::Android
	#define NOAHH_CALL
	#define NOAHH_HIDDEN __attribute__((visibility("hidden")))
	#define NOAHH_DUPABLE __attribute__((always_inline))
	#define NOAHH_VIRTUAL_CONSTEXPR constexpr
	#define NOAHH_NOINLINE __attribute__((noinline))
	#define NOAHH_PLATFORM_EXTENSION ".so"

	#ifdef NOAHH_EXPORTING
	    #define NOAHH_DLL    __attribute__((visibility("default")))
	#else
	    #define NOAHH_DLL    
	#endif

	#define NOAHH_API extern "C" __attribute__((visibility("default")))
	#define NOAHH_EXPORT __attribute__((visibility("default")))

	#include "windows.hpp"

#else
	#define NOAHH_ANDROID(...)
#endif

#ifndef NOAHH_PLATFORM_NAME
	#error "Unsupported PlatformID!"
#endif