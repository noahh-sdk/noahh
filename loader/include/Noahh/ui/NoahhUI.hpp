#pragma once

#include "../loader/Mod.hpp"
#include <Noahh/binding/FLAlertLayer.hpp>
#include <Noahh/ui/Popup.hpp>

class ModPopup;
class ModItem;
class ModLogoSprite;
class FLAlertLayer; // for macos :3

namespace noahh {
    /**
     * Event posted whenever a popup is opened for a mod. Allows mods to modify
     * the Noahh UI. See the [tutorial on Noahh UI modification](https://docs.noahh-sdk.org/tutorials/modify-noahh)
     * for **very important notes on these events**!
     */
    class ModPopupUIEvent final : public Event<ModPopupUIEvent, bool(FLAlertLayer*, std::string_view, std::optional<Mod*>)> {
    public:
        // listener params popup, modID, mod
        using Event::Event;
    };

    /**
     * Event posted whenever a logo sprite is created for a mod. Allows mods to modify
     * the Noahh UI. See the [tutorial on Noahh UI modification](https://docs.noahh-sdk.org/tutorials/modify-noahh)
     * for **very important notes on these events**!
     */
    class ModItemUIEvent final : public Event<ModItemUIEvent, bool(cocos2d::CCNode*, std::string_view, std::optional<Mod*>)> {
    public:
        // listener params item, modID, mod
        using Event::Event;
    };

    /**
     * Event posted whenever a logo sprite is created for a mod. Allows mods to modify
     * the Noahh UI. See the [tutorial on Noahh UI modification](https://docs.noahh-sdk.org/tutorials/modify-noahh)
     * for **very important notes on these events**!
     */
    class ModLogoUIEvent final : public Event<ModItemUIEvent, bool(cocos2d::CCNode*, std::string_view, std::optional<Mod*>)> {
    public:
        // listener params sprite, modID, mod
        using Event::Event;
    };

    /**
     * Open the Noahh mods list
     */
    NOAHH_DLL void openModsList();
    /**
     * Open the info popup for a mod
     */
    NOAHH_DLL void openInfoPopup(Mod* mod);
    /**
     * Open the info popup for a mod based on an ID. If the mod is installed,
     * its installed popup is opened. Otherwise will check if the servers
     * have this mod, or if not, show an error popup
     * @returns `std::nullopt` if the mod is installed, otherwise a Task
     * that completes to `true` if the mod was found and a popup was opened,
     * and `false` otherwise. If you wish to modify the created popup,
     * listen for the Noahh UI events listed in `NoahhUI.hpp`
     */
    NOAHH_DLL std::optional<arc::TaskHandle<bool>> openInfoPopup(std::string modID);
    /**
     * Open the info popup for a mod on the changelog page
     */
    NOAHH_DLL void openChangelogPopup(Mod* mod);
    /**
     * Open the issue report popup for a mod
     */
    NOAHH_DLL void openIssueReportPopup(Mod* mod);
    /**
     * Open the support popup for a mod
     */
    NOAHH_DLL void openSupportPopup(Mod* mod);
    NOAHH_DLL void openSupportPopup(ModMetadata const& metadata);
    /**
     * Open the settings popup for a mod (if it has any settings)
     */
    NOAHH_DLL void openSettingsPopup(Mod* mod);
    /**
     * Open the settings popup for a mod (if it has any settings)
     * @param mod Mod the open the popup for
     * @param disableNoahhTheme If false, the popup follows the user's chosen
     * theme options. If true, the popup is always in the GD theme (not Noahh's
     * dark purple colors)
     * @returns A pointer to the created Popup, or null if the mod has no
     * settings
     */
    NOAHH_DLL Popup* openSettingsPopup(Mod* mod, bool disableNoahhTheme);
    /**
     * Create a default logo sprite
     */
    NOAHH_DLL cocos2d::CCNode* createDefaultLogo();
    /**
     * Create a logo sprite for a mod
     */
    NOAHH_DLL cocos2d::CCNode* createModLogo(Mod* mod);
    /**
     * Create a logo sprite for a mod from a .noahh file
     */
    NOAHH_DLL cocos2d::CCNode* createModLogo(std::filesystem::path const& noahhPackage);
    /**
     * Create a logo sprite for a mod downloaded from the Noahh servers. The
     * logo is initially a loading circle, with the actual sprite downloaded
     * asynchronously
     */
    NOAHH_DLL cocos2d::CCNode* createServerModLogo(std::string id);
}

