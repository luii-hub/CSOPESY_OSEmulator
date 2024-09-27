#ifndef CONSOLEMANAGER_H
#define CONSOLEMANAGER_H

#include <string>
#include <map>
#include <thread>
#include <mutex>
#include "ScreenSession.h"

/**
 * @brief The ConsoleManager class manages the lifecycle of screen sessions.
 * This class provides functionality to start, resume, list, and terminate sessions.
 * Each session simulates the execution of a process and tracks its progress.
 */
class ConsoleManager {
public:
    /**
     * @brief Constructor for ConsoleManager.
     * Initializes a ConsoleManager object.
     */
    ConsoleManager();

    /**
     * @brief Starts a new session with the specified name.
     * Checks if the session name already exists and runs the session in a background thread.
     *
     * @param name The name of the session to start.
     */
    void startSession(const std::string& name);

    /**
     * @brief Resumes an existing session with the specified name.
     * Displays the current status of the session and allows user interaction.
     *
     * @param name The name of the session to resume.
     */
    void resumeSession(const std::string& name);

    /**
     * @brief Lists all active sessions.
     * Displays each session's ID, process name, current line, total line, and creation timestamp.
     */
    void listSessions();

    /**
     * @brief Terminates a session with the specified name.
     * Marks the session as inactive and removes it from the list of active sessions.
     *
     * @param name The name of the session to terminate.
     */
    void terminateSession(const std::string& name);

private:
    /**
     * @brief Simulates the execution of a session.
     * Runs in a background thread and increments the `currentLine` until completion or termination.
     *
     * @param name The name of the session being run.
     */
    void runSession(const std::string& name);

    /**
     * @brief Gets the current system timestamp as a string.
     * Formats the timestamp as "MM/DD/YYYY, HH:MM:SS AM/PM".
     *
     * @return The current timestamp as a formatted string.
     */
    std::string getCurrentTimestamp();


    // Mutex for thread-safe access to the sessions map
    std::mutex sessionMutex;

    // A map that holds all active screen sessions, keyed by session name
    std::map<std::string, ScreenSession> sessions;

    // A map that stores the threads running the session processes
    std::map<std::string, std::thread> sessionThreads;

    // The ID for the next session to be created
    int nextSessionId = 1;
};

#endif // CONSOLEMANAGER_H
