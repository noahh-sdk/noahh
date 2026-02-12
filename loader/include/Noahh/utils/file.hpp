#pragma once

#include <Noahh/DefaultInclude.hpp>
#include "Result.hpp"
#include <string>
#include "types.hpp"
#include "fs/filesystem.hpp"

namespace noahh::file_utils {
    NOAHH_DLL Result<std::string> readString(std::string            const& path);
    NOAHH_DLL Result<std::string> readString(std::wstring           const& path);
    NOAHH_DLL Result<std::string> readString(ghc::filesystem::path  const& path);
    NOAHH_DLL Result<byte_array>  readBinary(std::string            const& path);
    NOAHH_DLL Result<byte_array>  readBinary(std::wstring           const& path);
    NOAHH_DLL Result<byte_array>  readBinary(ghc::filesystem::path  const& path);

    NOAHH_DLL Result<> writeString(std::string           const& path, std::string const& data);
    NOAHH_DLL Result<> writeString(std::wstring          const& path, std::string const& data);
    NOAHH_DLL Result<> writeString(ghc::filesystem::path const& path, std::string const& data);
    NOAHH_DLL Result<> writeBinary(std::string           const& path, byte_array  const& data);
    NOAHH_DLL Result<> writeBinary(std::wstring          const& path, byte_array  const& data);
    NOAHH_DLL Result<> writeBinary(ghc::filesystem::path const& path, byte_array  const& data);

    NOAHH_DLL Result<> createDirectory(std::string const& path);
    NOAHH_DLL Result<> createDirectoryAll(std::string const& path);
    NOAHH_DLL Result<std::vector<std::string>> listFiles(std::string const& path);
    NOAHH_DLL Result<std::vector<std::string>> listFilesRecursively(std::string const& path);
}
