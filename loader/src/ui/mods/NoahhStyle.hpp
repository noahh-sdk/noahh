#pragma once

#include <Noahh/DefaultInclude.hpp>
#include <Noahh/binding/ButtonSprite.hpp>
#include <Noahh/ui/General.hpp>
#include <Noahh/ui/IconButtonSprite.hpp>
#include <Noahh/ui/BasedButtonSprite.hpp>
#include <Noahh/ui/Popup.hpp>
#include <Noahh/ui/ScrollLayer.hpp>
#include <Noahh/ui/NineSlice.hpp>
#include <Noahh/utils/ZStringView.hpp>
#include <Noahh/loader/Mod.hpp>
#include <server/Server.hpp>

using namespace noahh::prelude;

enum class NoahhPopupStyle {
    Default,
    Alt,
    Alt2,
};

bool isNoahhTheme(bool forceDisableTheme = false);

class NoahhPopup : public Popup {
protected:
    bool m_forceDisableTheme = false;

    bool init(float width, float height, NoahhPopupStyle style = NoahhPopupStyle::Default, bool forceDisableTheme = false);
};

class NoahhSquareSprite : public CCSprite {
protected:
    bool* m_stateSrc = nullptr;
    bool m_state = false;
    bool m_forceDisableTheme = false;
    CCSprite* m_topSprite;

    bool init(CCSprite* top, bool* state, bool forceDisableTheme = false);

    void update(float dt) override;
    void updateImage();

public:
    static NoahhSquareSprite* create(const char* top, bool* state = nullptr, bool forceDisableTheme = false);
    static NoahhSquareSprite* createWithSpriteFrameName(const char* top, bool* state = nullptr, bool forceDisableTheme = false);

    CCSprite* getTopSprite() const;
    void setState(bool state);
};

CCNode* createLoadingCircle(float sideLength, const char* id = "loading-spinner");

enum class NoahhButtonSprite {
    Default,
    Install,
    Delete,
    Enable,
    Gray,
};
const char* getNoahhButtonSpriteName(NoahhButtonSprite spr, bool forceDisableTheme = false);
IconButtonSprite* createNoahhButton(
    CCNode* icon,
    ZStringView text,
    NoahhButtonSprite bg = NoahhButtonSprite::Default,
    bool forceDisableTheme = false
);
IconButtonSprite* createNoahhButton(
    CCNode* icon,
    ZStringView text,
    bool gold,
    NoahhButtonSprite bg = NoahhButtonSprite::Default,
    bool forceDisableTheme = false
);
ButtonSprite* createNoahhButton(
    ZStringView text,
    int width,
    bool absolute = false,
    bool gold = false,
    NoahhButtonSprite bg = NoahhButtonSprite::Default,
    bool forceDisableTheme = false
);
ButtonSprite* createNoahhButton(
    ZStringView text,
    bool gold = false,
    NoahhButtonSprite bg = NoahhButtonSprite::Default,
    bool forceDisableTheme = false
);

CircleButtonSprite* createNoahhCircleButton(CCSprite* top, float scale = 1.f, CircleBaseSize size = CircleBaseSize::Medium, bool altColor = false, bool forceDisableTheme = false);

ButtonSprite* createTagLabel(ZStringView text, std::pair<ccColor3B, ccColor3B> const& color);
IconButtonSprite* createTagLabelWithIcon(CCNode* icon, ZStringView text, std::pair<ccColor3B, ccColor3B> const& color);
ButtonSprite* createNoahhTagLabel(server::ServerTag const& tag);
std::pair<ccColor3B, ccColor3B> noahhTagColors(server::ServerTag const& tag);

ListBorders* createNoahhListBorders(CCSize const& size, bool forceDisableTheme = false);

class NoahhTabSprite : public CCNode {
protected:
    NineSlice* m_deselectedBG;
    NineSlice* m_selectedBG;
    CCSprite* m_icon;
    CCLabelBMFont* m_label;

    bool init(const char* iconFrame, const char* text, float width, bool altColor);

public:
    static NoahhTabSprite* create(const char* iconFrame, const char* text, float width, bool altColor = false);

    void select(bool selected);
    void disable(bool disabled);
};

