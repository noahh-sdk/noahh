#include <Noahh/utils/platform.hpp>

#ifdef NOAHH_IS_IOS

#include <Noahh/Noahh.hpp>
#include <dlfcn.h>

USE_NOAHH_NAMESPACE();

template<typename T>
T findSymbolOrMangled(void* dylib, const char* name, const char* mangled) {
	auto res = reinterpret_cast<T>(dlsym(dylib, name));
	if (!res) {
		res = reinterpret_cast<T>(dlsym(dylib,mangled));
	}
	return res;
}

Result<> Mod::loadPlatformBinary() {
	auto dylib = dlopen((this->m_tempDirName / this->m_info.m_binaryName).string().c_str(), RTLD_LAZY);
	if (dylib) {
		this->m_implicitLoadFunc = findSymbolOrMangled<noahh_load>(dylib, "noahh_implicit_load", "_noahh_implicit_load");
		this->m_loadFunc = findSymbolOrMangled<noahh_load>(dylib, "noahh_load", "_noahh_load");
		this->m_unloadFunc = findSymbolOrMangled<noahh_unload>(dylib, "noahh_unload", "_noahh_unload");
		this->m_enableFunc = findSymbolOrMangled<noahh_enable>(dylib, "noahh_enable", "_noahh_enable");
		this->m_disableFunc = findSymbolOrMangled<noahh_disable>(dylib, "noahh_disable", "_noahh_disable");
		this->m_saveDataFunc = findSymbolOrMangled<noahh_save_data>(dylib, "noahh_save_data", "_noahh_save_data");
		this->m_loadDataFunc = findSymbolOrMangled<noahh_load_data>(dylib, "noahh_load_data", "_noahh_load_data");
		this->m_settingUpdatedFunc = findSymbolOrMangled<noahh_setting_updated>(dylib, "noahh_setting_updated", "_noahh_setting_updated");

		if (!this->m_implicitLoadFunc && !this->m_loadFunc) {
			return Err<>("Unable to find mod entry point (lacking both implicit & explicit definition)");
		}

		if (this->m_platformInfo) {
			delete this->m_platformInfo;
		}
		this->m_platformInfo = new PlatformInfo { dylib };

		return Ok<>();
	}
	std::string err = (char const*)dlerror();
	return Err<>("Unable to load the DYLIB: dlerror returned (" + err + ")");
}

Result<> Mod::unloadPlatformBinary() {
	auto dylib = this->m_platformInfo->m_dylib;
	delete this->m_platformInfo;
	this->m_platformInfo = nullptr;
	if (dlclose(dylib) == 0) {
		this->m_unloadFunc = nullptr;
		this->m_loadFunc = nullptr;
		this->m_implicitLoadFunc = nullptr;
		this->m_enableFunc = nullptr;
		this->m_disableFunc = nullptr;
		this->m_saveDataFunc = nullptr;
		this->m_loadDataFunc = nullptr;
		this->m_settingUpdatedFunc = nullptr;
		return Ok<>();
	} else {
		return Err<>("Unable to free library");
	}
}

#endif
