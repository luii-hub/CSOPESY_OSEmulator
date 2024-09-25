// OSEmulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <string>
#include <stdlib.h>
#include "styles.h"  // Include the header for color and style functions
#include "utilities.h"  // Include the header for utility functions
#include "process.h"  // Include the header for process functions
#include "ConsoleManager.h"  // Include the header for console management functions

using namespace std;


int main()
{
    string command;

    //Print ASCII header
    printHeader();

    // Greet the user
    greetUser();

    // Uncomment to test color and style functions (Author Notes: used for test color and style functions. This is not a part of the assignment)
    // testStyleFunctions();

    while (true) {
        cout << color_white("Enter a command: ");
        std::getline(cin, command);
        executeCommand(command);
    }

}

