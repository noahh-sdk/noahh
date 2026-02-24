#pragma once

#include <Noahh/cocos/cocoa/CCGeometry.h>
#include <Noahh/cocos/base_nodes/CCNode.h>
#include <Noahh/loader/Loader.hpp>
#include <Noahh/loader/Mod.hpp>
#include <Noahh/ui/ScrollLayer.hpp>
#include <Noahh/ui/NineSlice.hpp>
#include "ui/mods/popups/DevPopup.hpp"
#include "ui/mods/sources/ModSource.hpp"

using namespace noahh::prelude;

class ModDeveloperList : public CCNode {
protected:
    ModSource m_source;
    ScrollLayer* m_list;
    NineSlice* m_bg;
public:
    static ModDeveloperList* create(
        DevListPopup* popup,
        ModSource const& source,
        CCSize const& size
    );
protected:
    bool init(
        DevListPopup* popup,
        ModSource const& source,
        CCSize const& size
    );
};

