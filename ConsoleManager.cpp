#include "ConsoleManager.h"       // Include the header file for ConsoleManager class
#include "MainMenu.h"             // Include the MainMenu class
#include "ConfigurationManager.h" // Include the ConfigurationManager class
#include "Scheduler.h"            // Include the Scheduler class
#include "Process.h"              // Include the Process class
#include "ProcessScreen.h"        // Include the ProcessScreen class

#include <random>                 // Include random for random functionalities if needed

// Constructor for ConsoleManager
ConsoleManager::ConsoleManager() {
	auto MAIN_MENU = std::make_shared<MainMenu>();          // Create a shared pointer to MainMenu object
	consoles[MAIN_MENU->getName()] = MAIN_MENU;             // Add MAIN_MENU to the consoles map with its name as the key

	currentConsole = MAIN_MENU;                             // Set currentConsole to MAIN_MENU, the initial console
}

// Destructor for ConsoleManager (empty because shared_ptr handles cleanup)
ConsoleManager::~ConsoleManager()
{
}

// Main loop function to execute the current console
void ConsoleManager::run() {
	if (currentConsole) {                                   // Check if there is a current console set
		currentConsole->onExecute();                        // Execute the current console's main function
	}
}

// Function to switch between different console screens
void ConsoleManager::switchScreen(const std::string consoleName) {

	// Check if the consoleName starts with "PROCESS_SCREEN_"
	if (consoleName.substr(0, 15) == "PROCESS_SCREEN_") {
		std::string processName = consoleName.substr(15);   // Extract the process name from the consoleName

		if (resourceManager.processExists(processName)) {   // Check if the process exists

			std::shared_ptr<Process> process = resourceManager.findProcessByName(processName); // Retrieve the process

			if (!process->isFinished()) {                   // Check if the process is still running
				previousConsole = currentConsole;           // Store current console in previousConsole
				currentConsole = consoles[consoleName];     // Set currentConsole to the new console
				system("cls");                              // Clear the console screen (Windows-specific)
				currentConsole->onExecute();                // Execute the new console's main function
			}
			else {
				std::cerr << "Process " << processName << " has already finished." << std::endl; // Output error if process finished
			}
		}
		else {
			std::cerr << "Process " << processName << " not found." << std::endl; // Output error if process not found
		}
	}

	// Handle switching to non-process screens
	else {
		if (consoles.find(consoleName) != consoles.end()) { // Check if console exists in the consoles map
			previousConsole = currentConsole;               // Store current console in previousConsole
			currentConsole = consoles[consoleName];         // Set currentConsole to the specified console
			system("cls");                                  // Clear the console screen
			currentConsole->onExecute();                    // Execute the new console's main function
		}
		else {
			std::cerr << "Console " << consoleName << " not found." << std::endl; // Output error if console not found
		}
	}
}

// Initialize ConfigurationManager and ResourceManager
void ConsoleManager::setInitialized() {
	if (configManager.initialize() && resourceManager.initialize(&configManager)) { // Initialize both managers
		std::cout << "Initialization successful..." << std::endl; // Output success message
	}
}

// Getter for ConfigurationManager by reference
ConfigurationManager& ConsoleManager::getConfigurationManager() {
	return configManager;                                    // Return reference to configManager
}

// Getter for consoles map, returning by const reference to prevent modification
const std::unordered_map<std::string, std::shared_ptr<AConsole>>& ConsoleManager::getConsoles() const {
	return consoles;                                         // Return reference to consoles map
}

// Add a new console to the consoles map
void ConsoleManager::addConsole(std::shared_ptr<AConsole> console) {
	consoles[console->getName()] = console;                  // Insert console into the map with its name as the key
}

// Return to the previous console screen
void ConsoleManager::returnToPreviousScreen() {
	if (previousConsole) {                                   // Check if a previous console exists
		currentConsole = previousConsole;                    // Set current console to previous console
		previousConsole = nullptr;                           // Clear previousConsole pointer
		system("cls");                                       // Clear the console screen
		currentConsole->onExecute();                         // Execute the previous console's main function
	}
	else {
		std::cerr << "No previous screen to return to." << std::endl; // Output error if no previous screen
	}
}

// Getter for ResourceManager by reference
ResourceManager& ConsoleManager::getResourceManager() {
	return resourceManager;                                  // Return reference to resourceManager
}

// Create a new process screen and add it to the console manager
void ConsoleManager::createProcessScreen(const std::string processName) {
	std::shared_ptr<Process> processPointer = resourceManager.createProcess(processName); // Create a new process

	auto processScreen = std::make_shared<ProcessScreen>(processPointer); // Create a new ProcessScreen for the process

	addConsole(processScreen);                               // Add process screen to consoles map
	// Switch to process screen
	switchScreen(processScreen->getName());
}

// Display the status of resources (delegates to ResourceManager)
void ConsoleManager::displayStatus() {
	resourceManager.displayStatus();                         // Call displayStatus on the resourceManager
}

// Check if a process with a given name exists
bool ConsoleManager::ifProcessExists(std::string name) {
	return resourceManager.getScheduler()->getProcessByName(name) != nullptr; // Return true if process is found
}

// Check if a process with a given name is finished
bool ConsoleManager::isProcessFinished(std::string name) {
	if (ifProcessExists(name)) {                             // Check if process exists
		std::shared_ptr<Process> foundProcess = resourceManager.getScheduler()->getProcessByName(name); // Retrieve process
		return foundProcess->isFinished();                   // Return whether the process is finished
	}

	return false;                                            // Return false if process doesn't exist
}
