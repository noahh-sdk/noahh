#pragma once

#include <Noahh/ui/General.hpp>
#include <Noahh/ui/SimpleAxisLayout.hpp>
#include <Noahh/ui/Popup.hpp>
#include <Noahh/ui/NineSlice.hpp>

using namespace noahh::prelude;

enum class ModListDisplay {
    SmallList,
    BigList,
    Grid,
};

class ModListItem : public CCNode {
protected:
    ModListDisplay m_display = ModListDisplay::SmallList;
    float m_targetWidth = 300;
    NineSlice* m_bg;
    CCMenu* m_viewMenu;

    bool init();

    virtual void updateState();

public:
    virtual void updateDisplay(float width, ModListDisplay display);
};

