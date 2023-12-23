#include "include/video.h"
#include "include/string.h"

struct limine_framebuffer *framebuf;

void init_framebuffer(uint32_t *framebuffer, size_t width, size_t height, size_t pitch) {
    framebuf = flanterm_fb_simple_init(framebuffer, width, height, pitch);
    return;
}

void kputc(char c) {
    flanterm_write(framebuf, (const char*)c, strlen((const char*)c));
    return;
}

void kputs(const char msg[]) {
    flanterm_write(framebuf, msg, strlen(msg));
    return;
}