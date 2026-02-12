#pragma once

#include <mutex>
#include <unordered_map>
#include <vector>
#include "FileWatcher.hpp"
#include <Noahh/loader/Loader.hpp>
#include <Noahh/loader/Log.hpp>
#include <Noahh/utils/Result.hpp>

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

	InternalLoader();
	~InternalLoader();
public:
	static InternalLoader* get();

	bool setup();

	bool loadHooks();

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
