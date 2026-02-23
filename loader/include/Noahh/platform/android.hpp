#pragma once

#include <dlfcn.h>
#include <type_traits>
#include "ItaniumCast.hpp"
#include "clang.hpp"

namespace noahh {
    struct PlatformInfo {
        void* m_so;
    };
}

namespace noahh::base {
    /*NOAHH_NOINLINE inline*/ uintptr_t get();
}


