#include "ConsoleManager.h"
#include "process.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>

/**
 * @brief ConsoleManager constructor.
 * Initializes a ConsoleManager object.
 */
ConsoleManager::ConsoleManager() {
    // Initialize if necessary
}

/**
 * @brief Get the current system timestamp as a string.
 * Formats the time as "MM/DD/YYYY, HH:MM:SS AM/PM".
 *
 * @return The current timestamp as a formatted string.
 */
std::string ConsoleManager::getCurrentTimestamp() {
    time_t now = time(0);
    tm localtm;
    localtime_s(&localtm, &now);
    char buffer[100];
    strftime(buffer, 100, "%m/%d/%Y, %I:%M:%S %p", &localtm);
    return std::string(buffer);
}

/**
 * @brief Simulate the execution of a session.
 * Runs in a background thread, increments the `currentLine`, and terminates if necessary.
 *
 * @param name The name of the session being run.
 */
void ConsoleManager::runSession(const std::string& name) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::lock_guard<std::mutex> lock(sessionMutex);

        if (!sessions[name].getIsActive()) break;

        if (sessions[name].getCurrentLine() < sessions[name].getTotalLine()) {
            sessions[name].setCurrentLine(sessions[name].getCurrentLine() + 1);
        }
    }
}

/**
 * @brief Start a new session with the given name.
 * Initializes the session, assigns it a unique ID, and runs it in a background thread.
 *
 * @param name The name of the session to start.
 */
void ConsoleManager::startSession(const std::string& name) {
    std::lock_guard<std::mutex> lock(sessionMutex);

    if (name.empty()) {
        std::cout << "Error: Missing process name. Usage: screen -s <name>\n";
        return;
    }

    if (sessions.find(name) != sessions.end()) {
        std::cout << "Session '" << name << "' already exists.\n";
        return;
    }

    ScreenSession newSession(name);
    newSession.setSessionId(nextSessionId++);
    sessions[name] = std::move(newSession);

    sessionThreads[name] = std::thread(&ConsoleManager::runSession, this, name);
    sessionThreads[name].detach();

    std::cout << "Started new session '" << sessions[name].getProcessName()
        << "' with ID: " << sessions[name].getSessionId() << std::endl;
}

/**
 * @brief Resume an existing session.
 * Clears the screen, restores the session's history, and allows interaction.
 *
 * @param name The name of the session to resume.
 */
void ConsoleManager::resumeSession(const std::string& name) {
    std::lock_guard<std::mutex> lock(sessionMutex);

    if (sessions.find(name) == sessions.end()) {
        std::cout << "No session found with name '" << name << "'\n";
        return;
    }

    clearScreenAndHeader();

    ScreenSession& session = sessions[name];

    if (!session.getIsActive()) {
        session.setIsActive(true);
    }

    // Print session history and status
    session.resume();

    // Enter a loop that allows interaction with only the "exit" command
    std::string command;
    while (true) {
        std::cout << "root:\\> ";  // Custom prompt for the process screen
        std::getline(std::cin, command);

        if (command == "exit") {
            clear();
            std::cout << "Returning to main menu...\n";
            break;
        }
        else {
            session.addToHistory(command); // Save the entered command in the session history
            std::cout << "Unknown command. Type 'exit' to return to the main menu.\n";
        }
    }
}

/**
 * @brief List all active sessions.
 * Displays the session ID, process name, and timestamp.
 */
void ConsoleManager::listSessions() {
    std::lock_guard<std::mutex> lock(sessionMutex);

    if (sessions.empty()) {
        std::cout << "No active sessions.\n";
        return;
    }

    for (const auto& pair : sessions) {
        const ScreenSession& session = pair.second;
        std::cout << "- ID: " << session.getSessionId()
            << " | " << session.getProcessName()
            << " | Created: " << session.getTimestamp() << "\n";
    }
}

/**
 * @brief Terminate a session by name.
 * Marks the session as inactive and removes it from the list of active sessions.
 *
 * @param name The name of the session to terminate.
 */
void ConsoleManager::terminateSession(const std::string& name) {
    std::lock_guard<std::mutex> lock(sessionMutex);

    if (sessions.find(name) == sessions.end()) {
        std::cout << "No session found with name '" << name << "'\n";
        return;
    }

    sessions[name].setIsActive(false);
    std::cout << "Session '" << name << "' terminated.\n";
    sessions.erase(name);
}
