#ifndef OLIVEOS_STDLIB_H
#define OLIVEOS_STDLIB_H

#include <stddef.h>

void* malloc(size_t szie);
void free(void* ptr);
char* itoa(int i);

#endif