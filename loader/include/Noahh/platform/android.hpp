#pragma once

#include <dlfcn.h>

namespace noahh::base {
	NOAHH_NOINLINE inline uintptr_t get() {
		static uintptr_t base = reinterpret_cast<uintptr_t>(dlopen("libcocos2dcpp.so", RTLD_LAZY));
		return base;
	}
}

namespace noahh::cast {
	template <class After, class Before>
	After typeinfo_cast(Before ptr) {
		// yall have symbols smh
	    return dynamic_cast<After>(ptr);
	} 
}