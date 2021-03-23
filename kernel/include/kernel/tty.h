/// @file tty.h
#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>

/**
 * Initializes the terminal and clears the screen.
 */
void terminal_init(void);

/**
 * Prints a single ASCII character to the screen.
 * @param[in] ch The character to print.
 */
void terminal_putchar(char ch);

/**
 * Prints a sequence of ASCII characters to the screen.
 * @param[in] data Pointer to the start of the sequence of bytes.
 * @param[in] size Number of bytes to print.
 */
void terminal_write(const char* data, size_t size);

/**
 * Prints a null-terminated string to the screen.
 * @param[in] data Pointer to the start of the string.
 */
void terminal_writestring(const char* data);

#endif
