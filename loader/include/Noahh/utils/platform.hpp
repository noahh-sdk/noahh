#pragma once

#include <Noahh/DefaultInclude.hpp>
#include "Result.hpp"
#include <string>
#include <vector>
#include <functional>
#include "fs/filesystem.hpp"

namespace noahh::utils::clipboard {
    NOAHH_DLL bool write(std::string const& data);
    NOAHH_DLL std::string read();
}

namespace noahh::utils::dirs {
    NOAHH_DLL ghc::filesystem::path noahhRoot();
    NOAHH_DLL bool openFolder(ghc::filesystem::path const& path);
}

namespace noahh::utils::web {
    NOAHH_DLL void openLinkInBrowser(std::string const& url);
}
