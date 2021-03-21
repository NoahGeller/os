#ifndef _STRING_H
#define _STRING_H

#include <stddef.h>

int memcmp(const void* ptr1, const void* ptr2, size_t num);
void* memcpy(void* dest, const void* src, size_t num);
void* memmove(void* dest, const void* src, size_t num);
void* memset(void* ptr, int value, size_t num);
size_t strlen(const char* str);

#endif
