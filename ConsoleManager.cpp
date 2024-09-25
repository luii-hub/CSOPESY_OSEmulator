#include "ConsoleManager.h"
#include <iostream>
#include <ctime>
#include <iomanip>


ConsoleManager::ConsoleManager() {
    // Constructor
}

std::string ConsoleManager::getCurrentTimestamp() {
    time_t now = time(0);
    tm localtm;
    localtime_s(&localtm, &now);
    char buffer[100];
    strftime(buffer, 100, "%m/%d/%Y, %I:%M:%S %p", &localtm);
    return std::string(buffer);
}

// Function to run a session in the background
void ConsoleManager::runSession(const std::string& name) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::lock_guard<std::mutex> lock(sessionMutex);
        if (!sessions[name].isActive) break;  // Stop if session is terminated
        if (sessions[name].currentLine < sessions[name].totalLine) {
            sessions[name].currentLine++;  // Simulate processing
        }
    }
}

// Start a new session
void ConsoleManager::startSession(const std::string& name) {
    std::lock_guard<std::mutex> lock(sessionMutex);
    if (name.empty()) {
        std::cout << "Error: Missing process name. Usage: screen -s <name>\n";
        return;
    }
    if (sessions.find(name) != sessions.end()) {
        std::cout << "Session with name '" << name << "' already exists.\n";
        return;
    }
    ScreenSession newSession;
    newSession.processName = name;
    newSession.currentLine = 0;
    newSession.totalLine = 100;
    newSession.timestamp = getCurrentTimestamp();
    newSession.isActive = true;
    sessions[name] = newSession;

    // Start session in background thread
    sessionThreads[name] = std::thread(&ConsoleManager::runSession, this, name);
    sessionThreads[name].detach();  // Detach thread to run independently
    std::cout << "Started new session '" << name << "'\n";
}

void ConsoleManager::resumeSession(const std::string& name) {
    std::lock_guard<std::mutex> lock(sessionMutex);
    if (name.empty()) {
        std::cout << "Error: Missing process name. Usage: screen -r <name>\n";
        return;
    }
    if (sessions.find(name) == sessions.end()) {
        std::cout << "No session found with name '" << name << "'\n";
        return;
    }

    ScreenSession& session = sessions[name];

    // Display session details when resumed
    std::cout << "Resuming session '" << session.processName << "'\n";
    std::cout << "Current Line: " << session.currentLine << " / " << session.totalLine << "\n";
    std::cout << "Timestamp: " << session.timestamp << "\n";
    std::cout << "\nType 'exit' to return to the main menu.\n";

    // Enter the session loop - only allow 'exit' to return to the main menu
    std::string command;
    while (true) {
        std::getline(std::cin, command);

        if (command == "exit") {
            // Exit the session and return to main menu
            std::cout << "Returning to main menu...\n";
            break;
        }
        else {
            // Any other command is invalid while in the session
            std::cout << "Unknown command. Type 'exit' to return to the main menu.\n";
        }
    }
}


// List all active sessions
void ConsoleManager::listSessions() {
    std::lock_guard<std::mutex> lock(sessionMutex);
    if (sessions.empty()) {
        std::cout << "No active sessions.\n";
        return;
    }

    std::cout << "Active sessions:\n";
    for (const auto& pair : sessions) {
        const ScreenSession& session = pair.second;
        std::cout << "- " << session.processName << " | Current Line: " << session.currentLine
            << " / " << session.totalLine << " | Created: " << session.timestamp << "\n";
    }
}

// Terminate a session
void ConsoleManager::terminateSession(const std::string& name) {
    std::lock_guard<std::mutex> lock(sessionMutex);
    if (sessions.find(name) == sessions.end()) {
        std::cout << "No session found with name '" << name << "'\n";
        return;
    }
    sessions[name].isActive = false;
    std::cout << "Session '" << name << "' terminated.\n";
    sessions.erase(name);  // Remove session from map
}