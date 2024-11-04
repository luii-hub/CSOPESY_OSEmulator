# **OSEmulator Project**

This project simulates an Operating System Emulator (OSEmulator) designed to manage multiple processes or screen sessions through a command-line interface (CLI). Users can interact with the system by entering commands to initialize the system, create and manage screen sessions, schedule tasks, and run utilities.

## **Members**

- **Luis Miguel Rana**
- **Mark Daniel Guttierrez**
- **Raico Madrinan**
- **Eun Ji Ha**

## **How to run** 
1. **Install Required Software**:
   - Ensure you have the following software installed:
     - **Visual Studio 2022** with the **Desktop development with C++** workload.
     - **Git** (for cloning the repository)
      
2. **Clone the Repository**:
   - Open Visual Studio 2022, select "Clone a repository"
   - In the GitHub Repo, copy the repository link then paste the link inside Visual Studio 2022
   - 
3. **Build and Run**
   -   Navigate to the Solution Explorer thens select the file ```bash CSOPESY_OSEmulator.cpp```
   -   ```bash CSOPESY_OSEmulator.cpp``` is the **entry class file**, where the main fucntion is located
   -   Build and Run the project.


---

## **Files and Directory Structure**

### **Source Files**
| File              | Description                                                                                                                                                          |
|-------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **CSOPESY_OSEmulator**| Contains the `main` function. This is where the program begins execution where it instantiates the ConsoleManager   |
| **ConsoleManager**   | This class manages the system configuration, including reading from a configuration file (config.txt) and providing access to configuration parameters.                |
| **ConfigurationManager** | This class manages the system configuration, including reading from a configuration file (config.txt) and providing access to configuration parameters.                   |
| **ResourceManager**| This class manages the creation, scheduling, memory allocation, and resource monitoring for processes. It interacts with the ConsoleManager, Scheduler, and MemoryManager to handle resource distribution and utilization within the system.  |
| **AConsole**| This abstract base class defines a generic console interface with methods for execution, display, and processing. It is designed to be inherited by specific console implementations, like MainMenu, processScreens.   |
| **MainMenu**   | This class represents the main menu screen, providing the user with a command-line interface to interact with the console manager, access different screens, and manage processes.                |
| **ProcessScreen** | This class represents the console screen for a specific process, allowing users to view process details and interact with the process through commands.                   |
| **Process** | This class represents a single process, tracking its execution state, memory usage, and core assignment. It provides methods for executing instructions and checking the process's status.  |
| **CoreWorker**| This class represents a single CPU core responsible for executing processes. It manages process assignments, tracks CPU usage, and interacts with the scheduler to reassign or complete processes   |
| **Scheduler**   | This class manages CPU scheduling, assigning processes to cores based on the scheduling algorithm specified in the configuration. It supports both First-Come, First-Served (FCFS) and Round-Robin (RR) scheduling.                |
| **Styles** | This class simply contains styling and formatting functions used for the UI                   |
| **ResourceManager**| This class manages the creation, scheduling, memory allocation, and resource monitoring for processes. It interacts with the ConsoleManager, Scheduler, and MemoryManager to handle resource distribution and utilization within the system.  |

