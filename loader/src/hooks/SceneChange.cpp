#include <Noahh/ui/SceneEvent.hpp>
#include <Noahh/modify/CCDirector.hpp>
#include <cocos2d.h>

using namespace noahh::prelude;

struct SceneChangeHook : Modify<SceneChangeHook, cocos2d::CCDirector> {
	void willSwitchToScene(CCScene* scene) {
		SceneEvent().send(scene);
		CCDirector::willSwitchToScene(scene);
	}
};

