#pragma once

#include <type_traits>

namespace noahh {
    template <class T>
    NOAHH_INLINE inline void doNotOptimize(T const& value) {
        asm volatile("" : : "r,m"(value) : "memory");
    }

    template <class T>
    NOAHH_INLINE inline void doNotOptimize(T& value) {
        asm volatile("" : "+r,m"(value) : : "memory");
    }

    template <class T>
    NOAHH_INLINE inline void doNotOptimize(T&& value) {
        asm volatile("" : "+r,m"(value) : : "memory");
    }
}
