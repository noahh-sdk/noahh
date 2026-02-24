#pragma once

#include <Noahh/loader/Hook.hpp>
#include <Noahh/loader/Loader.hpp>
#include <Noahh/loader/Mod.hpp>
#include <Noahh/utils/casts.hpp>
#include <Noahh/utils/ranges.hpp>
#include <vector>
#include "ModImpl.hpp"
#include "ModPatch.hpp"

using namespace noahh::prelude;

class Hook::Impl final : ModPatch {
public:
    Impl(
        void* address,
        void* detour,
        std::string displayName,
        tulip::hook::HandlerMetadata handlerMetadata,
        tulip::hook::HookMetadata hookMetadata
    );
    ~Impl();

    static std::shared_ptr<Hook> create(
        void* address,
        void* detour,
        std::string displayName,
        tulip::hook::HandlerMetadata handlerMetadata,
        tulip::hook::HookMetadata hookMetadata
    );

    template<class DetourType>
    static std::shared_ptr<Hook> create(
        void* address,
        DetourType detour,
        std::string displayName,
        tulip::hook::TulipConvention convention,
        tulip::hook::HookMetadata hookMetadata
    );

    Hook* m_self = nullptr;
    void* m_address;
    void* m_detour;
    std::string m_displayName;
    tulip::hook::HandlerMetadata m_handlerMetadata;
    tulip::hook::HookMetadata m_hookMetadata;
    tulip::hook::HookHandle m_handle = 0;

    Result<> enable();
    Result<> disable();
    Result<> toggle();
    Result<> toggle(bool enable);

    uintptr_t getAddress() const;
    std::string_view getDisplayName() const;
    matjson::Value getRuntimeInfo() const;
    tulip::hook::HookMetadata getHookMetadata() const;
    void setHookMetadata(tulip::hook::HookMetadata metadata);
    int32_t getPriority() const;
    void setPriority(int32_t priority);

    Result<> updateHookMetadata();

    friend class Hook;
    friend class Mod;
};

