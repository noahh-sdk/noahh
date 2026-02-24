#include <Noahh/Noahh.hpp>
#include <Noahh/modify/CCMenuItem.hpp>
#include <Noahh/modify/CCMenu.hpp>

using namespace noahh::prelude;

class $modify(CCMenuItem) {
    void activate() {
        this->retain();
        CCMenuItem::activate();
        this->release();
    }
};

class $modify(CCMenu) {
    void ccTouchEnded(CCTouch* touch, CCEvent* event) {
        this->retain();
        CCMenu::ccTouchEnded(touch, event);
        this->release();
    }
};
