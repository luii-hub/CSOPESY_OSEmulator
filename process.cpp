#include <iostream>
#include <map>
#include <thread>
#include <chrono>
#include <mutex>
#include "styles.h" 
#include "utilities.h"
#include "process.h"
#include "ConsoleManager.h"

using namespace std;

// Global instance of ConsoleManager to handle screen sessions
ConsoleManager consoleManager;


/**
 * @brief Executes the command entered by the user.
 *
 * This function takes the user input and executes the corresponding function
 * based on the command. It checks the command and calls helper functions
 * like `initialize()`, `screen()`, `scheduler_test()`, and others.
 *
 * @param command The command string entered by the user.
 */
void executeCommand(string command) {
    if (command == "initialize") {
        initialize();  // Calls the function to initialize the system
    }
    else if (command == "help") {
        helpInfo();  // Displays the help information
    }
    // Check if the command is to start a new screen session
    else if (command == "screen -s") {
        std::cout << "Error: Missing process name. Usage: screen -s <name>\n";
    }
    // Check if the command is to resume an existing screen session
    else if (command == "screen -r") {
        std::cout << "Error: Missing process name. Usage: screen -r <name>\n";
    }
    // Command to start a new screen session with a specified name
    else if (command.rfind("screen -s", 0) == 0) {
        std::string processName = command.substr(10);  // Extract the process name
        consoleManager.startSession(processName);  // Start the session
    }
    // Command to resume an existing screen session with a specified name
    else if (command.rfind("screen -r", 0) == 0) {
        std::string processName = command.substr(10);  // Extract the process name
        consoleManager.resumeSession(processName);  // Resume the session
    }
    // Command to list all active screen sessions
    else if (command == "screen -ls") {
        consoleManager.listSessions();  // List all active sessions
    }
    else if (command == "scheduler-test") {
        scheduler_test();  // Calls the scheduler test function
    }
    else if (command == "scheduler-stop") {
        scheduler_stop();  // Calls the function to stop the scheduler
    }
    else if (command == "report-util") {
        report_until();  // Calls the report generation utility
    }
    else if (command == "clear") {
        clear();  // Clears the screen
    }
    else if (command == "exit") {
        exit();  // Exits the program
    }
    else {
		cout << "Command not recognized. Type 'help' to see the list of available commands." << endl;
	}
}

/**
 * @brief Initializes the system or application.
 *
 * This function is a placeholder for the initialization logic of the system.
 * It currently outputs a message indicating that initialization is in progress.
 */
void initialize() {
    cout << "initialize command recognized. Doing something." << endl;
}

/* Depracated */
/**
 * @brief Handles screen-related functionality.
 *
 * This function deals with screen management commands such as starting, resuming,
 * and listing screen sessions. It processes the user input and calls the appropriate
 * methods from the ConsoleManager class.
 */
void screen() {
    std::string command;
    std::cout << "Enter screen command (-s, -r, -ls): ";
    std::getline(std::cin, command);  // Get the user input for screen commands
}

/**
 * @brief Runs a test on the scheduler.
 *
 * This function is a placeholder for testing the system's scheduling functionality.
 * It currently outputs a message indicating that the scheduler test is in progress.
 */
void scheduler_test() {
    cout << "scheduler-test command recognized. Doing something." << endl;
}

/**
 * @brief Stops the scheduler.
 *
 * This function is a placeholder for stopping the scheduler functionality.
 * It currently outputs a message indicating that the scheduler has been stopped.
 */
void scheduler_stop() {
    cout << "scheduler-stop command recognized. Doing something." << endl;
}

/**
 * @brief Runs a utility report.
 *
 * This function is a placeholder for generating or executing a report.
 * It currently outputs a message indicating that the report utility is running.
 */
void report_until() {
    cout << "report-util command recognized. Doing something." << endl;
}

/**
 * @brief Clears the console screen.
 *
 * This function clears the terminal screen using ANSI escape codes.
 * It then prints the application header and greets the user again.
 */
void clear() {
    cout << "\033[2J\033[H";  // ANSI escape code to clear the screen
    printHeader();  // Print the header again after clearing the screen
    greetUser();  // Greet the user after the screen is cleared
}

/**
 * @brief Clears the console screen without printing the header.
 *
 * This function clears the terminal screen using ANSI escape codes.
 */
void clearScreenAndHeader() {
    std::cout << "\033[2J\033[H";  // ANSI escape code to clear the screen
}

/**
 * @brief Exits the application.
 *
 * This function terminates the application. It calls the `exit()` function from
 * the standard library to stop the program execution.
 */
void exit() {
    exit(0);  // Terminate the program
}
