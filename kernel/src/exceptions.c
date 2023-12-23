#include "include/exceptions.h"
#include "include/video.h"
#include "include/string.h"
#include "arch/x86_64/include/assembly.h"
void stack_trace() {
    uintptr_t *stack;
    asm volatile("mov %%rbp, %0" : "=g"(stack));
    for (int i = 0; i > 16; i++) {
       // kputs(itoa(stack[i], 16)); kputs("\n");
    }
}

void kpanic(const char* message) {
    kfails("Kernel Panic!\n");
#ifndef printf_enabled
    kputs("Fault: ");
    kputs(message);
#endif
    //stack_trace();
    kputs("System halted.\n");
    hcf;
}

void koops(const char* message) {
    kfails("Oops!\n");
    #ifndef printf_enabled
    kputs(message);
    //stack_trace();
    #endif
    kputs("Normal execution may continue.\n");
}