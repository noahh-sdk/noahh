#pragma once

#include "MDTextArea.hpp"
#include "Popup.hpp"

namespace noahh {
    /**
     * FLAlertLayer with support for Markdown. See MDTextArea
     * for details on what features of MD are supported.
     */
    class NOAHH_DLL MDPopup : public Popup {
        class Impl;
        std::unique_ptr<Impl> m_impl;
    protected:
        MDPopup();
        ~MDPopup();
        bool init(
            bool compatibilityMode, ZStringView title, std::string info, ZStringView btn1, ZStringView btn2,
            noahh::Function<void(bool)> onClick
        );

        void onBtn(CCObject*);

        static float estimateHeight(std::string_view content);
    public:
        static MDPopup* create(
            ZStringView title, std::string content, ZStringView btn1,
            ZStringView btn2 = nullptr, noahh::Function<void(bool)> onClick = nullptr
        );

        static MDPopup* create(
            bool compatibilityMode, ZStringView title, std::string content,
            ZStringView btn1, ZStringView btn2 = nullptr, noahh::Function<void(bool)> onClick = nullptr
        );

        const noahh::Function<void(bool)>& getOnClick();
        void setOnClick(noahh::Function<void(bool)> onClick);
    };
}

