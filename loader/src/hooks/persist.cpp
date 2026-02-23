#include <Noahh/ui/OverlayManager.hpp>
#include <Noahh/modify/CCDirector.hpp>
#include <Noahh/modify/CCEGLView.hpp>

using namespace noahh::prelude;

#ifdef NOAHH_IS_WINDOWS
#include <Noahh/modify/AppDelegate.hpp>
#else
#include <Noahh/modify/AchievementNotifier.hpp>
#endif

namespace noahh {

struct SceneSwitch2 : Modify<SceneSwitch2, CCDirector> {
    NOAHH_FORWARD_COMPAT_DISABLE_HOOKS("persist disabled")
    // CCDirector does not call willSwitchToScene in these 2 instances,
    // so we have to do it ourselves to make everything behave as expected
    void popScene() {
        CCDirector::popScene();
    #ifdef NOAHH_IS_WINDOWS
        AppDelegate::get()->willSwitchToScene(m_pNextScene);
    #else
        AchievementNotifier::sharedState()->willSwitchToScene(m_pNextScene);
    #endif
    }

    void popToSceneStackLevel(int level) {
        CCDirector::popToSceneStackLevel(level);
    #ifdef NOAHH_IS_WINDOWS
        AppDelegate::get()->willSwitchToScene(m_pNextScene);
    #else
        AchievementNotifier::sharedState()->willSwitchToScene(m_pNextScene);
    #endif
    }
};


}

