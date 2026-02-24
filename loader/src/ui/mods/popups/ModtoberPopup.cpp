#include "ModtoberPopup.hpp"
#include <Noahh/utils/web.hpp>
#include <Noahh/loader/Mod.hpp>
#include <Noahh/binding/ButtonSprite.hpp>

bool ModtoberPopup::init() {
    if (!NoahhPopup::init(410.f, 270.f))
        return false;

    m_bgSprite->setVisible(false);

    auto bg = CCSprite::createWithSpriteFrameName("modtober25-popup.png"_spr);
    m_mainLayer->addChildAtPosition(bg, Anchor::Center);

    auto supportSpr = createNoahhButton("Join");
    supportSpr->setScale(.8f);
    auto supportBtn = CCMenuItemSpriteExtra::create(
        supportSpr, this, menu_selector(ModtoberPopup::onDiscord)
    );
    m_buttonMenu->addChildAtPosition(supportBtn, Anchor::BottomRight, ccp(-65, 50));

    return true;
}

void ModtoberPopup::onDiscord(CCObject*) {
    createQuickPopup(
        "Join Modtober",
        "<co>Modtober</c> is being hosted on the <cr>Noahh</c> <ca>Discord Server</c>.\n"
        "To participate, join Noahh and read the rules for the contest in <cy>#dev-news</c>",
        "Cancel", "Join Discord",
        [](auto, bool btn2) {
            if (btn2) {
                web::openLinkInBrowser("https://discord.gg/9e43WMKzhp");
            }
        },
        true,
        false
    );
}

ModtoberPopup* ModtoberPopup::create() {
    auto ret = new ModtoberPopup();
    if (ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}
