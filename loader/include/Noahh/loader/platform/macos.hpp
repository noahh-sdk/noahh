#pragma once

#define NOAHH_API extern "C"
#define NOAHH_DLL 

namespace noahh {
	using dylib_t = void*;
    struct PlatformInfo {
    	dylib_t m_dylib;
    };
}