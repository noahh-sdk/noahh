#pragma once

#include <Noahh/Prelude.hpp>
#include <Noahh/c++stl/gdstdlib.hpp>
#include <Noahh/platform/platform.hpp>
#include <variant>

#if defined(NOAHH_EXPOSE_SECRET_INTERNALS_IN_HEADERS_DO_NOT_DEFINE_PLEASE)
    #if !defined(__clang__)
        #error Noahh Loader only compiles with Clang.
    #endif
#endif

#if !defined(NOAHH_CONCAT)
    #define NOAHH_WRAPPER_CONCAT(x, y) x##y
    #define NOAHH_CONCAT(x, y) NOAHH_WRAPPER_CONCAT(x, y)
#endif

#define NOAHH_PAD(size) uint8_t NOAHH_CONCAT(__pad, __LINE__)[size]
#define NOAHH_UNIMPLEMENTED_PAD private:

#define NOAHH_NONINHERITED_MEMBERS private:

#define NOAHH_EXPAND(x) x
#define NOAHH_INVOKE(macro, ...) NOAHH_EXPAND(macro(__VA_ARGS__))

namespace noahh {
    struct ZeroConstructorType {};

    static constexpr auto ZeroConstructor = ZeroConstructorType();

    struct CutoffConstructorType {};

    static constexpr auto CutoffConstructor = CutoffConstructorType();
}

#define NOAHH_CUSTOM_CONSTRUCTOR_BEGIN(Class_) \
    NOAHH_ZERO_CONSTRUCTOR_BEGIN(Class_)       \
    NOAHH_CUTOFF_CONSTRUCTOR_BEGIN(Class_)

#define NOAHH_CUSTOM_CONSTRUCTOR_COCOS(Class_, Base_) \
    NOAHH_ZERO_CONSTRUCTOR(Class_, Base_)             \
    NOAHH_CUTOFF_CONSTRUCTOR_COCOS(Class_, Base_)

#define NOAHH_CUSTOM_CONSTRUCTOR_GD(Class_, Base_) \
    NOAHH_ZERO_CONSTRUCTOR(Class_, Base_)          \
    NOAHH_CUTOFF_CONSTRUCTOR_GD(Class_, Base_)

#define NOAHH_CUSTOM_CONSTRUCTOR_CUTOFF(Class_, Base_) \
    NOAHH_ZERO_CONSTRUCTOR(Class_, Base_)              \
    NOAHH_CUTOFF_CONSTRUCTOR_CUTOFF(Class_, Base_)

#define NOAHH_ZERO_CONSTRUCTOR_BEGIN(Class_)                                              \
    Class_(noahh::ZeroConstructorType, void*) {}                                          \
    Class_(noahh::ZeroConstructorType, size_t fill) :                                     \
        Class_(noahh::ZeroConstructor, std::memset(static_cast<void*>(this), 0, fill)) {} \
    Class_(noahh::ZeroConstructorType) : Class_(noahh::ZeroConstructor, nullptr) {}

#define NOAHH_ZERO_CONSTRUCTOR(Class_, Base_)                                                \
    Class_(noahh::ZeroConstructorType, size_t fill) : Base_(noahh::ZeroConstructor, fill) {} \
    Class_(noahh::ZeroConstructorType) : Base_(noahh::ZeroConstructor, sizeof(Class_)) {}

#define NOAHH_FILL_CONSTRUCTOR(Class_, Offset_)                                          \
    Class_(noahh::CutoffConstructorType, size_t fill) :                                  \
        Class_(                                                                          \
            noahh::CutoffConstructor,                                                    \
            std::memset(reinterpret_cast<std::byte*>(this) + Offset_, 0, fill - Offset_) \
        ) {}                                                                             \
    Class_(noahh::CutoffConstructorType, void*)

#define NOAHH_CUTOFF_CONSTRUCTOR_BEGIN(Class_)                      \
    NOAHH_FILL_CONSTRUCTOR(Class_, 0){}

#define NOAHH_CUTOFF_CONSTRUCTOR_COCOS(Class_, Base_)               \
    Class_(noahh::CutoffConstructorType, size_t fill)               \
    : Base_(noahh::CutoffConstructor, fill){}

#define NOAHH_CUTOFF_CONSTRUCTOR_GD(Class_, Base_)                  \
    Class_(noahh::CutoffConstructorType, size_t fill)               \
    : Base_(noahh::CutoffConstructor, fill) {}

#define NOAHH_CUTOFF_CONSTRUCTOR_CUTOFF(Class_, Base_)              \
    Class_(noahh::CutoffConstructorType, size_t fill)               \
    : Base_(noahh::CutoffConstructor, fill) {}

#define NOAHH_NUMBER_OF_ARGS(...) \
    NOAHH_EXPAND(NOAHH_NUMBER_OF_ARGS_(__VA_ARGS__, NOAHH_NUMBER_SEQUENCE(), ))
#define NOAHH_NUMBER_OF_ARGS_(...) NOAHH_EXPAND(NOAHH_NUMBER_OF_ARGS_N(__VA_ARGS__))
#define NOAHH_NUMBER_OF_ARGS_N( \
    _1,                         \
    _2,                         \
    _3,                         \
    _4,                         \
    _5,                         \
    _6,                         \
    _7,                         \
    _8,                         \
    _9,                         \
    _10,                        \
    _11,                        \
    _12,                        \
    _13,                        \
    _14,                        \
    _15,                        \
    _16,                        \
    _17,                        \
    _18,                        \
    _19,                        \
    _20,                        \
    _21,                        \
    _22,                        \
    _23,                        \
    _24,                        \
    _25,                        \
    _26,                        \
    _27,                        \
    _28,                        \
    _29,                        \
    _30,                        \
    _31,                        \
    _32,                        \
    _33,                        \
    _34,                        \
    _35,                        \
    _36,                        \
    _37,                        \
    _38,                        \
    _39,                        \
    _40,                        \
    _41,                        \
    _42,                        \
    _43,                        \
    _44,                        \
    _45,                        \
    _46,                        \
    _47,                        \
    _48,                        \
    _49,                        \
    _50,                        \
    _51,                        \
    _52,                        \
    _53,                        \
    _54,                        \
    _55,                        \
    _56,                        \
    _57,                        \
    _58,                        \
    _59,                        \
    _60,                        \
    _61,                        \
    _62,                        \
    _63,                        \
    N,                          \
    ...                         \
)                               \
    N
#define NOAHH_NUMBER_SEQUENCE()                                                                 \
    63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, \
        40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, \
        18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0


#ifndef NOAHH_UNITY_NS_ID
#define NOAHH_UNITY_NS_ID _test_no_unity
#endif

#define $execute_base(body1) \
namespace { namespace NOAHH_UNITY_NS_ID {                              \
                                                                       \
struct NOAHH_CONCAT(ExecFuncUnique, __LINE__) {};                      \
template<class>                                                        \
void NOAHH_CONCAT(noahhExecFunction1, __LINE__)();                      \
void NOAHH_CONCAT(noahhExecFunctionI, __LINE__)();                      \
static inline auto NOAHH_CONCAT(Exec, __LINE__) =                      \
    (NOAHH_CONCAT(noahhExecFunction1, __LINE__) < NOAHH_CONCAT(ExecFuncUnique, __LINE__) > (), 0);        \
                                                                       \
}}                                                                     \
                                                                       \
template<class>                                                        \
void NOAHH_UNITY_NS_ID::NOAHH_CONCAT(noahhExecFunction1, __LINE__)() body1 \
                                                                       \
void NOAHH_UNITY_NS_ID::NOAHH_CONCAT(noahhExecFunctionI, __LINE__)()

#define $execute $execute_base({ \
    NOAHH_CONCAT(noahhExecFunctionI, __LINE__)(); \
})

#define NOAHH_FORWARD_COMPAT_DISABLE_HOOKS_INNER(message) \
    if (Loader::get()->isForwardCompatMode()) {           \
        if (strlen(message)) {                            \
            log::warn("[Forward Compat] " message);       \
        }                                                 \
        for (const auto& [_, hook] : self.m_hooks) {      \
            hook->setAutoEnable(false);                   \
        }                                                 \
    }
#define NOAHH_FORWARD_COMPAT_ENABLE_HOOKS_INNER(message)  \
    if (!Loader::get()->isForwardCompatMode()) {          \
        if (strlen(message)) {                            \
            log::warn("[Forward Compat] " message);       \
        }                                                 \
        for (const auto& [_, hook] : self.m_hooks) {      \
            hook->setAutoEnable(false);                   \
        }                                                 \
    }
#define NOAHH_FORWARD_COMPAT_DISABLE_HOOKS(message)       \
    static void onModify(const auto& self) {              \
        NOAHH_FORWARD_COMPAT_DISABLE_HOOKS_INNER(message) \
    }
#define NOAHH_FORWARD_COMPAT_ENABLE_HOOKS(message)        \
    static void onModify(const auto& self) {              \
        NOAHH_FORWARD_COMPAT_ENABLE_HOOKS_INNER(message)  \
    }

// #define NOAHH_NEST1(macro, begin)           \
// macro(NOAHH_CONCAT(begin, 0)),                        \
// macro(NOAHH_CONCAT(begin, 1)),                        \
// macro(NOAHH_CONCAT(begin, 2)),                        \
// macro(NOAHH_CONCAT(begin, 3)),                        \
// macro(NOAHH_CONCAT(begin, 4)),                        \
// macro(NOAHH_CONCAT(begin, 5)),                        \
// macro(NOAHH_CONCAT(begin, 6)),                        \
// macro(NOAHH_CONCAT(begin, 7)),                        \
// macro(NOAHH_CONCAT(begin, 8)),                        \
// macro(NOAHH_CONCAT(begin, 9)),                        \
// macro(NOAHH_CONCAT(begin, a)),                        \
// macro(NOAHH_CONCAT(begin, b)),                        \
// macro(NOAHH_CONCAT(begin, c)),                        \
// macro(NOAHH_CONCAT(begin, d)),                        \
// macro(NOAHH_CONCAT(begin, e)),                        \
// macro(NOAHH_CONCAT(begin, f))

// #define NOAHH_NEST2(macro, begin)           \
// NOAHH_NEST1(macro, NOAHH_CONCAT(begin, 0)), \
// NOAHH_NEST1(macro, NOAHH_CONCAT(begin, 1)), \
// NOAHH_NEST1(macro, NOAHH_CONCAT(begin, 2)), \
// NOAHH_NEST1(macro, NOAHH_CONCAT(begin, 3)), \
// NOAHH_NEST1(macro, NOAHH_CONCAT(begin, 4)), \
// NOAHH_NEST1(macro, NOAHH_CONCAT(begin, 5)), \
// NOAHH_NEST1(macro, NOAHH_CONCAT(begin, 6)), \
// NOAHH_NEST1(macro, NOAHH_CONCAT(begin, 7)), \
// NOAHH_NEST1(macro, NOAHH_CONCAT(begin, 8)), \
// NOAHH_NEST1(macro, NOAHH_CONCAT(begin, 9)), \
// NOAHH_NEST1(macro, NOAHH_CONCAT(begin, a)), \
// NOAHH_NEST1(macro, NOAHH_CONCAT(begin, b)), \
// NOAHH_NEST1(macro, NOAHH_CONCAT(begin, c)), \
// NOAHH_NEST1(macro, NOAHH_CONCAT(begin, d)), \
// NOAHH_NEST1(macro, NOAHH_CONCAT(begin, e)), \
// NOAHH_NEST1(macro, NOAHH_CONCAT(begin, f))

// #define NOAHH_NEST3(macro, begin)           \
// NOAHH_NEST2(macro, NOAHH_CONCAT(begin, 0)), \
// NOAHH_NEST2(macro, NOAHH_CONCAT(begin, 1)), \
// NOAHH_NEST2(macro, NOAHH_CONCAT(begin, 2)), \
// NOAHH_NEST2(macro, NOAHH_CONCAT(begin, 3)), \
// NOAHH_NEST2(macro, NOAHH_CONCAT(begin, 4)), \
// NOAHH_NEST2(macro, NOAHH_CONCAT(begin, 5)), \
// NOAHH_NEST2(macro, NOAHH_CONCAT(begin, 6)), \
// NOAHH_NEST2(macro, NOAHH_CONCAT(begin, 7)), \
// NOAHH_NEST2(macro, NOAHH_CONCAT(begin, 8)), \
// NOAHH_NEST2(macro, NOAHH_CONCAT(begin, 9)), \
// NOAHH_NEST2(macro, NOAHH_CONCAT(begin, a)), \
// NOAHH_NEST2(macro, NOAHH_CONCAT(begin, b)), \
// NOAHH_NEST2(macro, NOAHH_CONCAT(begin, c)), \
// NOAHH_NEST2(macro, NOAHH_CONCAT(begin, d)), \
// NOAHH_NEST2(macro, NOAHH_CONCAT(begin, e)), \
// NOAHH_NEST2(macro, NOAHH_CONCAT(begin, f))

// #define NOAHH_NEST4(macro, begin)           \
// NOAHH_NEST3(macro, NOAHH_CONCAT(begin, 0)), \
// NOAHH_NEST3(macro, NOAHH_CONCAT(begin, 1)), \
// NOAHH_NEST3(macro, NOAHH_CONCAT(begin, 2)), \
// NOAHH_NEST3(macro, NOAHH_CONCAT(begin, 3)), \
// NOAHH_NEST3(macro, NOAHH_CONCAT(begin, 4)), \
// NOAHH_NEST3(macro, NOAHH_CONCAT(begin, 5)), \
// NOAHH_NEST3(macro, NOAHH_CONCAT(begin, 6)), \
// NOAHH_NEST3(macro, NOAHH_CONCAT(begin, 7)), \
// NOAHH_NEST3(macro, NOAHH_CONCAT(begin, 8)), \
// NOAHH_NEST3(macro, NOAHH_CONCAT(begin, 9)), \
// NOAHH_NEST3(macro, NOAHH_CONCAT(begin, a)), \
// NOAHH_NEST3(macro, NOAHH_CONCAT(begin, b)), \
// NOAHH_NEST3(macro, NOAHH_CONCAT(begin, c)), \
// NOAHH_NEST3(macro, NOAHH_CONCAT(begin, d)), \
// NOAHH_NEST3(macro, NOAHH_CONCAT(begin, e)), \
// NOAHH_NEST3(macro, NOAHH_CONCAT(begin, f))

// #define NOAHH_ENUM_OFFSETS_DEFINE(hex) NOAHH_CONCAT($, hex)
// #define NOAHH_ENUM_OFFSETS_SET() NOAHH_NEST4(NOAHH_ENUM_OFFSETS_DEFINE, 0x)

// enum class PrinterOffsets {
//    NOAHH_ENUM_OFFSETS_SET()
// };

