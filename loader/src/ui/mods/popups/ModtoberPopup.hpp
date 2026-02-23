#pragma once

#include <Noahh/ui/Popup.hpp>
#include "../NoahhStyle.hpp"

using namespace noahh::prelude;

class ModtoberPopup : public NoahhPopup {
protected:
    bool init() override;

    void onDiscord(CCObject*);

public:
    static ModtoberPopup* create();
};
