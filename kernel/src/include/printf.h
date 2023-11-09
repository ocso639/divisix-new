#include "include/video.h"
#include "include/string.h"
#include <string.h>

void koks(const char msg[]);

void kfails(const char msg[]);

void kinfos(const char msg[]);

void kunimps(const char msg[]);

static bool print(char *dest, const char *src, size_t length);

int vsprintf(char *str, const char* restrict fmt, va_list params);

int vprintf(const char* restrict fmt, va_list params);

int printf(const char* restrict fmt, ...);