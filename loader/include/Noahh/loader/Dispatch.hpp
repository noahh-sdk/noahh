#pragma once

#include "Event.hpp"
#include "../utils/function.hpp"
#include "../modify/Traits.hpp"
#include <Noahh/utils/function.hpp>
#include <Noahh/utils/StringMap.hpp>

#include <functional>
#include <string>
#include <tuple>

namespace noahh {
    template <class... Args>
    class Dispatch : public ThreadSafeEvent<Dispatch<Args...>, bool(Args...), std::string> {
    public:
        using ThreadSafeEvent<Dispatch<Args...>, bool(Args...), std::string>::ThreadSafeEvent;
    };

    template<class... Args>
    using DispatchEvent = Dispatch<Args...>;

}

// - Macros for exporting functions via events -

// You can use these to easily export functions to other mods
// without being a required dependency.
// # Example Usage:
/*
```
// (In your api distributed header file)
#pragma once

#include <Noahh/loader/Dispatch.hpp>
// You must **manually** declare the mod id, as macros like NOAHH_MOD_ID will not
// behave correctly to other mods using your api.
#define MY_MOD_ID "dev.my-api"

namespace api {
// Important: The function must be declared inline, and return a noahh::Result,
// as it can fail if the api is not available.
inline noahh::Result<int> addNumbers(int a, int b) NOAHH_EVENT_EXPORT(&addNumbers, (a, b));
}
```
*/
// Then, in **one** of your source files, you must define the exported functions:
/*
```
// MUST be defined before including the header.
#define NOAHH_DEFINE_EVENT_EXPORTS
#include "../include/api.hpp"

Result<int> api::addNumbers(int a, int b) {
    return Ok(a + b);
}
```
*/

// once this is set in stone we should not change it ever
#define NOAHH_EVENT_EXPORT_ID_FOR(fnPtrStr, callArgsStr) \
    (std::string(MY_MOD_ID "/") + (fnPtrStr[0] == '&' ? &fnPtrStr[1] : fnPtrStr))

namespace noahh::noahh_internal {
    template <class Fn>
    inline auto callEventExportListener(Fn fnPtr, auto eventID) {
        using StaticType = noahh::modifier::AsStaticType<Fn>::type;
        Fn ptr = nullptr;
        noahh::Dispatch<Fn*>(std::move(eventID)).send(&ptr);
        return noahh::Function<std::remove_pointer_t<StaticType>>(ptr);
    }

    template <class Fn>
    inline bool getEventExportListener(Fn fnPtr, auto eventID) {
        noahh::Dispatch<Fn*>(std::move(eventID)).listen([=](Fn* ptr) {
            *ptr = fnPtr;
            return noahh::ListenerResult::Stop;
        }).leak();
        return true;
    }
}

#define NOAHH_EVENT_EXPORT_CALL(fnPtr, callArgs, eventID)                                       \
    {                                                                                           \
        static auto storage = noahh::noahh_internal::callEventExportListener(fnPtr, eventID);   \
        if (!storage) return noahh::Err("Unable to call method");                               \
        return storage callArgs;                                                                \
    }

#define NOAHH_EVENT_EXPORT_CALL_NORES(fnPtr, callArgs, eventID)                                 \
    {                                                                                           \
        static auto storage = noahh::noahh_internal::callEventExportListener(fnPtr, eventID);   \
        if (!storage) return noahh::utils::function::Return<decltype(fnPtr)>();                \
        return storage callArgs;                                                                \
    }


#define NOAHH_EVENT_EXPORT_DEFINE(fnPtr, callArgs, eventID)                                             \
    ;                                                                                                   \
    template <auto>                                                                                     \
    struct EventExportDefine;                                                                           \
    template <>                                                                                         \
    struct EventExportDefine<noahh::modifier::FunctionUUID<fnPtr>::value> {                             \
        static inline bool val = noahh::noahh_internal::getEventExportListener(fnPtr, eventID);         \
        static inline auto nonOmitted = &val;                                                           \
    };

#ifndef NOAHH_DEFINE_EVENT_EXPORTS

    #define NOAHH_EVENT_EXPORT(fnPtr, callArgs) \
        NOAHH_EVENT_EXPORT_CALL(fnPtr, callArgs, NOAHH_EVENT_EXPORT_ID_FOR(#fnPtr, #callArgs))

    #define NOAHH_EVENT_EXPORT_ID(fnPtr, callArgs, eventID) \
        NOAHH_EVENT_EXPORT_CALL(fnPtr, callArgs, eventID)

    #define NOAHH_EVENT_EXPORT_NORES(fnPtr, callArgs) \
        NOAHH_EVENT_EXPORT_CALL_NORES(fnPtr, callArgs, NOAHH_EVENT_EXPORT_ID_FOR(#fnPtr, #callArgs))

    #define NOAHH_EVENT_EXPORT_ID_NORES(fnPtr, callArgs, eventID) \
        NOAHH_EVENT_EXPORT_CALL_NORES(fnPtr, callArgs, eventID)
#else

    #define NOAHH_EVENT_EXPORT(fnPtr, callArgs) \
        NOAHH_EVENT_EXPORT_DEFINE(fnPtr, callArgs, NOAHH_EVENT_EXPORT_ID_FOR(#fnPtr, #callArgs))

    #define NOAHH_EVENT_EXPORT_ID(fnPtr, callArgs, eventID) \
        NOAHH_EVENT_EXPORT_DEFINE(fnPtr, callArgs, eventID)

    #define NOAHH_EVENT_EXPORT_NORES(fnPtr, callArgs) \
        NOAHH_EVENT_EXPORT(fnPtr, callArgs)

    #define NOAHH_EVENT_EXPORT_ID_NORES(fnPtr, callArgs, eventID) \
        NOAHH_EVENT_EXPORT_ID(fnPtr, callArgs, eventID)
#endif
