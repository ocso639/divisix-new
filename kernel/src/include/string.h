#pragma once
#include <stdint.h>
#include <stddef.h>

size_t strlen(const char *str);
char* itoa(uint64_t number, int base, int min_digits);