// OSEmulator.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>
#include <stdlib.h>
#include "styles.h"  // Include the header for color and style functions
#include "utilities.h"  // Include the header for utility functions
#include "process.h"  // Include the header for process functions
#include "ConsoleManager.h"  // Include the header for console management functions

using namespace std;

/**
 * @brief The main function of the OSEmulator application.
 *
 * This function initializes the command-line interface (CLI) by printing a header and
 * greeting the user. It then enters an infinite loop where it continuously waits
 * for the user to enter a command and executes the corresponding function.
 *
 * The main loop processes user input through the `executeCommand()` function, which
 * is defined in `utilities.cpp`. It checks the command and routes it to appropriate
 * handlers like screen management, scheduler utilities, etc.
 *
 * The program will continue running until the user explicitly exits using the 'exit' command.
 */
int main()
{
    string command;  // Variable to store user input commands

    // Print ASCII header to provide a visual introduction to the application
    printHeader();

    // Greet the user with a welcome message and instructions
    greetUser();

    // Uncomment the line below to test color and style functions
    // This is for testing purposes and is not part of the final assignment
    // testStyleFunctions();

    // Main application loop
    // Continuously prompts the user for commands until the application is exited
    while (true) {
        // Prompt the user to enter a command
        cout << color_white("Enter a command: ");
        std::getline(cin, command);  // Capture user input as a string

        // Pass the command to the executeCommand function for processing
        executeCommand(command);
    }

}
