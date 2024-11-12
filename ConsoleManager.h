#pragma once

#include <unordered_map>
#include <string>
#include <thread>

#include "AConsole.h"
#include "ConfigurationManager.h"
#include "Scheduler.h"
#include "ProcessScreen.h"
#include "ResourceManager.h"

class ConsoleManager {
public:
    ConsoleManager();
    ~ConsoleManager();

    void run();
    void switchScreen(std::string consoleName);
    void setInitialized();
    ConfigurationManager& getConfigurationManager();
    const std::unordered_map<std::string, std::shared_ptr<AConsole>>& getConsoles() const;
    void addConsole(std::shared_ptr<AConsole> console);
    void returnToPreviousScreen();
    ResourceManager& getResourceManager();
    void createProcessScreen(const std::string processName);
    void displayStatus();
    bool ifProcessExists(std::string name);
    bool isProcessFinished(std::string name);

private:
    ConfigurationManager configManager;
    ResourceManager resourceManager; // No pointer, just the object itself

    std::unordered_map<std::string, std::shared_ptr<AConsole>> consoles;
    std::shared_ptr<AConsole> previousConsole;
    std::shared_ptr<AConsole> currentConsole;

    int processID = 0;
    std::thread testThread;
    std::mutex mtx;
};
