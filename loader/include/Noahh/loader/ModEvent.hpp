#pragma once

#include "Event.hpp"
#include <matjson.hpp>
#include <optional>

namespace noahh {
    class Mod;
    Mod* getMod();

    enum class ModEventType {
        Loaded,
        DataLoaded,
        DataSaved,
    };

    /**
     * Event that is fired when a mod is loaded / unloaded / enabled / disabled
     */
    class ModStateEvent final : public GlobalEvent<ModStateEvent, bool(), ModEventType, Mod*> {
    public:
        // filter params type, targetMod
        using GlobalEvent::GlobalEvent;
    };

    /**
     * Event posted to a mod when another mod that depends on it is loaded
     */
    class DependencyLoadedEvent final : public Event<DependencyLoadedEvent, bool(Mod*), Mod*> {
    public:
        // listener params dependency
        // filter params target
        using Event::Event;
    };
}

#define $on_mod(type) $execute_base({                                  \
    noahh::ModStateEvent(noahh::ModEventType::type, noahh::getMod())   \
    .listen(&NOAHH_CONCAT(noahhExecFunctionI, __LINE__)).leak();       \
})

