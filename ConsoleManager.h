#ifndef CONSOLEMANAGER_H
#define CONSOLEMANAGER_H

#include <string>
#include <map>
#include <thread>
#include <chrono>
#include <mutex>

/*
    Struct to hold information about each screen session.
    Fields:
        - processName: The name of the session or process.
        - currentLine: The current instruction being executed.
        - totalLine: Total number of instructions in the process.
        - timestamp: The time when the session was created.
        - isActive: A flag indicating if the session is still active.
*/
struct ScreenSession {
    std::string processName;
    int currentLine = 0;      // Initialize currentLine to 0
    int totalLine = 100;      // Initialize totalLine to 100 (or default value)
    std::string timestamp;
    bool isActive = true;     // Initialize isActive to true by default
};

/*
    ConsoleManager class manages multiple screen sessions.
    It allows starting, resuming, listing, and terminating screen sessions.
*/
class ConsoleManager {
public:
    ConsoleManager();  // Constructor

    /*
        Start a new session with the specified name.
        Creates a new session, initializes it, and runs it in a detached thread.
        Param: name - the name of the session.
    */
    void startSession(const std::string& name);

    /*
        Resume an existing session with the specified name.
        Displays the current status of the session and restricts the user to the session until they exit.
        Param: name - the name of the session.
    */
    void resumeSession(const std::string& name);

    /*
        List all active sessions with details (process name, current line, total line, and timestamp).
    */
    void listSessions();

    /*
        Terminate a session by marking it as inactive and removing it from the active list.
        Param: name - the name of the session to terminate.
    */
    void terminateSession(const std::string& name);

private:
    // Map of session names to ScreenSession objects
    std::map<std::string, ScreenSession> sessions;

    // Map of session names to their corresponding threads
    std::map<std::string, std::thread> sessionThreads;

    // Mutex to ensure thread-safe access to sessions and threads
    std::mutex sessionMutex;

    /*
        Function that simulates running the session by incrementing the current line until the process is complete.
        Param: name - the name of the session to run.
    */
    void runSession(const std::string& name);

    /*
        Get the current system timestamp as a formatted string.
        Return: The current timestamp in "MM/DD/YYYY, HH:MM:SS AM/PM" format.
    */
    std::string getCurrentTimestamp();
};

#endif
