#include <Noahh/DefaultInclude.hpp>

#include <Noahh/loader/Mod.hpp>
#include <loader/ModImpl.hpp>
#include <dlfcn.h>

using namespace noahh::prelude;

template <typename T>
T findSymbolOrMangled(void* dylib, char const* name, char const* mangled) {
    auto res = reinterpret_cast<T>(dlsym(dylib, name));
    if (!res) {
        res = reinterpret_cast<T>(dlsym(dylib, mangled));
    }
    return res;
}

Result<> Mod::Impl::loadPlatformBinary() {
    auto dylib =
        dlopen(utils::string::pathToString(this->getBinaryPath()).c_str(), RTLD_LAZY);
    if (dylib) {
        if (m_platformInfo) {
            delete m_platformInfo;
        }
        m_platformInfo = new PlatformInfo { dylib };

        auto noahhImplicitEntry = findSymbolOrMangled<void(*)()>(dylib, "noahhImplicitEntry", "_Z17noahhImplicitEntryv");
        if (noahhImplicitEntry) {
            noahhImplicitEntry();
        }

        auto noahhCustomEntry = findSymbolOrMangled<void(*)()>(dylib, "noahhCustomEntry", "_Z15noahhCustomEntryv");
        if (noahhCustomEntry) {
            noahhCustomEntry();
        }

        return Ok();
    }
    std::string err = (char const*)dlerror();
    return Err("Unable to load the DYLIB: dlerror returned (" + err + ")");
}

