#include <Noahh/DefaultInclude.hpp>
#include <Noahh/loader/Mod.hpp>

using namespace noahh::prelude;

$on_mod(Loaded) {
    // this replaces the call to __dynamic_cast with a call to our own
    // this is needed because the transitions in cocos uses dynamic cast to check
    // layers, which fail on user layers due to typeinfo not matching

    #if defined(NOAHH_IS_MACOS) && NOAHH_COMP_GD_VERSION != 22081
        #error "Unsupported version for macOS dynamic cast fix, please update the addresses"
    #endif
    #if defined(NOAHH_IS_IOS) && NOAHH_COMP_GD_VERSION != 22081
        #error "Unsupported version for iOS dynamic cast fix, please update the addresses"
    #endif

    #if defined(NOAHH_IS_INTEL_MAC)
        void* dynamicCastAddr = reinterpret_cast<void*>(base::get() + 0x7cf4ce);
        (void) Mod::get()->hook(dynamicCastAddr, &cast::typeinfoCastInternal, "__dynamic_cast");
    #elif defined(NOAHH_IS_ARM_MAC)
        void* dynamicCastAddr = reinterpret_cast<void*>(base::get() + 0x6d1dfc);
        (void)Mod::get()->hook(dynamicCastAddr, &cast::typeinfoCastInternal, "__dynamic_cast");
    #elif defined(NOAHH_IS_ANDROID)
        void* handle = dlopen("libcocos2dcpp.so", RTLD_LAZY | RTLD_NOLOAD);
        void* dynamicCastAddr = dlsym(handle, "__dynamic_cast");

        (void)Mod::get()->hook(dynamicCastAddr, &cast::typeinfoCastInternal, "__dynamic_cast");

        dlclose(handle);
    #elif defined(NOAHH_IS_IOS)
        void* addr = reinterpret_cast<void*>(base::get() + 0x7812d8);
        (void) Mod::get()->patch(addr, noahh::toBytes(&cast::typeinfoCastInternal));
    #endif
}

