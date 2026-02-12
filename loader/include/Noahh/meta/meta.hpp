#ifndef NOAHH_CORE_META_META_HPP
#define NOAHH_CORE_META_META_HPP

#include "callconv.hpp"
#include "common.hpp"
#include "function.hpp"
#include "preproc.hpp"
#include "defaultconv.hpp"

namespace noahh::core::meta {}
namespace noahh::core::meta::x86 {}

#if defined(NOAHH_IS_WINDOWS)
    #include "cdecl.hpp"
    #include "membercall.hpp"
    #include "optcall.hpp"
    #include "thiscall.hpp"
#endif

#endif /* NOAHH_CORE_META_META_HPP */