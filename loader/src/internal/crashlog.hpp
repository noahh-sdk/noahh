#pragma once

#include <Noahh/Loader.hpp>
#include <Noahh/utils/StringBuffer.hpp>
#include <filesystem>
#include <string>

/**
 * Platform-specific crashlog functions. Used by the loader
 */
namespace crashlog {
    using Buffer = noahh::utils::StringBuffer<1>;

    /**
     * Setup platform-specific crashlog handler
     * @returns True if the handler was successfully installed, false otherwise
     */
    bool NOAHH_DLL setupPlatformHandler();

    /**
     * Setup platform-specific crashlog handler for post-launch
     */
    void NOAHH_DLL setupPlatformHandlerPost();

    /**
     * Check if previous launch of GD crashed unexpectedly
     * @returns True if the launch crashed, false otherwise or if indeterminate
     */
    bool NOAHH_DLL didLastLaunchCrash();
    /**
     * Get the directory where crashlogs are saved on the current platform
     * @returns Path to the directory, or an empty string if the platform does
     * not support crash logs
     */
    std::filesystem::path NOAHH_DLL getCrashLogDirectory();


    std::string NOAHH_DLL writeCrashlog(noahh::Mod* faultyMod, std::string_view info, std::string_view stacktrace, std::string_view registers);

    std::string writeCrashlog(noahh::Mod* faultyMod, std::string_view info, std::string_view stacktrace, std::string_view registers, std::filesystem::path& outCrashlogPath);

    std::string getDateString(bool filesafe);

    void NOAHH_DLL printNoahhInfo(Buffer& stream);
    void NOAHH_DLL printMods(Buffer& stream);

    struct FunctionBinding {
        std::string name;
        uintptr_t offset;
    };

    void updateFunctionBindings();
    std::string_view NOAHH_DLL lookupClosestFunction(uintptr_t& address);
    std::string_view NOAHH_DLL lookupFunctionByOffset(uintptr_t address);
}

template <>
struct matjson::Serialize<crashlog::FunctionBinding> {
    static noahh::Result<crashlog::FunctionBinding> fromJson(Value const& value) {
        return noahh::Ok(crashlog::FunctionBinding{
            NOAHH_UNWRAP(value[1].asString()),
            NOAHH_UNWRAP(value[0].as<uintptr_t>())
        });
    }

    static Value toJson(crashlog::FunctionBinding const& binding) {
        auto arr = Value::array();
        arr.push(binding.offset);
        arr.push(binding.name);
        return arr;
    }
};
