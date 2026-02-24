#include <Noahh/Noahh.hpp>
#ifndef NOAHH_IS_IOS
#include <Noahh/utils/VMTHookManager.hpp>
#include <Noahh/modify/Traits.hpp>
#include <Noahh/modify/CCMenu.hpp>

using namespace noahh::prelude;

struct CCMenuSelectedFix : Modify<CCMenuSelectedFix, CCMenu> {
    bool initWithArray(CCArray* arr) {
        if (!CCMenu::initWithArray(arr)) return false;

        if (!exact_cast<CCMenu*>(this)) {
            return true;
        }

        auto hook = VMTHookManager::get().addHook<
            noahh::modifier::ResolveC<CCMenuSelectedFix>::func(&CCMenuSelectedFix::removeAllChildren)
        >(this, "cocos2d::CCMenu::removeAllChildren");

        if (!hook) {
            log::error("Failed to hook CCMenu::removeAllChildren: {}", hook.unwrapErr());
        }

        return true;
    }

    $override
    void removeAllChildren() {
        // CCMenu itself overrides `removeChild` to reset `m_pSelectedItem` and prevent UB.
        // `removeAllChildren` is not overridden and never calls `removeChild`, thus not resetting this member.
        // This fixes that, eliminating UB that can happen when spam clicking a button that removes itself with this method.
        m_pSelectedItem = nullptr;
        CCNode::removeAllChildren();
    }
};
#endif

