#pragma once
#include <stdint.h>
#include <stddef.h>
//#define printf_enabled

void stack_trace();
void kpanic(const char* message);
void koops(const char* message);