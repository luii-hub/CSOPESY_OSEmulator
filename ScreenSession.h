#ifndef SCREEN_SESSION_H
#define SCREEN_SESSION_H

#include <string>
#include <vector>
#include <thread>

/**
 * @brief The ScreenSession class simulates a session process.
 * It tracks the session's name, status, current progress, and command history.
 * Each session runs on its own thread to simulate execution.
 */
class ScreenSession {
public:
    /**
     * @brief Default constructor.
     * Initializes the session with default values.
     */
    ScreenSession();

    /**
     * @brief Constructor with session name.
     * Initializes the session with a specific name.
     *
     * @param sessionName The name of the session.
     */
    ScreenSession(const std::string& sessionName);

    /**
     * @brief Move constructor for ScreenSession.
     * Transfers ownership of session data from another session.
     *
     * @param other The session to move from.
     */
    ScreenSession(ScreenSession&& other) noexcept;

    /**
     * @brief Move assignment operator for ScreenSession.
     * Transfers ownership of session data from another session.
     *
     * @param other The session to move from.
     * @return The updated ScreenSession object.
     */
    ScreenSession& operator=(ScreenSession&& other) noexcept;

    /**
     * @brief Destructor.
     * Joins the session thread if it is still running.
     */
    ~ScreenSession();

    // Disable copying
    ScreenSession(const ScreenSession&) = delete;
    ScreenSession& operator=(const ScreenSession&) = delete;

    // Getter methods
    std::string getProcessName() const;
    int getSessionId() const;
    std::string getTimestamp() const;
    bool getIsActive() const;
    int getCurrentLine() const;
    int getTotalLine() const;

    // Setter methods
    void setSessionId(int id);
    void setIsActive(bool status);
    void setCurrentLine(int line);

    // Other methods
    void resume();
    void addToHistory(const std::string& command);
    void printHistory() const;

private:
    std::string name;
    std::string processName;
    int sessionId;
    std::string timestamp;
    bool isRunning;
    bool isActive;
    int totalLine;
    int currentLine;
    std::thread sessionThread;
    std::vector<std::string> sessionHistory; // Stores commands entered during the session

    /**
     * @brief Get the current system time as a string.
     *
     * @return The formatted current time.
     */
    std::string getCurrentTime() const;
};

#endif // SCREEN_SESSION_H
