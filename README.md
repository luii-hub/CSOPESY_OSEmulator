# **OSEmulator Project**

## **Project Overview**

This project simulates an Operating System Emulator (OSEmulator) designed to manage multiple processes or screen sessions through a command-line interface (CLI). Users can interact with the system by entering commands to initialize the system, create and manage screen sessions, schedule tasks, and run utilities.

---

## **Project Members**

- **Luis Miguel Rana**
- **Mark Daniel Guttierrez**
- **Raico Madrinan**
- **Eun Ji Ha**

---

## **Files and Directory Structure**

### **Source Files**
| File              | Description                                                                                                                                                          |
|-------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **OSEmulator.cpp**| Contains the `main` function. This is where the program begins execution. It initializes the CLI, greets the user, and continuously waits for user input (commands).   |
| **process.cpp**   | Handles system initialization, screen management commands, and scheduler utilities. This file includes logic for running and managing system processes.                |
| **utilities.cpp** | Contains utility functions such as greeting the user, printing the application header, handling command execution, and testing console text styling.                    |
| **ConsoleManager.cpp**| Manages the life cycle of screen sessions. It allows for starting, resuming, listing, and terminating processes in background threads to simulate real execution.  |

### **Header Files**
| Header File           | Description                                                                                                                                                       |
|-----------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **process.h**         | Declares function prototypes for system initialization, screen management, and scheduler-related tasks. This includes initializing the system and handling screens. |
| **utilities.h**       | Declares utility function prototypes that support the application, such as printing headers, greeting users, and handling command execution.                        |
| **ConsoleManager.h**  | Declares the `ConsoleManager` class, which handles the creation, resumption, and listing of screen sessions. It manages all screen sessions using multithreading.   |
| **styles.h**          | Provides helper functions to style and format console output. This includes colorizing text, adding bold, underline, and other stylistic effects to console output.  |
