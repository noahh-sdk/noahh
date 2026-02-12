#include <Noahh/loader/Mod.hpp>
#include <Noahh/loader/Loader.hpp>
#include <InternalLoader.hpp>
#include <InternalMod.hpp>
#include <Noahh/loader/Log.hpp>
#include <Noahh/loader/Interface.hpp>
#include "../core/Core.hpp"

int noahhEntry(void* platformData);
// platform-specific entry points

#if defined(NOAHH_IS_IOS) || defined(NOAHH_IS_MACOS)
#include <mach-o/dyld.h>
#include <unistd.h>

std::length_error::~length_error() _NOEXCEPT {} // do not ask...

__attribute__((constructor)) void _entry() {
    char gddir[PATH_MAX];
    uint32_t out = PATH_MAX;
    _NSGetExecutablePath(gddir, &out);

    ghc::filesystem::path gdpath = gddir;
    ghc::filesystem::current_path(gdpath.parent_path().parent_path());

    noahhEntry(nullptr);
}
#elif defined(NOAHH_IS_WINDOWS)
#include <Windows.h>

DWORD WINAPI loadThread(void* arg) {
    return noahhEntry(arg);
}

BOOL WINAPI DllMain(HINSTANCE lib, DWORD reason, LPVOID) {
    switch (reason) {
        case DLL_PROCESS_ATTACH:
            // Prevents threads from notifying this DLL on creation or destruction.
            // Kind of redundant for a game that isn't multi-threaded but will provide
            // some slight optimizations if a mod frequently creates and deletes threads.
            DisableThreadLibraryCalls(lib);

            // loading thread
            HANDLE _ = CreateThread(0, 0, loadThread, lib, 0, nullptr);
            if (_) CloseHandle(_);

            break;
    }
    return TRUE;
}
#endif


int noahhEntry(void* platformData) {
    // setup internals

    if (!InternalLoader::get()) {
        InternalLoader::platformMessageBox(
            "Unable to Load Noahh!",
            "There was an unknown fatal error setting up "
            "internal tools and Noahh can not be loaded. "
            "(InternalLoader::get returned nullptr)"
        );
    }

    if (!noahh::core::hook::initialize()) {
        InternalLoader::platformMessageBox(
            "Unable to load Noahh!",
            "There was an unknown fatal error setting up "
            "internal tools and Noahh can not be loaded. "
            "(Unable to set up hook manager)"
        );
    }

    Interface::get()->init(InternalMod::get());

    if (!InternalLoader::get()->setup()) {
        // if we've made it here, Noahh will 
        // be gettable (otherwise the call to 
        // setup would've immediately crashed)

        InternalLoader::platformMessageBox(
            "Unable to Load Noahh!",
            "There was an unknown fatal error setting up "
            "internal tools and Noahh can not be loaded. "
            "(InternalLoader::setup) returned false"
        );
        return 1;
    }

    InternalMod::get()->log()
        << Severity::Debug
        << "Loaded internal Noahh class";

    // set up loader, load mods, etc.
    if (!Loader::get()->setup()) {
        InternalLoader::platformMessageBox(
            "Unable to Load Noahh!",
            "There was an unknown fatal error setting up "
            "the loader and Noahh can not be loaded."
        );
        delete InternalLoader::get();
        return 1;
    }

    InternalMod::get()->log()
        << Severity::Debug
        << "Set up loader";

    // debugging console
    #ifdef NOAHH_PLATFORM_CONSOLE
    InternalMod::get()->log()
        << Severity::Debug
        << "Loading Console...";

    InternalLoader::get()->setupPlatformConsole();
    InternalLoader::get()->awaitPlatformConsole();
    InternalLoader::get()->closePlatformConsole();

    InternalMod::get()->log()
        << Severity::Debug
        << "Cleaning up...";

    //delete InternalLoader::get();
    #endif

    InternalMod::get()->log()
        << Severity::Debug
        << "Entry done.";
        
    return 0;
}