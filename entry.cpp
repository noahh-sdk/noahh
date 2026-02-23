#include <Noahh/loader/Loader.hpp>
#include <Noahh/loader/Mod.hpp>
#include <Noahh/loader/Log.hpp>
#include <Noahh/utils/async.hpp>

namespace noahh {
    /**
     * To bypass the need for cyclic dependencies,
     * this function does the exact same as Mod::get()
     * However, it can be externed, unlike Mod::get()
     * @returns Same thing Mod::get() returns
     */
    Mod* getMod() {
        return Mod::get();
    }

    ZStringView getModID(Mod* mod) {
        return mod->getID();
    }
}

NOAHH_API void noahhImplicitEntry() {
    // to make sure the instance is set into the sharedMod<> in load time
    auto mod = noahh::getMod();

    // initialize arc runtime
    if (!mod->isInternal()) {
        arc::setGlobalRuntime(&noahh::async::runtime());
    }

    arc::setLogFunction([](auto msg, arc::LogLevel level) {
        using enum arc::LogLevel;

        switch (level) {
            case Warn:
                noahh::log::warn("[arc] {}", msg); break;
            case Error:
                noahh::log::error("[arc] {}", msg); break;
            default:
                // log::debug("[arc] {}", msg); break;
        }
    });
}

#if defined(_DEBUG) && defined(NOAHH_IS_WINDOWS)

// This bypasses any of the heap validation measures that are injected when compiling in Debug.
// Without these, the game will very likely crash when the mod tries to free memory allocated by the game (or another non-debug mod).

static inline void* relallocthrow(size_t size) {
    void* p;
    while ((p = HeapAlloc(GetProcessHeap(), 0, size)) == 0) {
        if (_callnewh(size) == 0) {
            static const std::bad_alloc exc;
            throw exc;
        }
    }

    return p;
}

static inline void relfree(void* block) {
    HeapFree(GetProcessHeap(), 0, block);
}

void* operator new(size_t size) {
    return relallocthrow(size);
}

void* operator new[](size_t size) {
    return relallocthrow(size);
}

void operator delete(void* block) noexcept {
    relfree(block);
}

#endif


