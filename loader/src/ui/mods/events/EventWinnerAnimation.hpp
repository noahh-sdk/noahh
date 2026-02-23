#pragma once

#include <Noahh/utils/cocos.hpp>

using namespace noahh::prelude;

// NOTE: this has a generic name because we should have modtober info

class EventWinnerAnimation : public CCMenu {
protected:
    CCLayerColor* m_bg;

    bool init();

    void onClose(CCObject*);

public:
    static EventWinnerAnimation* create();
};

