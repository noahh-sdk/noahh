#pragma once

#include <string>
#include <matjson.hpp>

namespace noahh::ipc {
    void setup();
    matjson::Value processRaw(void* rawHandle, std::string_view buffer);
}

