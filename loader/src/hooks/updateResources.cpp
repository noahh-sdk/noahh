#include <Noahh/Modify.hpp>
#include <Noahh/loader/Loader.hpp>

USE_NOAHH_NAMESPACE();

class $modify(GameManager) {
	void reloadAllStep2() {
		GameManager::reloadAllStep2();
		Loader::get()->updateResourcePaths();
	}
};

class $modify(LoadingLayer) {
	void loadAssets() {
		LoadingLayer::loadAssets();
		if (this->m_loadStep == 5) {
			Loader::get()->updateResources();
		}
	}
};