#pragma once

#include <Noahh/binding/CCMenuItemSpriteExtra.hpp>
#include <Noahh/binding/FLAlertLayer.hpp>
#include <Noahh/utils/cocos.hpp>
#include <Noahh/utils/ZStringView.hpp>
#include <Noahh/utils/function.hpp>
#include <Noahh/ui/Layout.hpp>
#include <Noahh/ui/NineSlice.hpp>

namespace noahh {
    class NOAHH_DLL Popup : public FLAlertLayer {
    public:
        /**
         * Event posted when this popup is being closed
         */
        class CloseEvent final : public ::noahh::Event<CloseEvent, bool(), Popup*> {
            // filter params popup
            using Event::Event;
        };

    protected:
        cocos2d::CCSize m_size;
        NineSlice* m_bgSprite;
        cocos2d::CCLabelBMFont* m_title = nullptr;
        CCMenuItemSpriteExtra* m_closeBtn;

        ~Popup();
        void registerWithTouchDispatcher() override;
        
        /**
         * Init with AnchorLayout and the content size of `m_buttonMenu` and
         * `m_bgSprite` being tied to the size of `m_mainLayer` (rather than
         * being the size of the window)
         */
        bool init(
            float width, float height, char const* bg = "GJ_square01.png",
            cocos2d::CCRect bgRect = {}
        );
        bool init(
            cocos2d::CCSize size, char const* bg = "GJ_square01.png",
            cocos2d::CCRect bgRect = {}
        );

        void keyBackClicked() override;
        void keyDown(cocos2d::enumKeyCodes key, double p1) override;
        virtual void onClose(CCObject*);

        void setTitle(
            ZStringView title,
            const char* font = "goldFont.fnt",
            float scale = .7f,
            float offset = 20.f
        );

        void setCloseButtonSpr(cocos2d::CCSprite* spr, float scale = 1.f);

        /**
         * Returns an event filter that listens for when this popup is closed
         */
        CloseEvent listenForClose();
    };

    NOAHH_DLL FLAlertLayer* createQuickPopup(
        char const* title, std::string content, char const* btn1, char const* btn2,
        noahh::Function<void(FLAlertLayer*, bool)> selected, bool doShow = true, bool cancelledByEscape = false
    );

    NOAHH_DLL FLAlertLayer* createQuickPopup(
        char const* title, std::string content, char const* btn1, char const* btn2,
        float width, noahh::Function<void(FLAlertLayer*, bool)> selected, bool doShow = true, bool cancelledByEscape = false
    );
}

