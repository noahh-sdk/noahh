#pragma once

#include <Noahh/platform/platform.hpp>

#include "string.hpp"

#if defined(NOAHH_IS_ANDROID)
#include "gnustl.hpp"
#else
#include "aliastl.hpp"
#endif

