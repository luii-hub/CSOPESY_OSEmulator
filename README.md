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
   
3. **Build and Run**
   -   Navigate to the Solution Explorer thens select the file ```CSOPESY_OSEmulator.cpp```
   -   ```CSOPESY_OSEmulator.cpp``` is the $${\color{red}entry}$$ $${\color{red}class}$$ $${\color{red}file}$$ where the main function is located
   -   Build and Run the project.


---

## **Files and Directory Structure**

### **Source Files**
| File                          | Description                                                                                                                                                                             |
|-------------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **CSOPESY_OSEmulator.cpp**     | Contains the `main()` function where the program begins execution. This file instantiates the `ConsoleManager` to initialize the system and manage user interactions.                    |
| **ConsoleManager.cpp**         | Manages the system configuration, including loading settings from the `config.txt` file, handling system initialization, and providing access to configuration parameters.               |
| **ConfigurationManager.cpp**   | Responsible for reading and parsing the configuration file (`config.txt`) and storing system parameters like scheduling algorithms, memory settings, and other configurations.           |
| **ResourceManager.cpp**        | Handles the allocation of system resources such as memory and CPU cores, manages process creation, scheduling, and monitors resource usage in collaboration with the scheduler.          |
| **AConsole.cpp**               | An abstract base class that defines a generic interface for console screens. Inherited by specific console screens like `MainMenu` and `ProcessScreen` for further customization.        |
| **MainMenu.cpp**               | Displays the main menu, allowing users to interact with the emulator. Provides access to process management, screen sessions, and system configurations through the command-line interface.|
| **ProcessScreen.cpp**          | Represents the console screen for individual processes, displaying process details like memory usage, execution state, and enabling user interaction with the processes.                |
| **Process.cpp**                | Defines the `Process` class, which tracks the process's execution state, memory usage, CPU core assignment, and provides methods to execute instructions and check process status.       |
| **CoreWorker.cpp**             | Represents a CPU core. Each `CoreWorker` is responsible for executing processes assigned to it, managing core utilization, and interacting with the scheduler to reassign or complete tasks.|
| **Scheduler.cpp**              | Manages the CPU scheduling algorithm (FCFS or Round-Robin) and assigns processes to available CPU cores based on the chosen scheduling strategy.                                       |
| **Styles.cpp**                 | Contains functions for styling and formatting the user interface in the command line, ensuring a structured and readable display of the system's status and output.                    |
| **PagingAllocator.cpp**        | Implements the paging memory allocation system. This class manages the translation between virtual and physical memory, dividing memory into fixed-size pages and handling paging.       |
| **MemoryManager.cpp**          | Manages memory allocation and deallocation. This class integrates with the `FlatMemoryAllocator` and `PagingAllocator` to manage both flat and paged memory schemes, providing efficient memory handling for processes. |
| **FlatMemoryAllocator.cpp**    | Implements flat memory allocation, providing a simple method of allocating contiguous memory blocks to processes without any segmentation or paging.                                   |
| **BackingStore.cpp**           | Simulates a backing store (typically used in virtual memory systems) that provides additional storage space when the system's main memory is full. It manages swapping data between memory and disk storage. |

