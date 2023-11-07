#include "include/exceptions.h"
#include "include/video.h"
#include "include/assembly.h"

void stack_trace() {
    kputs("Stack trace not implemented yet.\n");
}

void kpanic(const char* message) {
    kfails("Kernel Panic!\n");
#ifndef printf_enabled
    kputs("Fault: ");
    kputs(message);
#endif
    stack_trace();
    kputs("System halted.\n");
    hcf();
}

void koops(const char* message) {
    kfails("Oops!\n");
    #ifndef printf_enabled
    kputs(message);
    stack_trace();
    #endif
    kputs("Normal execution may continue.\n");
}