#include <Noahh/loader/cnoahh.h>
#include <Noahh/loader/Mod.hpp>
#include <Noahh/loader/Log.hpp>

USE_NOAHH_NAMESPACE();

std::string g_lastError = "";

void noahh_mod_log(void* cmod, const char* message) {
	auto mod = reinterpret_cast<Mod*>(cmod);
	mod->log() << message;
}

bool noahh_mod_add_hook(void* cmod, void* address, void* detour) {
	// auto mod = reinterpret_cast<Mod*>(cmod);
	// auto res = mod->addHook(address, detour);
	// if (!res) {
	// 	g_lastError = res.error();
	// 	return false;
	// }
	return true;
}

bool noahh_get_last_error(char* buffer, size_t bufferSize) {
	if (buffer && bufferSize >= g_lastError.size()) {
		try {
			std::copy(g_lastError.begin(), g_lastError.end(), buffer);
			return true;
		} catch(...) {}
	}
	return false;
}
