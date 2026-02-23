#include <Noahh/loader/GameEvent.hpp>
#include <Noahh/modify/GameManager.hpp>

using namespace noahh::prelude;

struct GameReloadHook : Modify<GameReloadHook, GameManager> {
    void reloadAllStep5() {
        GameManager::reloadAllStep5();
        GameEvent(GameEventType::TexturesUnloaded).send();
    }
};

