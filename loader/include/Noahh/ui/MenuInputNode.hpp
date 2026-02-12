#pragma once

#include <Noahh/Bindings.hpp>

namespace noahh {
    /**
     * Simple wrapper around CCTextInputNode that 
     * turns it into a CCMenuItem that can be used 
     * in a CCMenu. Can help with touch dispatcher 
     * issues. Also comes with a background sprite
     */
    class NOAHH_DLL MenuInputNode : public cocos2d::CCMenuItem {
    protected:
        cocos2d::extension::CCScale9Sprite* m_bgSprite = nullptr;
        CCTextInputNode* m_input;

        bool init(
            float width,
            float height,
            const char* placeholder,
            const char* font,
            bool bg
        );

    public:
        static MenuInputNode* create(
            float width,
            float height,
            const char* placeholder,
            const char* font,
            bool bg = false
        );

        void selected() override;

        CCTextInputNode* getInput() const;
    };
}