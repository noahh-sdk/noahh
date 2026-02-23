#pragma once

#include <Noahh/utils/ZStringView.hpp>

namespace noahh::utils::thread {
    // the platform-specific methods are needed for the thread names to show up
    // in places like task managers and debuggers
    void platformSetName(ZStringView name);
}

