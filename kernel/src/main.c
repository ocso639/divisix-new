// ESSENTIALS
#include <stdint.h>
#include <stddef.h>
#include <limine.h>
// LOW LEVEL
#include "include/memory.h"
#include "arch/x86_64/include/assembly.h"
#include "include/library/process.h"
#include "include/gdt.h"
// DISPLAY
#include "include/video.h"
#include "include/string.h"
#include "include/printf.h"
// ERROR HANDLING
#include "arch/x86_64/include/idt.h"
#include "arch/x86_64/include/exceptions.h"


static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

void init_process() {
    kputs("Init Test\n");
}

void init2_test() {
    kputs("Second Init Test\n");
}

void _start(void) {
    if (framebuffer_request.response == NULL
        || framebuffer_request.response->framebuffer_count < 1) 
        hcf;

    struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];
    init_framebuffer(framebuffer->address, framebuffer->width, framebuffer->height, framebuffer->pitch);
    
    init_gdt();

    idt_init();
    kputs("\e[1;97m"); // set color to high intensity white
    kputs("current binary shit\n");
    kinfos("Same printf function, long mode\n");
    printf("DIVISICS Supervisor (version 0, revision 1.2-4)\n");
    //kputs("DIVISICS Supervisor (version 0, revision 1.2-3)\n");
    //asm("hlt");
    

    create_process("System", *init_process, *init_process, ATTRIBUTE_SYSTEM | ATTRIBUTE_UNKILL);
    list_processes();
    //timeshare_idle();
    hcf;
}

