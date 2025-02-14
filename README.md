# Linux SpinLock System Call
*Demonstrating a Custom Kernel System Call with Dynamic SpinLock Synchronization*

## Overview
The **Linux SpinLock System Call** project implements a custom system call (`spinLock`) that safely decrements an integer by employing a dynamically initialized spinlock. This kernel module example illustrates how to control access to critical sections in a multi-threaded environment using dynamic spinlocks in the Linux kernel.

### Key Features
- **Custom System Call:** Uses `SYSCALL_DEFINE1` to expose the `spinLock` system call.
- **Dynamic SpinLock Initialization:** Ensures thread-safe decrement operations in concurrent or interrupt-driven contexts.
- **Logging and Debugging:** Provides kernel logs to trace the entry and exit of the critical section.
- **Educational Example:** Serves as a reference for integrating user-space applications with custom kernel functionalities.

## Project Type & Technology Stack
- **Project Type:** Linux kernel module
- **Language:** C
- **Technologies:** Linux Kernel, POSIX threads, system calls

## Purpose & Functionality
This project is intended for developers and researchers interested in kernel development and concurrency control. It demonstrates how to implement safe atomic operations using spinlocks, making it a valuable reference for building or extending kernel functionality with custom system calls.

## Installation & Setup

### Prerequisites
- Linux development environment
- Kernel headers corresponding to your kernel version
- gcc and make utilities

### Steps
1. **Clone the repository:**
   ```sh
   git clone https://github.com/muhammadhamzagova666/Linux-SpinLock-System-Call.git
   cd Linux-SpinLock-System-Call
   ```
2. **Build the kernel module:**
   - Write a Makefile to compile the kernel module (e.g., `spinlock_system_call.c`).
   - Run:
     ```sh
     make
     ```
3. **Insert the Kernel Module:**
   ```sh
   sudo insmod spinlock_system_call.ko
   ```
4. **Build and Run the User-space Application:**
   - Compile `sample_code.c`:
     ```sh
     gcc sample_code.c -lpthread -o sample_code
     ```
   - Execute:
     ```sh
     sudo ./sample_code
     ```
   - Follow the interactive prompts to witness the spinlock system call in action.

## Usage Example
After setting up, running the user-space application (`sample_code`) asks for an integer value and a number of threads. Each thread invokes the custom system call that safely decrements the integer:
```
Enter the value of x: 10
Enter the number of threads: 3
Initial value of x: 10
Final value of x: 7
```

## Contributing
Contributions are welcome! Please follow these guidelines:
- Fork the repository.
- Create a feature branch (e.g., `feature/new-feature`).
- Commit your changes with clear messages.
- Open a pull request with a detailed description of your changes.

For any issues or suggestions, please open an issue on the GitHub repository.

## Author
Muhammad Hamza Gova  
Visit my GitHub profile: [muhammadhamzagova666](https://github.com/muhammadhamzagova666)
