#include <Noahh/Noahh.hpp>
#include <Noahh/ui/SceneManager.hpp>

USE_NOAHH_NAMESPACE();

class $modify(AchievementNotifier) {
    void willSwitchToScene(CCScene* scene) {
        AchievementNotifier::willSwitchToScene(scene);
        SceneManager::get()->willSwitchToScene(scene);
    }
};