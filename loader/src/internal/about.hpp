#pragma once

#include <Noahh/utils/VersionInfo.hpp>

namespace about {
    NOAHH_DLL noahh::VersionInfo getLoaderVersion();
    NOAHH_DLL const char* getLoaderVersionStr();
    NOAHH_DLL const char* getLoaderCommitHash();
    NOAHH_DLL const char* getBindingsCommitHash();
    NOAHH_DLL const char* getLoaderModJson();
};

