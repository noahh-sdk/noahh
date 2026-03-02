#include <Noahh/loader/GameEvent.hpp>
#include <Noahh/modify/CCDirector.hpp>
#include <Noahh/modify/PlatformToolbox.hpp>
#include <cocos2d.h>

using namespace noahh::prelude;

namespace noahh {

static void triggerEvent() {
    GameEvent(GameEventType::Exiting).send();
}

#ifdef NOAHH_IS_MACOS

struct GameExitHook : Modify<GameExitHook, PlatformToolbox> {
    static void platformShutdown() {
        triggerEvent();
        PlatformToolbox::platformShutdown();
    }
};

#else

struct GameExitHook : Modify<GameExitHook, CCDirector> {
    void purgeDirector() {
        triggerEvent();
        CCDirector::purgeDirector();
    }
};

#endif

}

