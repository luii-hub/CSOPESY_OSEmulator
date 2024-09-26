#include <string>
#include "utilities.h"
#include "styles.h"
#include "process.h"
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <chrono>

using namespace std;

/**
 * @brief Prints the application header.
 *
 * This function prints a visually styled header that uses color and styles
 * to display the name of the application in a visually appealing format.
 */
void printHeader() {
    cout << color_blue(style_bold(style_blink(R"( 
 _____________________________________________________                                                   
|   _____  _____  ____  _____  ______ _____ __     __ |
|  / ____|/ ____|/ __ \|  __ \|  ____/ ____|\ \   / / |
| | |    | (___ | |  | | |__) | |__  | (___  \ \_/ /  |
| | |     \___ \| |  | |  ___/|  __|  \___ \  \   /   |
| | |____ ____) | |__| | |    | |____ ____) |  | |    |
|  \_____|_____/ \____/|_|    |______|_____/   |_|    |                                                     
 -----------------------------------------------------
    )"))) << endl;
}

/**
 * @brief Greets the user with a welcome message and a guide to available commands.
 *
 * This function prints a welcome message to the user along with a helpful message
 * instructing the user to type 'help' to see a list of available commands.
 */
void greetUser() {
    string welcome = "Hello, Welcome to CSOPESY command line!";
    string guide = "Type 'help' to see a list of commands";
    cout << color_green(welcome) << endl;  // Print welcome message in green
    cout << color_bright_yellow(guide) << endl;  // Print guide message in yellow
}

/**
 * @brief Displays the list of available commands.
 *
 * This function prints a list of commands available to the user, along with
 * descriptions of what each command does. It serves as a guide for interacting with the CLI.
 */
void helpInfo() {
    cout << R"(
List of commands:
|-- initialize           : Initialize the system
|-- screen               : Screen management commands
|   |-- screen -ls       : List all sessions
|   |-- screen -s <name> : Start a new screen
|   |-- screen -r <name> : Resume a screen
|-- scheduler-test       : Test the scheduler
|-- scheduler-stop       : Stop the scheduler
|-- report-util          : Generate a report
|-- clear                : Clear the screen
|-- exit                 : Exit the program
)" << endl;
}

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
    else if (command == "screen") {
        screen();  // Opens the screen management system
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
}

/**
 * @brief Returns the current system time as a formatted string.
 *
 * This function retrieves the current time from the system and returns it
 * as a string formatted as "MM/DD/YYYY, HH:MM:SS AM/PM". It uses `localtime_s`
 * for thread-safe time conversion.
 *
 * @return The current time as a string in "MM/DD/YYYY, HH:MM:SS AM/PM" format.
 */
std::string currentTime() {
    time_t now = time(0);  // Get the current system time
    tm localtm;
    localtime_s(&localtm, &now);  // Use thread-safe time conversion
    char buffer[100];
    strftime(buffer, 100, "%m/%d/%Y, %I:%M:%S %p", &localtm);  // Format the time
    return std::string(buffer);  // Return the formatted string
}

/**
 * @brief Tests the color and style functions.
 *
 * This function prints a series of test messages in different colors and styles
 * to showcase the available styles such as bold, underline, and various text colors.
 */
void testStyleFunctions() {
    cout << "Testing color and style functions" << endl;
    cout << color_red("this is red text") << endl;
    cout << color_green("this is green text") << endl;
    cout << color_yellow("this is yellow text") << endl;
    cout << color_blue("this is blue text") << endl;
    cout << color_magenta("this is magenta text") << endl;
    cout << color_cyan("this is cyan text") << endl;
    cout << color_white("this is white text") << endl;
    cout << style_bold("this is bold text") << endl;
    cout << style_underline("this is underlined text") << endl;
    cout << style_blink("this is blinking text") << endl;
    cout << style_dim("this is dim text") << endl;
    cout << style_italic("this is italic text") << endl;
    cout << style_inverse("this is inverse text") << endl;
    cout << style_hidden("this is hidden text") << endl;
    cout << style_strikethrough("this is strikethrough text") << endl;
    cout << style_double_underline("this is double underlined text") << endl;
    cout << style_overline("this is overlined text") << endl;
}
