#include "ScreenSession.h"
#include <iostream>
#include <ctime>

/**
 * @brief Default constructor for ScreenSession.
 * Initializes default values for a session.
 */
ScreenSession::ScreenSession()
    : name("Unnamed"), processName("Unknown"), isRunning(false), isActive(true),
    totalLine(100), currentLine(0), sessionId(-1), timestamp(getCurrentTime()) {}

/**
 * @brief Constructor with session name.
 * Initializes a session with the given name and default values.
 *
 * @param sessionName The name of the session.
 */
ScreenSession::ScreenSession(const std::string& sessionName)
    : name(sessionName), processName(sessionName), isRunning(false), isActive(true),
    totalLine(100), currentLine(0), sessionId(-1), timestamp(getCurrentTime()) {}

/**
 * @brief Move constructor for ScreenSession.
 * Transfers ownership of session data from another session.
 *
 * @param other The session to move from.
 */
ScreenSession::ScreenSession(ScreenSession&& other) noexcept
    : name(std::move(other.name)),
    processName(std::move(other.processName)),
    sessionId(other.sessionId),
    timestamp(std::move(other.timestamp)),
    isRunning(other.isRunning),
    isActive(other.isActive),
    totalLine(other.totalLine),
    currentLine(other.currentLine),
    sessionThread(std::move(other.sessionThread)),
    sessionHistory(std::move(other.sessionHistory)) {
    other.isRunning = false;
    other.isActive = false;
}

/**
 * @brief Move assignment operator for ScreenSession.
 * Transfers ownership of session data from another session.
 *
 * @param other The session to move from.
 * @return The updated ScreenSession object.
 */
ScreenSession& ScreenSession::operator=(ScreenSession&& other) noexcept {
    if (this != &other) {
        name = std::move(other.name);
        processName = std::move(other.processName);
        sessionId = other.sessionId;
        timestamp = std::move(other.timestamp);
        isRunning = other.isRunning;
        isActive = other.isActive;
        totalLine = other.totalLine;
        currentLine = other.currentLine;
        sessionThread = std::move(other.sessionThread);
        sessionHistory = std::move(other.sessionHistory);

        other.isRunning = false;
        other.isActive = false;
    }
    return *this;
}

/**
 * @brief Destructor for ScreenSession.
 * Joins the session thread if it is still running.
 */
ScreenSession::~ScreenSession() {
    if (sessionThread.joinable()) {
        sessionThread.join();
    }
}

/**
 * @brief Getter for process name.
 *
 * @return The name of the process.
 */
std::string ScreenSession::getProcessName() const {
    return processName;
}

/**
 * @brief Getter for session ID.
 *
 * @return The session ID.
 */
int ScreenSession::getSessionId() const {
    return sessionId;
}

/**
 * @brief Getter for session creation timestamp.
 *
 * @return The timestamp as a string.
 */
std::string ScreenSession::getTimestamp() const {
    return timestamp;
}

/**
 * @brief Getter for isActive status.
 *
 * @return True if the session is active, false otherwise.
 */
bool ScreenSession::getIsActive() const {
    return isActive;
}

/**
 * @brief Getter for current line.
 *
 * @return The current line being processed.
 */
int ScreenSession::getCurrentLine() const {
    return currentLine;
}

/**
 * @brief Getter for total line.
 *
 * @return The total number of lines in the session.
 */
int ScreenSession::getTotalLine() const {
    return totalLine;
}

/**
 * @brief Setter for session ID.
 *
 * @param id The new session ID.
 */
void ScreenSession::setSessionId(int id) {
    sessionId = id;
}

/**
 * @brief Setter for isActive status.
 *
 * @param status The new status of the session.
 */
void ScreenSession::setIsActive(bool status) {
    isActive = status;
}

/**
 * @brief Setter for current line.
 *
 * @param line The new current line number.
 */
void ScreenSession::setCurrentLine(int line) {
    currentLine = line;
}

/**
 * @brief Resume the session and print its history.
 */
void ScreenSession::resume() {
    if (isActive) {
        std::cout << "Resuming session '" << processName << "'...\n";
        printHistory();
        std::cout << "Session is running. Current line: " << currentLine
            << " / " << totalLine << std::endl;
    }
}

/**
 * @brief Add a command to the session history.
 *
 * @param command The command to add.
 */
void ScreenSession::addToHistory(const std::string& command) {
    sessionHistory.push_back(command);
}

/**
 * @brief Print the history of commands entered during the session.
 */
void ScreenSession::printHistory() const {
    for (const auto& command : sessionHistory) {
        std::cout << "root:\\> " << command << std::endl;
    }
}

/**
 * @brief Get the current system time as a string.
 *
 * @return The formatted current time.
 */
std::string ScreenSession::getCurrentTime() const {
    time_t now = time(0);
    tm localtm;
    localtime_s(&localtm, &now);
    char buffer[100];
    strftime(buffer, 100, "%m/%d/%Y, %I:%M:%S %p", &localtm);
    return std::string(buffer);
}
