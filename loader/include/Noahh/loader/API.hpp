#include "Mod.hpp"
#include "Loader.hpp"
#include "Interface.hpp"

#ifdef API_DECL
#undef API_DECL
#endif


#if NOAHH_CONCAT(EXPORT_, EXPORT_NAME)
    #define API_DECL(func, ...) ; static inline auto NOAHH_CONCAT(_dummy, __LINE__) = (noahh::Interface::get()->exportAPIFunction(NOAHH_STR(func), func), 0);
#else
    #define API_DECL(func, ...) \
    {\
        static noahh::Mod* src = noahh::Loader::get()->getLoadedMod(_source);\
    	static auto ptr = noahh::Mod::get()->importAPIFunction<decltype(func)>(NOAHH_STR(func), src);\
    	return std::invoke(ptr, __VA_ARGS__);\
    }
#endif

#ifndef NOAHH_API_HPP
#define NOAHH_API_HPP

#define API_INIT(name) static constexpr auto _source = name;

namespace noahh {
    class NOAHH_DLL ModAPI {};
}
#endif

#undef EXPORT_NAME