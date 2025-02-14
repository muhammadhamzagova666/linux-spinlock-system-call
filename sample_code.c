#include <sys/syscall.h>  // Provides access to the syscall interface.
#include <linux/kernel.h> // Contains kernel-related functionalities for syscalls.
#include <stdio.h>        // Standard I/O functions.
#include <stdlib.h>       // General utilities like memory allocation.
#include <pthread.h>      // POSIX threads library for concurrent execution.

// Global variables to store the number of threads and the integer to be decremented.
// 'n' - the number of threads the user wants to launch.
// 'x' - the shared integer value that will be decremented by each thread.
int n, x;

/**
 * handler - Thread handler function that invokes the custom 'spinLock' system call.
 *
 * This function makes a system call (with identifier 335) to invoke the custom kernel
 * module function 'spinLock', passing the address of the integer 'x'. The primary
 * purpose is to illustrate safe decrement operations from multiple threads.
 *
 * Return: Always returns 0 as a placeholder termination value for the thread.
 */
void *handler()
{
    // Invoke the custom system call 'spinLock' with pointer to x.
    // Note: Ensure the system call number (335) matches the installed kernel module.
    syscall(335, &x);
    return 0;
}

/**
 * main - Entry point of the user-space application.
 *
 * This function orchestrates reading user input, creating threads to call the custom
 * system call, and waiting for all threads to complete. It displays the integer's initial
 * and final state to illustrate the atomic decrement operation in a concurrent context.
 *
 * Return: 0 on successful execution.
 */
int main()
{
    // Prompt for and read the initial value of x.
    printf("Enter the value of x: ");
    scanf("%d", &x);

    // Prompt for and read the number of threads to spawn.
    printf("Enter the number of threads: ");
    scanf("%d", &n);

    // Display the initial state of x to provide useful debugging information.
    printf("Initial value of x: %d\n", x);

    // Create an array of thread identifiers based on the user-specified count.
    pthread_t threads[n];

    // Create and launch threads that execute the 'handler' function.
    for (int i = 0; i < n; i++)
    {
        // Each thread invokes the custom system call to safely decrement x.
        pthread_create(&threads[i], NULL, handler, NULL);
    }

    // Wait for all threads to complete their execution.
    for (int i = 0; i < n; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // Print the final value of x after all threads have executed.
    printf("Final value of x: %d\n", x);
    return 0;
}