#ifndef NOAHH_CORE_META_DEFAULTCONV_HPP
#define NOAHH_CORE_META_DEFAULTCONV_HPP

namespace noahh::core::meta {
    template <class Ret, class... Args>
    class DefaultConv {
    public:
        static Ret invoke(void* address, Args... all) {
            Ret (*raw)(Args...) = reinterpret_cast<decltype(raw)>(address);
            return raw(all...);
        }

        template <Ret (*detour)(Args...)>
        static constexpr decltype(auto) get_wrapper() {
            return detour;
        }
    };
}

#endif /* NOAHH_CORE_META_DEFAULTCONV_HPP */