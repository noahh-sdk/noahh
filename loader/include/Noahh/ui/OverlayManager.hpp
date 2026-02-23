#pragma once

#include "../DefaultInclude.hpp"
#include <cocos2d.h>

namespace noahh {
    class NOAHH_DLL OverlayManager final : public cocos2d::CCNode {
    public:
        static OverlayManager* get();
    };
}

