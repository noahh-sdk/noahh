#pragma once

#include <Noahh/loader/Event.hpp>
#include <Noahh/loader/Dispatch.hpp>
#include <Noahh/binding/GJGarageLayer.hpp>

using namespace noahh::prelude;

#ifdef NOAHH_IS_WINDOWS
    #ifdef EXPORTING_MOD
        #define NOAHH_TESTDEP_DLL __declspec(dllexport)
    #else
        #define NOAHH_TESTDEP_DLL __declspec(dllimport)
    #endif
#else
    #define NOAHH_TESTDEP_DLL
#endif

#ifdef MY_MOD_ID
    #undef MY_MOD_ID
#endif
#define MY_MOD_ID "noahh.testdep"

namespace api {
    // Important: The function must be declared inline, and return a noahh::Result,
    // as it can fail if the api is not available.
    inline noahh::Result<int> addNumbers(int a, int b) NOAHH_EVENT_EXPORT(&addNumbers, (a, b));

    struct Test {
        noahh::Result<int> addNumbers(int a, int b) NOAHH_EVENT_EXPORT(&Test::addNumbers, (this, a, b));
    };
}

class TestEvent : public Event<TestEvent, bool(std::string_view)> {
public:
    // listener params data
    using Event::Event;
};

using MyDispatchEvent = noahh::Dispatch<GJGarageLayer*>;
