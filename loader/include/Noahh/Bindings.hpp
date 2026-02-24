#pragma once

#ifdef _MSC_VER
    #pragma warning(disable : 4251) // dll-interface
    #pragma warning(disable : 4099) // type first seen as 'class'
    #pragma warning(disable : 4584) // CCKeyboardDelegate included twice in UILayer
#endif

#include <Noahh/Enums.hpp>

#include <Noahh/DefaultInclude.hpp>
#include <Noahh/utils/addresser.hpp>
#include <cocos-ext.h>
#include <cocos2d.h>
#include <fmod.hpp>
#include <stdint.h>
#include <type_traits>
#include <unordered_map>
#include <algorithm>

#define CLASSPARAM(...)
#define STRUCTPARAM(...)

#include <Noahh/GeneratedBinding.hpp>

