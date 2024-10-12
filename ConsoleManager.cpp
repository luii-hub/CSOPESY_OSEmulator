#include "ConsoleManager.h"
#include "MainMenu.h"
#include "Marquee.h"
#include "ConfigurationManager.h"
#include "Scheduler.h"
#include "Process.h"
#include "ProcessScreen.h"

#include <random>

ConsoleManager::ConsoleManager() {
	auto MAIN_MENU = std::make_shared<MainMenu>();
	consoles[MAIN_MENU->getName()] = MAIN_MENU;

	auto MARQUEE_SCREEN = std::make_shared<Marquee>();
	consoles[MARQUEE_SCREEN->getName()] = MARQUEE_SCREEN;

	currentConsole = MAIN_MENU;
}

ConsoleManager::~ConsoleManager()
{
}

void ConsoleManager::run()
{	
	// Main loop
	if (currentConsole) {
		currentConsole->onExecute();
	}
}

void ConsoleManager::switchScreen(const std::string consoleName) {

	// For process screens
	if (consoleName.substr(0, 15) == "PROCESS_SCREEN_") {
		std::string processName = consoleName.substr(15);

		if (resourceManager.processExists(processName)) {
			
			// Check if process is finished
			std::shared_ptr<Process> process = resourceManager.findProcessByName(processName);
			
			if (!process->isFinished()) {
				previousConsole = currentConsole;
				currentConsole = consoles[consoleName];
				system("cls");
				currentConsole->onExecute();
			}
			else {
				std::cerr << "Process " << processName << " has already finished." << std::endl;
			}
		}
		else {
			std::cerr << "Process " << processName << " not found." << std::endl;
		}
	}

	// For non-process screens (should be removed after Group HW)
	else {
		if (consoles.find(consoleName) != consoles.end()) {
			previousConsole = currentConsole;
			currentConsole = consoles[consoleName];
			system("cls");
			currentConsole->onExecute();
		}
		else {
			std::cerr << "Console " << consoleName << " not found." << std::endl;
		}
	}
}

void ConsoleManager::setInitialized() {
	if (configManager.initialize() && resourceManager.initialize(&configManager)) {
		std::cout << "Initialization successful..." << std::endl;
	}
}

ConfigurationManager& ConsoleManager::getConfigurationManager() {
	return configManager;
}

const std::unordered_map<std::string, std::shared_ptr<AConsole>>& ConsoleManager::getConsoles() const {
	return consoles;
}

void ConsoleManager::addConsole(std::shared_ptr<AConsole> console) {
	consoles[console->getName()] = console;
}

void ConsoleManager::returnToPreviousScreen() {
	if (previousConsole) {
		currentConsole = previousConsole;
		previousConsole = nullptr;
		system("cls");
		currentConsole->onExecute();
	}
	else {
		std::cerr << "No previous screen to return to." << std::endl;
	}
}

ResourceManager& ConsoleManager::getResourceManager() {
	return resourceManager;
}


void ConsoleManager::createProcessScreen(const std::string processName) {
	// Create new process
	std::shared_ptr<Process> processPointer = resourceManager.createProcess(processName);

	// Create new process screen
	auto processScreen = std::make_shared<ProcessScreen>(processPointer);

	// Add process screen to console manager
	addConsole(processScreen);

	// Switch to process screen
	//switchScreen(processScreen->getName());
}



void ConsoleManager::displayStatus() {
	resourceManager.displayStatus();
}

bool ConsoleManager::ifProcessExists(std::string name) {
	bool flag;
	if (resourceManager.getScheduler()->getProcessByName(name) == nullptr) return false;
	return true;
}

bool ConsoleManager::isProcessFinished(std::string name) {
	if (ifProcessExists(name)) {
		std::shared_ptr<Process> foundProcess = resourceManager.getScheduler()->getProcessByName(name);
		return foundProcess->isFinished();
	}

	return false;
}
