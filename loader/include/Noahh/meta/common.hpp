#ifndef NOAHH_CORE_META_COMMON_HPP
#define NOAHH_CORE_META_COMMON_HPP

#include <type_traits>

namespace noahh::core::meta {
    template <class Type, class... Compare>
    static constexpr bool any_of = (std::is_same_v<Type, Compare> || ...);

    template <class... Classes>
    static constexpr bool always_false = false;
}

#endif /* NOAHH_CORE_META_COMMON_HPP */