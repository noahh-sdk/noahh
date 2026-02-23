#pragma once

#include <filesystem>
#include "../DefaultInclude.hpp"

namespace noahh::dirs {
    /**
     * Directory where Geometry Dash is
     *
     * Windows: {GD installation folder}/ (traditionally Geometry Dash)
     * macOS: {GD installation folder}/ (traditionally GeometryDash.app)
     * Android: {Android Launcher's media directory}/game
     * iOS: Documents/game (within the launcher's sandbox)
     */
    NOAHH_DLL std::filesystem::path getGameDir();
    /**
     * Directory where GD saves its files
     *
     * Windows: %LOCALAPPDATA%/{executable name}
     * macOS: ~/Library/Application Support/GeometryDash
     * Android: {Android Launcher's media directory}/save
     * iOS: Documents/save (within the launcher's sandbox)
     */
    NOAHH_DLL std::filesystem::path getSaveDir();
    /**
     * Directory where Noahh is
     * `getGameDir()`/noahh
     */
    NOAHH_DLL std::filesystem::path getNoahhDir();
    /**
     * Directory where Noahh saves its files
     * `getSaveDir()`/noahh
     */
    NOAHH_DLL std::filesystem::path getNoahhSaveDir();
    /**
     * Directory where Noahh's resources are stored
     * `getNoahhDir()`/resources
     */
    NOAHH_DLL std::filesystem::path getNoahhResourcesDir();
    /**
     * Directory where Noahh's logs are stored
     * `getNoahhDir()`/logs
     */
    NOAHH_DLL std::filesystem::path getNoahhLogDir();
    /**
     * Directory to store temporary files
     * `getNoahhDir()`/temp
     */
    NOAHH_DLL std::filesystem::path getTempDir();
    /**
     * Directory where mods are stored by default
     * `getNoahhDir()`/mods
     */
    NOAHH_DLL std::filesystem::path getModsDir();
    /**
     * Directory where mods' save data is stored
     * `getNoahhSaveDir()`/mods
     */
    NOAHH_DLL std::filesystem::path getModsSaveDir();
    /**
     * Directory where mods' unzipped packages are stored at runtime
     *
     * Windows/macOS/iOS: `getNoahhDir()`/unzipped
     * Android: {Android Launcher's internal files directory}/noahh/unzipped
     */
    NOAHH_DLL std::filesystem::path getModRuntimeDir();
    /**
     * Directory where mods' unzipped binary files are stored
     * This is used in order to override existing unzip binaries,
     * such as on iOS where signing the binary is required
     *
     * TODO: enable on ~~4.7.0~~ nice job
     */
    // NOAHH_DLL std::filesystem::path getModBinariesDir();
    /**
     * Directory where mods' config files lie
     * `getNoahhDir()`/config
     */
    NOAHH_DLL std::filesystem::path getModConfigDir();
    /**
     * Directory where Noahh stores the cached index
     * `getNoahhDir()`/index
     */
    NOAHH_DLL std::filesystem::path getIndexDir();
    /**
     * Directory where crashlogs are stored
     * `getNoahhDir()`/crashlogs
     */
    NOAHH_DLL std::filesystem::path getCrashlogsDir();
    /**
     * Directory where mods' persistent files lie
     * This directory is not deleted even when Noahh is uninstalled
     * `getSaveDir()`/noahh-persistent
     */
    NOAHH_DLL std::filesystem::path getModPersistentDir();
    /**
     * Directory where Geometry Dash's resources are stored
     *
     * Windows/macOS: `getGameDir()`/Resources
     * Android: assets
     * iOS: {GD bundle path}/Resources
     */
    NOAHH_DLL std::filesystem::path getResourcesDir();
}

