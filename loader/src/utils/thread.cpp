#include <Noahh/DefaultInclude.hpp>

using namespace noahh::prelude;

#include <Noahh/loader/Loader.hpp> // i don't think i have to label these anymore
#include <Noahh/Utils.hpp>
#include "thread.hpp"

static thread_local std::string s_threadName;

ZStringView noahh::utils::thread::getName() {
    // only use the thread-local variable here, no need for platform get methods
    if (s_threadName.empty()) {
        s_threadName = getDefaultName();
    }
    return s_threadName;
}

void noahh::utils::thread::setName(std::string name) {
    s_threadName = std::move(name);
    platformSetName(s_threadName);
}

