#include "../crashlog.hpp"

#ifdef NOAHH_IS_MACOS

bool crashlog::setupPlatformHandler() {
    return false;
}

bool crashlog::didLastLaunchCrash() {
    return false;
}

std::string crashlog::getCrashLogDirectory() {
    return "";
}

#endif