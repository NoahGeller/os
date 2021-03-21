#ifndef _STDIO_H
#define _STDIO_H

#include <stddef.h>
#include <stdint.h>

#define EOF (-1)

/**
 * Writes a character to the standard output.
 * @param[in] ch The character to write.
 * @param[out] The written or character, or EOF on error.
 */
int putchar(int ch);

/**
 * Writes a string to the standard output and appends a newline.
 * @param[in] str Pointer to the start of the string to write.
 * @param[out] Number of characters written on success, EOF on error.
 */
int puts(const char* restrict str);

/**
 * Writes a formatted string to the standard output.
 * @param[in] format String with optional format specifiers.
 * @param[out] Number of characters written on success, EOF on error.
 */
int printf(const char* restrict format, ...);

#endif
