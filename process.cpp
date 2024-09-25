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

ConsoleManager consoleManager;


// Function Prototypes
void initialize() {
    cout << "initialize command recognized. Doing something." << endl;
}

void screen() {
    std::string command;
    std::cout << "Enter screen command (-s, -r, -ls): ";
    std::getline(std::cin, command);

    if (command == "screen -s") {
        std::cout << "Error: Missing process name. Usage: screen -s <name>\n";
    }
    else if (command == "screen -r") {
        std::cout << "Error: Missing process name. Usage: screen -r <name>\n";
    }
    else if (command.rfind("screen -s", 0) == 0) {
        std::string processName = command.substr(10);  // Extract process name
        consoleManager.startSession(processName);
    }
    else if (command.rfind("screen -r", 0) == 0) {
        std::string processName = command.substr(10);  // Extract process name
        consoleManager.resumeSession(processName);
    }
    else if (command == "screen -ls") {
        consoleManager.listSessions();
    }
    else {
        std::cout << "Unknown screen command.\n";
    }
}

void scheduler_test() {
    cout << "scheduler-test command recognized. Doing something." << endl;
}

void scheduler_stop() {
    cout << "scheduler-stop command recognized. Doing something." << endl;
}

void report_until() {
    cout << "report-util command recognized. Doing something." << endl;
}

void clear() {
    cout << "\033[2J\033[H";  // ANSI escape code to clear the screen
    printHeader();
    greetUser();
}

void exit() {
    exit(0);
}
