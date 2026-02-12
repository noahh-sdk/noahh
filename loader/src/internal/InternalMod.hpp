#pragma once

class InternalMod;

#include <Noahh/loader/Mod.hpp>

USE_NOAHH_NAMESPACE();

class InternalLoader;

class InternalMod : public Mod {
    protected:
        friend class InternalLoade;

        InternalMod();
        virtual ~InternalMod();

    public:
        static InternalMod* get();
};
