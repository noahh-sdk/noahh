#pragma once

#include "cplatform.h"
#include <string>
#include <functional>
#include <memory>

#if !defined(__PRETTY_FUNCTION__) && !defined(__GNUC__)
    #define NOAHH_PRETTY_FUNCTION std::string(__FUNCSIG__)
#else
    #define NOAHH_PRETTY_FUNCTION std::string(__PRETTY_FUNCTION__)
#endif

#define NOAHH_WRAPPER_STR(...) #__VA_ARGS__
#define NOAHH_STR(...) NOAHH_WRAPPER_STR(__VA_ARGS__)

#if defined (_MSC_VER) && !defined(__clang__)
    #define NOAHH_CXX_STANDARD _MSVC_LANG
#else
    #define NOAHH_CXX_STANDARD __cplusplus
#endif

static_assert(
    NOAHH_CXX_STANDARD >= 202302L,
    "\n\nError: Noahh requires C++23 support to build! (" NOAHH_STR(NOAHH_CXX_STANDARD) " < 202302L)\n"
    "Please modify your CMakeLists.txt and change CMAKE_CXX_STANDARD from 20 to 23.\n"
    "If you're using an outdated compiler that doesn't support C++23, please update it.\n\n"
);

// Windows
#ifdef NOAHH_IS_WINDOWS

    #define NOAHH_HIDDEN
    #define NOAHH_INLINE __forceinline
    #define NOAHH_VIRTUAL_CONSTEXPR
    #define NOAHH_NOINLINE __declspec(noinline)

    #ifdef NOAHH_EXPORTING
        #define NOAHH_DLL __declspec(dllexport)
    #else
        #define NOAHH_DLL __declspec(dllimport)
    #endif

    #define NOAHH_API extern "C" __declspec(dllexport)
    #define NOAHH_EXPORT __declspec(dllexport)
    #define NOAHH_NO_UNIQUE_ADDRESS [[msvc::no_unique_address]]

    #if defined(NOAHH_IS_WINDOWS64)
        #define NOAHH_IS_X64
        #define NOAHH_CDECL_CALL
    #else
        #define NOAHH_IS_X86
        #define NOAHH_CDECL_CALL __cdecl
	#endif

    #include "windows.hpp"

#elif defined(NOAHH_IS_MACOS)

    #define NOAHH_HIDDEN __attribute__((visibility("hidden")))
    #define NOAHH_INLINE __attribute__((always_inline))
    #define NOAHH_VIRTUAL_CONSTEXPR constexpr
    #define NOAHH_NOINLINE __attribute__((noinline))

    #ifdef NOAHH_EXPORTING
        #define NOAHH_DLL __attribute__((visibility("default")))
    #else
        #define NOAHH_DLL
    #endif

    #define NOAHH_API extern "C" __attribute__((visibility("default")))
    #define NOAHH_EXPORT __attribute__((visibility("default")))
    #define NOAHH_NO_UNIQUE_ADDRESS [[no_unique_address]]

    #define NOAHH_IS_X64
    #define NOAHH_CDECL_CALL

    #include "macos.hpp"

#elif defined(NOAHH_IS_IOS)

    #define NOAHH_HIDDEN __attribute__((visibility("hidden")))
    #define NOAHH_INLINE __attribute__((always_inline))
    #define NOAHH_VIRTUAL_CONSTEXPR constexpr
    #define NOAHH_NOINLINE __attribute__((noinline))

    #ifdef NOAHH_EXPORTING
        #define NOAHH_DLL __attribute__((visibility("default")))
    #else
        #define NOAHH_DLL
    #endif

    #define NOAHH_API extern "C" __attribute__((visibility("default")))
    #define NOAHH_EXPORT __attribute__((visibility("default")))
    #define NOAHH_NO_UNIQUE_ADDRESS [[no_unique_address]]

    #define NOAHH_IS_X64
    #define NOAHH_CDECL_CALL

    #include "ios.hpp"

#elif defined(NOAHH_IS_ANDROID)

    #define NOAHH_HIDDEN __attribute__((visibility("hidden")))
    #define NOAHH_INLINE __attribute__((always_inline))
    #define NOAHH_VIRTUAL_CONSTEXPR constexpr
    #define NOAHH_NOINLINE __attribute__((noinline))

    #ifdef NOAHH_EXPORTING
        #define NOAHH_DLL __attribute__((visibility("default")))
    #else
        #define NOAHH_DLL
    #endif

    #define NOAHH_API extern "C" __attribute__((visibility("default")))
    #define NOAHH_EXPORT __attribute__((visibility("default")))
    #define NOAHH_NO_UNIQUE_ADDRESS [[no_unique_address]]

    #if defined(NOAHH_IS_ANDROID64)
        #define NOAHH_IS_X64
    #else
        #define NOAHH_IS_X86
    #endif
    #define NOAHH_CDECL_CALL

    #include "android.hpp"

#else

    #error "Unsupported Platform!"

#endif

namespace noahh {
    class PlatformID {
    public:
        enum {
            Unknown    = 0b000000,
            Windows    = 0b000001,
            Android32  = 0b000010,
            Android64  = 0b000100,
            MacIntel   = 0b001000,
            MacArm     = 0b010000,
            iOS        = 0b100000,
            Android    = Android32 | Android64,
            Mac        = MacIntel | MacArm,
            Apple      = Mac | iOS,
            X64        = MacIntel | Windows,
            X86        = Unknown,
            ArmV7      = Android32,
            ArmV8      = Android64 | MacArm | iOS,
            Desktop    = Windows | Mac,
            Mobile     = Android | iOS,
            All        = Desktop | Mobile,
        };

        using Type = decltype(Unknown);

        Type m_value;

        constexpr PlatformID(Type t) {
            m_value = t;
        }

        constexpr PlatformID& operator=(Type t) {
            m_value = t;
            return *this;
        }

        constexpr bool operator==(int other) const {
            return m_value == other;
        }

        constexpr bool operator==(PlatformID const& other) const {
            return m_value == other.m_value;
        }

        constexpr bool operator<(PlatformID const& other) const {
            return m_value < other.m_value;
        }

        constexpr bool operator>(PlatformID const& other) const {
            return m_value > other.m_value;
        }

        constexpr operator int() const {
            return m_value;
        }

        /**
         * Parse string into PlatformID. String should be all-lowercase, for
         * example "windows" or "linux"
         */
        static NOAHH_DLL PlatformID from(std::string_view str);

        /**
         * Determines if a given platform string "covers" the given platform.
         * For example, "android" is covered by Platform::Android32 and Platform::Android64.
         * Input string must follow the format in PlatformID::toShortString.
         */
        static NOAHH_DLL bool coveredBy(std::string_view str, PlatformID t);

        static NOAHH_DLL std::string_view toString(Type lp);

        static NOAHH_DLL std::string_view toShortString(Type lp, bool ignoreArch = false);

        template <class T>
            requires requires(T t) {
                static_cast<Type>(t);
            }
        constexpr static PlatformID from(T t) {
            return static_cast<Type>(t);
        }

        template <class T>
            requires requires(Type t) {
                static_cast<T>(t);
            }
        constexpr T to() const {
            return static_cast<T>(m_value);
        }
    };
}

namespace std {
    template <>
    struct hash<noahh::PlatformID> {
        inline std::size_t operator()(noahh::PlatformID const& id) const {
            return std::hash<noahh::PlatformID::Type>()(id.m_value);
        }
    };
}

#ifdef NOAHH_IS_WINDOWS
    #define NOAHH_PLATFORM_TARGET PlatformID::Windows
#elif defined(NOAHH_IS_ARM_MAC)
    #define NOAHH_PLATFORM_TARGET PlatformID::MacArm
#elif defined(NOAHH_IS_INTEL_MAC)
    #define NOAHH_PLATFORM_TARGET PlatformID::MacIntel
#elif defined(NOAHH_IS_IOS)
    #define NOAHH_PLATFORM_TARGET PlatformID::iOS
#elif defined(NOAHH_IS_ANDROID32)
    #define NOAHH_PLATFORM_TARGET PlatformID::Android32
#elif defined(NOAHH_IS_ANDROID64)
    #define NOAHH_PLATFORM_TARGET PlatformID::Android64
#endif

// this is cross-platform so not duplicating it across the typeinfo_cast definitions
namespace noahh::cast {
    template<class T, class U>
    std::shared_ptr<T> typeinfo_pointer_cast(std::shared_ptr<U> const& r) noexcept {
        // https://en.cppreference.com/w/cpp/memory/shared_ptr/pointer_cast
        auto p = typeinfo_cast<typename std::shared_ptr<T>::element_type*>(r.get());
        return std::shared_ptr<T>(r, p);
    }
}

