#include <iostream>
#include "styles.h" 
#include "utilities.h"

using namespace std;

// Function Prototypes
void initialize() {
    cout << "initialize command recognized. Doing something." << endl;
}

void screen() {
    cout << "screen command recognized. Doing something." << endl;
}

void scheduler_test() {
    cout << "scheduler-test command recognized. Doing something." << endl;
}

void scheduler_stop() {
    cout << "scheduler-stop command recognized. Doing something." << endl;
}

void report_until() {
    cout << "report-util command recognized. Doing something." << endl;
}

void clear() {
    cout << "\033[2J\033[H";  // ANSI escape code to clear the screen
    printHeader();
    greetUser();
}

void exit() {
    exit(0);
}
