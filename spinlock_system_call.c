/*
 * spinlock_system_call.c - Kernel module implementing a custom system call using a dynamic spinlock.
 *
 * This module provides a custom system call "spinLock" that safely decrements an integer.
 * The critical section is protected by a dynamically initialized spinlock to ensure correct
 * operation in concurrent or interrupt contexts.
 *
 * Key Points:
 *  - Provides a custom system call using SYSCALL_DEFINE1.
 *  - Uses a dynamic spinlock to manage synchronization of the critical section.
 *  - Logs entering and exiting the critical section for debugging purposes.
 *  - Designed as an educational example of safe atomic operations in kernel space.
 */

#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/spinlock.h>
#include <linux/syscalls.h>

/**
 * spinLock - Custom system call to safely decrement an integer.
 * @x: Pointer to the integer value to be decremented.
 *
 * This function safely decrements the integer pointed to by @x by using a
 * spinlock. The spinlock is dynamically initialized and used here to ensure
 * that the decrement operation in the critical region is performed atomically,
 * even in an interrupt-driven context. Informative kernel messages are logged
 * to trace the execution flow during lock acquisition and release.
 *
 * Return: Always returns 0 to indicate successful operation.
 */
SYSCALL_DEFINE1(spinLock, int *, x)
{
    // Declare a static spinlock to maintain its state across system call invocations.
    static spinlock_t dynamic;
    
    // Variable to store flags that will hold interrupt state information.
    unsigned long flags;
    
    // Dynamically initialize the spinlock.
    spin_lock_init(&dynamic);
    
    // Acquire the spinlock and disable local interrupts, preserving the interrupt state.
    spin_lock_irqsave(&dynamic, flags);
    pr_info("Locked dynamic spinlock: entering critical section\n");
    
    // Critical section: perform safe decrement of the provided integer.
    *x = *x - 1;
    
    // Release the spinlock and restore the previous interrupt state.
    spin_unlock_irqrestore(&dynamic, flags);
    pr_info("Unlocked dynamic spinlock: exiting critical section\n");
    
    // Log the final value after decrement to assist in debugging.
    printk("New value after decrement: %d\n", *x);
    
    return 0;
}

MODULE_DESCRIPTION("Kernel module implementing custom 'spinLock' system call with dynamic spinlock");
MODULE_AUTHOR("Gova");