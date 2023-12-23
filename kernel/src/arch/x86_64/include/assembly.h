#pragma once
#define hcf asm("cli\nhlt");
#define load_idt(ptr) asm volatile("lidt %0" :: "m"(ptr));