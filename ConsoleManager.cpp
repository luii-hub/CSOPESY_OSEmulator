#include "ConsoleManager.h"
#include <iostream>
#include <ctime>
#include <iomanip>

/*
    ConsoleManager constructor.
    Initializes the ConsoleManager object with no additional actions.
*/
ConsoleManager::ConsoleManager() {
    // Constructor
}

/*
    Get the current system timestamp as a string.
    This function formats the time in "MM/DD/YYYY, HH:MM:SS AM/PM".
    Return: The current timestamp as a formatted string.
*/
std::string ConsoleManager::getCurrentTimestamp() {
    time_t now = time(0); // Get current system time
    tm localtm;
    localtime_s(&localtm, &now); // Convert to local time
    char buffer[100];
    strftime(buffer, 100, "%m/%d/%Y, %I:%M:%S %p", &localtm); // Format the time
    return std::string(buffer); // Return the formatted string
}

/*
    Function that simulates the execution of a session.
    It runs in a background thread and increments `currentLine` until it reaches `totalLine` or until the session is terminated.
    Param: name - the name of the session being run.
*/
void ConsoleManager::runSession(const std::string& name) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate a delay between each line execution
        std::lock_guard<std::mutex> lock(sessionMutex); // Lock mutex to ensure thread safety

        // If session is no longer active, exit the loop
        if (!sessions[name].isActive) break;

        // Increment currentLine if it's less than totalLine
        if (sessions[name].currentLine < sessions[name].totalLine) {
            sessions[name].currentLine++;  // Simulate process execution by incrementing the line number
        }
    }
}

/*
    Start a new session with the specified name.
    This function checks for valid input and whether the session name already exists.
    If valid, it initializes a new session and runs it in a detached background thread.
    Param: name - the name of the session to start.
*/
void ConsoleManager::startSession(const std::string& name) {
    std::lock_guard<std::mutex> lock(sessionMutex); // Lock mutex to ensure thread safety

    // Check if the session name is provided
    if (name.empty()) {
        std::cout << "Error: Missing process name. Usage: screen -s <name>\n";
        return;
    }

    // Check if the session name already exists
    if (sessions.find(name) != sessions.end()) {
        std::cout << "Session with name '" << name << "' already exists.\n";
        return;
    }

    // Create a new session
    ScreenSession newSession;
    newSession.processName = name;
    newSession.currentLine = 0; // Start from the first line
    newSession.totalLine = 100; // Set the total number of lines to 100
    newSession.timestamp = getCurrentTimestamp(); // Get the session creation timestamp
    newSession.isActive = true; // Mark the session as active
    sessions[name] = newSession; // Store the new session in the sessions map

    // Start the session in a background thread and detach it
    sessionThreads[name] = std::thread(&ConsoleManager::runSession, this, name);
    sessionThreads[name].detach();  // Detach thread to allow it to run independently

    std::cout << "Started new session '" << name << "'\n"; // Confirm that the session has started
}

/*
    Resume an existing session with the specified name.
    Displays the current status of the session (process name, current line, total line, and timestamp).
    The user can only exit the session by typing "exit".
    Param: name - the name of the session to resume.
*/
void ConsoleManager::resumeSession(const std::string& name) {
    std::lock_guard<std::mutex> lock(sessionMutex); // Lock mutex to ensure thread safety

    // Check if the session name is provided
    if (name.empty()) {
        std::cout << "Error: Missing process name. Usage: screen -r <name>\n";
        return;
    }

    // Check if the session exists
    if (sessions.find(name) == sessions.end()) {
        std::cout << "No session found with name '" << name << "'\n";
        return;
    }

    // Access the session data
    ScreenSession& session = sessions[name];

    // Display the session details
    std::cout << "Resuming session '" << session.processName << "'\n";
    std::cout << "Current Line: " << session.currentLine << " / " << session.totalLine << "\n";
    std::cout << "Timestamp: " << session.timestamp << "\n";
    std::cout << "\nType 'exit' to return to the main menu.\n";

    // Enter a loop that only accepts 'exit' as a valid command to return to the main menu
    std::string command;
    while (true) {
        std::getline(std::cin, command); // Wait for user input

        // If the user types 'exit', break the loop and return to the main menu
        if (command == "exit") {
            std::cout << "Returning to main menu...\n";
            break;
        }
        else {
            // If any other command is entered, notify the user that only 'exit' is valid
            std::cout << "Unknown command. Type 'exit' to return to the main menu.\n";
        }
    }
}

/*
    List all active sessions.
    Displays the process name, current line, total line, and the creation timestamp for each active session.
*/
void ConsoleManager::listSessions() {
    std::lock_guard<std::mutex> lock(sessionMutex); // Lock mutex to ensure thread safety

    // If no sessions are active, inform the user
    if (sessions.empty()) {
        std::cout << "No active sessions.\n";
        return;
    }

    // Display each session's details
    std::cout << "Active sessions:\n";
    for (const auto& pair : sessions) {
        const ScreenSession& session = pair.second;
        std::cout << "- " << session.processName << " | Current Line: " << session.currentLine
            << " / " << session.totalLine << " | Created: " << session.timestamp << "\n";
    }
}

/*
    Terminate a session with the specified name.
    Marks the session as inactive and removes it from the list of active sessions.
    Param: name - the name of the session to terminate.
*/
void ConsoleManager::terminateSession(const std::string& name) {
    std::lock_guard<std::mutex> lock(sessionMutex); // Lock mutex to ensure thread safety

    // Check if the session exists
    if (sessions.find(name) == sessions.end()) {
        std::cout << "No session found with name '" << name << "'\n";
        return;
    }

    // Mark the session as inactive and remove it from the sessions map
    sessions[name].isActive = false;
    std::cout << "Session '" << name << "' terminated.\n";
    sessions.erase(name);  // Remove session from the map
}
