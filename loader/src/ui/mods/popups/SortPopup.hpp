#pragma once

#include <Noahh/ui/Popup.hpp>
#include "../sources/ModListSource.hpp"
#include "../NoahhStyle.hpp"

using namespace noahh::prelude;

class SortPopup : public NoahhPopup {
protected:
    ModListSource* m_source;
    std::vector<CCMenuItemToggler*> m_options;
    size_t m_selected;

    bool init(ModListSource* src);

    void onClose(CCObject* sender) override;
    void onSelect(CCObject*);

public:
    static SortPopup* create(ModListSource* src);
};

