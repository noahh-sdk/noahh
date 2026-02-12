#pragma once

#include <Noahh/Noahh.hpp>

USE_NOAHH_NAMESPACE();

Result<std::string> fetch(std::string const& url);
Result<nlohmann::json> fetchJSON(std::string const& url);
Result<> fetchFile(
    std::string const& url,
    ghc::filesystem::path const& into,
    std::function<int(double, double)> prog = nullptr
);

