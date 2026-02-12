#include "InternalMod.hpp"
#include "about.hpp"

static ModInfo getInternalModInfo() {
    ModInfo info;
    
    info.m_id          = "noahh.loader";
    info.m_name        = "Noahh";
    info.m_developer   = "Noahh Team";
    info.m_description = "Internal representation";
    info.m_details     = LOADER_ABOUT_MD;
    info.m_version     = LOADER_VERSION;
    info.m_supportsDisabling = false;
    info.m_spritesheets = {
        "noahh.loader/LogoSheet",
        "noahh.loader/APISheet",
        "noahh.loader/BlankSheet"
    };

    return info;
}

InternalMod::InternalMod() : Mod(getInternalModInfo()) {}

InternalMod::~InternalMod() {}

InternalMod* InternalMod::get() {
    static auto g_mod = new InternalMod;
    return g_mod;
}
