#include <Noahh/loader/ModEvent.hpp>
#include <Noahh/Loader.hpp>
#include <Noahh/ui/OverlayManager.hpp>

using namespace noahh::prelude;

OverlayManager* OverlayManager::get() {
    static OverlayManager* inst = nullptr;
    if (!inst) {
        inst = new OverlayManager();
        inst->onEnter();
    }
    return inst;
}

$on_mod(Loaded) {
    queueInMainThread([] {
        CCDirector::get()->m_pNotificationNode = OverlayManager::get();
    });
}

