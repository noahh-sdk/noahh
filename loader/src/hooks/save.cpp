#include <Noahh/Modify.hpp>
#include <Noahh/loader/Loader.hpp>

USE_NOAHH_NAMESPACE();

class $modify(AppDelegate) {
    void trySaveGame() {
        Loader::getInternalMod()->log() << "Saving...";

        auto r = Loader::get()->saveSettings();
        if (!r) {
            Loader::getInternalMod()->logInfo(
                r.error(), Severity::Error
            );
        }

        Loader::getInternalMod()->log() << "Saved";
        
        return AppDelegate::trySaveGame();
    }
};