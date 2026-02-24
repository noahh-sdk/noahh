
#include <Noahh/loader/Dirs.hpp>
#include <cocos2d.h>
#include <crashlog.hpp>
#include <filesystem>
#include "LoaderImpl.hpp"

using namespace noahh::prelude;

std::filesystem::path dirs::getNoahhDir() {
    return dirs::getGameDir() / "noahh";
}

std::filesystem::path dirs::getNoahhSaveDir() {
    return dirs::getSaveDir() / "noahh";
}

std::filesystem::path dirs::getNoahhResourcesDir() {
    return dirs::getNoahhDir() / "resources";
}

std::filesystem::path dirs::getNoahhLogDir() {
    return dirs::getNoahhDir() / "logs";
}

std::filesystem::path dirs::getTempDir() {
    return dirs::getNoahhDir() / "temp";
}

std::filesystem::path dirs::getModsDir() {
    return dirs::getNoahhDir() / "mods";
}

std::filesystem::path dirs::getModsSaveDir() {
    return dirs::getNoahhSaveDir() / "mods";
}

std::filesystem::path dirs::getModConfigDir() {
    return dirs::getNoahhDir() / "config";
}

std::filesystem::path dirs::getIndexDir() {
    return dirs::getNoahhDir() / "index";
}

std::filesystem::path dirs::getCrashlogsDir() {
    return crashlog::getCrashLogDirectory();
}

std::filesystem::path dirs::getModPersistentDir() {
    return dirs::getSaveDir() / "noahh-persistent";
}

// std::filesystem::path dirs::getModBinariesDir() {
//     return dirs::getModRuntimeDir() / "binaries";
// }
