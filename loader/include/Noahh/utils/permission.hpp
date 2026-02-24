#pragma once

#include <Noahh/DefaultInclude.hpp>
#include <Noahh/utils/function.hpp>
#include <string_view>

namespace noahh::utils::permission {
    enum class Permission {
        ReadAllFiles = 0x3, // maintain compatibility with some older mods
        RecordAudio
    };

    /**
     * Request whether the given permission is granted to Noahh by the operating system.
     * @param permission The permission
    */
    bool NOAHH_DLL getPermissionStatus(Permission permission);

    /**
     * Request a permission to be granted by the operating system.
     * @param permission The permission
     * @param callback The callback, passed value is 'true' if permission was granted and 'false' otherwise.
     */
    void NOAHH_DLL requestPermission(Permission permission, noahh::Function<void(bool)> callback);
}
