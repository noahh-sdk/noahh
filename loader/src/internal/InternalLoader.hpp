#pragma once

#include <mutex>
#include <unordered_map>
#include <vector>
#include "FileWatcher.hpp"
#include <Noahh/loader/Loader.hpp>
#include <Noahh/loader/Log.hpp>
#include <Noahh/utils/Result.hpp>
#include <unordered_set>

USE_NOAHH_NAMESPACE();

/**
 * Internal extension of Loader for private information
 * @class InternalLoader
 */
class InternalLoader : public Loader {
protected:
	std::vector<LogPtr*> m_logQueue;
	std::vector<std::function<void(void)>> m_gdThreadQueue;
	mutable std::mutex m_gdThreadMutex;
	bool m_platformConsoleReady = false;
	std::unordered_set<std::string> m_shownInfoAlerts;

	void saveInfoAlerts(nlohmann::json& json);
	void loadInfoAlerts(nlohmann::json& json);

	InternalLoader();
	~InternalLoader();

	friend class Loader;

public:
	static InternalLoader* get();

	bool setup();

	bool loadHooks();

	/**
	 * Check if a one-time event has been shown to the user, 
	 * and set it to true if not. Will return the previous 
	 * state of the event before setting it to true
	 */
	bool shownInfoAlert(std::string const& key);
	void queueInGDThread(std::function<void NOAHH_CALL(void)> func);
	void executeGDThreadQueue();

	bool platformConsoleReady() const;
	void queueConsoleMessage(LogPtr*);
	void setupPlatformConsole();
	void awaitPlatformConsole();
	void closePlatformConsole();
	static void platformMessageBox(const char* title, const char* info);

	friend int noahhEntry(void* platformData);
};
