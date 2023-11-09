#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <limine.h>
#include "flanterm/flanterm.h"
#include "flanterm/backends/fb.h"
#include "memory.h"

void kputc(char c);

void kputs(const char msg[]);

void init_framebuffer(uint32_t *framebuffer, size_t width, size_t height, size_t pitch);