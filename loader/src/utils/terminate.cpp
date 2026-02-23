#include <Noahh/utils/terminate.hpp>
#include <Noahh/loader/Mod.hpp>
#include "../loader/Log.hpp"

using namespace noahh::prelude;

void noahh::utils::detail::logTerminationError(const char* reason, Mod* mod) {
    // invoke logImpl directly to indicate what mod it came from
    log::logImpl(
        Severity::Error, mod,
        "The mod '{}' by {} has deliberately asked the game to crash.\nReason: {}",
        mod->getID(), fmt::format("{}", fmt::join(mod->getDevelopers(), ", ")), reason
    );
}

