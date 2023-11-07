#include <stdint.h>
#include <stddef.h>
#include <limine.h>
#include "include/memory.h"
#include "include/assembly.h"
#include "include/string.h"
#include "include/video.h"
#include "include/idt.h"
#include "include/gdt.h"

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
    //idt_init();
    //koks("Interrupts enabled\n");
    koks("GDT created\n");
    init_gdt();

    koks("IDT created\n");
    idt_init();
    kunimps("FAT driver initiated\n");
    kunimps("SYSCALLS created\n");

    //asm("mov $0, %rax\n div %rax");
    asm("int $0x0");
    kputs("Exception testing\n");
    kinfos("Continued execution!\n");

    hcf();
}
