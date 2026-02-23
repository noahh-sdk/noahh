#pragma once

#include <Noahh/cocos/base_nodes/CCNode.h>
#include <Noahh/cocos/cocoa/CCGeometry.h>
#include <Noahh/cocos/sprite_nodes/CCSprite.h>
#include <Noahh/loader/Loader.hpp>
#include <Noahh/ui/NineSlice.hpp>
#include <optional>
#include "ui/mods/popups/DevPopup.hpp"

using namespace noahh::prelude;

class ModDeveloperItem : public CCNode {
protected:
    NineSlice* m_bg;
    DevListPopup* m_popup;
public:
    static ModDeveloperItem* create(
        DevListPopup* popup,
        std::string developer,
        CCSize const& size,
        std::optional<std::string> displayName = std::nullopt,
        bool addMoreButton = true
    );
private:
    bool init(
        DevListPopup* popup,
        std::string developer,
        CCSize const& size,
        std::optional<std::string> displayName,
        bool addMoreButton
    );
    void onMoreByThisDev(CCObject* sender);
};

