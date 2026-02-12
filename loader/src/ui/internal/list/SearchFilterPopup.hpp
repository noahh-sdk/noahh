#pragma once

#include <Noahh/ui/Popup.hpp>

USE_NOAHH_NAMESPACE();

class ModListLayer;

class SearchFilterPopup : public Popup<ModListLayer*> {
protected:
    ModListLayer* m_modLayer;

    bool setup(ModListLayer* layer) override;
    void addToggle(const char* title, int flag, CCPoint& pos);

    void onToggle(cocos2d::CCObject*);
    
public:
    static SearchFilterPopup* create(ModListLayer* layer);
};
