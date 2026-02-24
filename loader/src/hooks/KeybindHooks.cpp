#include <Noahh/modify/MoreOptionsLayer.hpp>
#include <ui/mods/settings/KeybindsPopup.hpp>

using namespace noahh::prelude;

#ifndef NOAHH_IS_IOS
// This seems to also be merged with the editor keybindings button
class $modify(MoreOptionsLayer) {
	$override
	void onKeybindings(CCObject*) {
		KeybindsPopup::create()->show();
	}
};
#endif

