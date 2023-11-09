#include "include/string.h"

size_t strlen(const char *str) {
    const char *s;

    for (s = str; *s; s++);
    return (s - str);
}

char* itoa(uint64_t number, int base, int min_digits)
{
	int digits = 0;
	static char chars[] = "0123456789abcdef";
	static char buff[128];
	char *ptr = &buff[127];

	*ptr = '\0';

	do {
		digits++;
		*--ptr = chars[number % base];
		number /= base;
	} while (number);

	if (digits < min_digits)
		ptr -= (min_digits - digits);

	return ptr;
}