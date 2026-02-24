#include <Noahh/DefaultInclude.hpp>

#import <Cocoa/Cocoa.h>
#include <AppKit/AppKit.h>
#include <objc/runtime.h>
#include "../load.hpp"
#include <dlfcn.h>
#include <mach-o/dyld.h>
#include <unistd.h>
#include <tulip/TulipHook.hpp>
#include <Noahh/utils/ObjcHook.hpp>
#include <array>
#include <filesystem>
#include <Noahh/Loader.hpp>
#include "../../loader/console.hpp"
#include "../../loader/LoaderImpl.hpp"
#include <thread>
#include <variant>
#include <loader/updater.hpp>

using namespace noahh::prelude;

std::length_error::~length_error() _NOEXCEPT {} // do not ask...

// camila has an old ass macos and this function turned
// from dynamic to static thats why she needs to define it
// this is what old versions does to a silly girl

void updateFiles() {
    auto frameworkDir = dirs::getGameDir() / "Frameworks";
    auto updatesDir = dirs::getNoahhDir() / "update";
    auto resourcesDir = dirs::getNoahhResourcesDir();

    if (std::filesystem::exists(frameworkDir) && std::filesystem::exists(updatesDir)) {
        std::error_code error;
        auto bootFile = "NoahhBootstrapper.dylib";
        auto noahhFile = "Noahh.dylib";

        if (std::filesystem::exists(updatesDir / bootFile)) {
            std::filesystem::remove(frameworkDir / bootFile, error);
            if (error) {
                log::warn("Couldn't remove old NoahhBootstrapper.dylib: {}", error.message());
            }
            else {
                std::filesystem::rename(updatesDir / bootFile, frameworkDir / bootFile, error);
                if (error) {
                    log::warn("Couldn't move new NoahhBootstrapper.dylib: {}", error.message());
                }
                else {
                    log::info("Updated NoahhBootstrapper.dylib");
                }
            }
        }
        if (std::filesystem::exists(updatesDir / noahhFile)) {
            std::filesystem::remove(frameworkDir / noahhFile, error);
            if (error) {
                log::warn("Couldn't remove old Noahh.dylib: {}", error.message());
            }
            else {
                std::filesystem::rename(updatesDir / noahhFile, frameworkDir / noahhFile, error);
                if (error) {
                    log::warn("Couldn't move new Noahh.dylib: {}", error.message());
                }
                else {
                    log::info("Updated Noahh.dylib");
                }
            }
        }
        if (std::filesystem::exists(updatesDir / "resources")) {
            std::filesystem::remove_all(resourcesDir / "noahh.loader", error);
            if (error) {
                log::warn("Couldn't remove old resources: {}", error.message());
            }
            else {
                std::filesystem::rename(updatesDir / "resources", resourcesDir / "noahh.loader", error);
                if (error) {
                    log::warn("Couldn't move new resources: {}", error.message());
                }
                else {
                    log::info("Updated resources");
                }
            }
        }
        std::filesystem::remove_all(updatesDir, error);
        if (error) {
            log::warn("Couldn't remove old update directory: {}", error.message());
        }
    }
}

$execute {
    using namespace noahh::updater;
    LoaderUpdateEvent().listen([](UpdateStatus const& status) {
        if (std::holds_alternative<UpdateFinished>(status)) {
            updateFiles();
        }
        return ListenerResult::Propagate;
    }).leak();
};

void updateNoahh() {
    std::filesystem::path oldSavePath = "/Users/Shared/Noahh/noahh";
    auto newSavePath = dirs::getSaveDir() / "noahh";
    if (std::filesystem::exists(oldSavePath)) {
        std::error_code error;

        std::filesystem::rename(oldSavePath, newSavePath, error);
        if (error) {
            log::warn("Couldn't migrate old save files from {} to {}", 
                oldSavePath, newSavePath
            );
        }
    }

    updateFiles();
}

extern "C" void fake() {}

static void(*s_applicationDidFinishLaunchingOrig)(void*, SEL, NSNotification*);

void applicationDidFinishLaunchingHook(void* self, SEL sel, NSNotification* notification) {
    updateNoahh();

    int exitCode = noahhEntry(nullptr);
    if (exitCode != 0)
        return;

    return s_applicationDidFinishLaunchingOrig(self, sel, notification);
}

// For some reason, keyUp isn't called if command is pressed, despite keyDown being called in the same situation.
static void(*s_sendEventOrig)(NSApplication* self, SEL sel, NSEvent* event);

void sendEventHook(NSApplication* self, SEL sel, NSEvent* event) {
    if ([event type] == NSEventTypeKeyUp) {
        [[[self mainWindow] firstResponder] tryToPerform:@selector(keyUp:) with:event];
        return;
    }

    s_sendEventOrig(self, sel, event);
}

// I like to call this the "Super Mega Ultra Safe Mode™"
// However for the sake of not getting side-eyed it's getting this boring name
bool cleanModeCheck() {
    if (
        CGEventSourceKeyState(kCGEventSourceStateHIDSystemState, (CGKeyCode)58) && // 58 = Option
        CGEventSourceKeyState(kCGEventSourceStateHIDSystemState, (CGKeyCode)56) // 56 = LShift
    ) {
        NSAlert* alert = [NSAlert new];
        alert.messageText = @"The Shift and Option keys were held down, do you want to open Geometry Dash without Noahh?";
        [alert addButtonWithTitle:@"Yes"];
        NSButton *cancelButton = [alert addButtonWithTitle:@"No"];
        alert.window.defaultButtonCell = cancelButton.cell;
        NSModalResponse choice = [alert runModal];
        return choice == NSAlertFirstButtonReturn;
    }
    return false;
}

bool loadNoahh() {
    if (cleanModeCheck()) return false;

    if (NOAHH_STR(NOAHH_GD_VERSION) != LoaderImpl::get()->getGameVersion()) {
        console::messageBox(
            "Unable to Load Noahh!",
            fmt::format(
                "Geometry Dash is outdated!\n"
                "Noahh requires GD {} but you have {}.\n"
                "Please, update Geometry Dash to {}.",
                NOAHH_STR(NOAHH_GD_VERSION),
                LoaderImpl::get()->getGameVersion(),
                NOAHH_STR(NOAHH_GD_VERSION)
            )
        );
        return false;
    }

    // this uses the internal hooking system because it needs to be fast
    if (auto imp = hook::replaceObjcMethod("AppController", "applicationDidFinishLaunching:", (void*)applicationDidFinishLaunchingHook)) {
        s_applicationDidFinishLaunchingOrig = reinterpret_cast<decltype(s_applicationDidFinishLaunchingOrig)>(imp.unwrap());
    }
    else {
        return false;
    }
    if (auto imp = hook::replaceObjcMethod("NSApplication", "sendEvent:", (void*)sendEventHook)) {
        s_sendEventOrig = reinterpret_cast<decltype(s_sendEventOrig)>(imp.unwrap());
    }
    else {
        return false;
    }

    return true;
}

__attribute__((constructor)) void _entry() {
    if (!loadNoahh())
        return;
}

