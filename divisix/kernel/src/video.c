#include "include/video.h"
#include "include/string.h"

struct flanterm_context *framebuf;

void init_framebuffer(uint32_t *framebuffer, size_t width, size_t height, size_t pitch) {
    framebuf = flanterm_fb_simple_init(framebuffer, width, height, pitch);
    return;
}

void kputs(const char msg[]) {
    flanterm_write(framebuf, msg, strlen(msg));
    return;
}

void koks(const char msg[]) {
    kputs("[\e[0;92mOKAY\e[1;97m] "); kputs(msg);
    return;
}

void kfails(const char msg[]) {
    kputs("[\e[0;91mFAIL\e[1;97m] "); kputs(msg);
    return;
}

void kinfos(const char msg[]) {
    kputs("[\e[0;93mINFO\e[1;97m] "); kputs(msg);
    return;
}

void kunimps(const char msg[]) {
    kputs("[\e[0;37mUNIM\e[1;97m] "); kputs(msg);
}