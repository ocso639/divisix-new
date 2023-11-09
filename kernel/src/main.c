// ESSENTIALS
#include <stdint.h>
#include <stddef.h>
#include <limine.h>
// LOW LEVEL
#include "include/memory.h"
#include "include/assembly.h"
#include "include/gdt.h"
// DISPLAY
#include "include/video.h"
#include "include/string.h"
#include "include/printf.h"
// ERROR HANDLING
#include "include/idt.h"
#include "include/exceptions.h"

static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

void _start(void) {
    
    if (framebuffer_request.response == NULL
        || framebuffer_request.response->framebuffer_count < 1) 
        hcf();

    struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];
    init_framebuffer(framebuffer->address, framebuffer->width, framebuffer->height, framebuffer->pitch);
    

    kputs("\e[1;97m"); // set color to high intensity white
    kinfos("DIVISIX Kernel (version 0, revision 1)\n");
    
    
    koks("GDT created\n");
    init_gdt();

    koks("IDT created\n");
    idt_init();
    //printf("Test format: %x\n", 5232);
    asm("mov $0, %rax\n div %rax");
    hcf();
}
