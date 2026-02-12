#ifndef NOAHH_CORE_META_CDECL_HPP
#define NOAHH_CORE_META_CDECL_HPP

namespace noahh::core::meta::x86 {
    template <class Ret, class... Args>
    class Cdecl {
    private:
        template <Ret (*detour)(Args...)>
        static Ret __cdecl wrapper(Args... all) {
            return detour(all...);
        }

    public:
        static Ret invoke(void* address, Args... all) {
            Ret(__cdecl * raw)(Args...) = reinterpret_cast<decltype(raw)>(address);
            return raw(all...);
        }

        template <Ret (*detour)(Args...)>
        static constexpr decltype(auto) get_wrapper() {
            return &wrapper<detour>;
        }
    };
}

#endif /* NOAHH_CORE_META_THISCALL_HPP */