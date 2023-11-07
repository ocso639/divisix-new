#pragma once
#include <stdint.h>
#include <stddef.h>
#include "flanterm/flanterm.h"
#include "flanterm/backends/fb.h"
#include "memory.h"

void init_framebuffer(uint32_t *framebuffer, size_t width, size_t height, size_t pitch);

void kputs(const char msg[]);

void koks(const char msg[]);

void kfails(const char msg[]);

void kinfos(const char msg[]);

void kunimps(const char msg[]);