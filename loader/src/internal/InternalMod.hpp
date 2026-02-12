#pragma once

class InternalMod;

#include <Noahh/loader/Mod.hpp>

USE_NOAHH_NAMESPACE();

class InternalMod : public Mod {
    protected:
        InternalMod();
        virtual ~InternalMod();

    public:
        static InternalMod* get();
};
