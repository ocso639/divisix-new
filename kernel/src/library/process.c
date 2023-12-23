#include <include/library/process.h>
#include <include/printf.h>
uint32_t __proc_list = 0;
uint32_t __free_processes[MAX_PROCESSES];
process process_list[MAX_PROCESSES];

process create_process(const char* name, uintptr_t address, uintptr_t entry, uint8_t attributes) {
    if (__proc_list < MAX_PROCESSES) {
        process proc = {
            .attributes = attributes,
            .entry = entry,
            .memory_address = address,
            .name = name
        };
        process_list[__proc_list] = proc;
        __proc_list++;
        return proc;
    }

    process failure = {
        .name = "failed to create process"
    };
    return failure;
}

void kill_process(const char* name) {
    for (int i = 0; i < MAX_PROCESSES; i++) {   
        process index = process_list[i];
        if (index.name == name) {
            __proc_list--;
            process_list[i] = process_list[__proc_list]; //replace with top process
        }
    }
}

void timeshare_idle() {
    int process_pointer = 0;
    while(1) {
        process current_process = process_list[process_pointer];
        uintptr_t entry = current_process.entry;
        void (*process_entry_point)(void) = entry;
        process_entry_point();

        if (process_pointer < __proc_list) {
            process_pointer++;
        } else {
            process_pointer = 0;
        }
    }
}
void list_processes() {
    kinfos("Total processes loaded in memory: "); kputs(itoa(__proc_list, 10, 1)); kputs("\n");
    kputs("List of all processes:\n");
    for (int i = 0; i < __proc_list; i++) {
        kputs("\t"); kputs(process_list[i].name); kputs(", location in memory: 0x"); kputs(itoa(process_list[i].memory_address, 16, 1)); kputs(", attributes: 0b"); kputs(itoa(process_list[i].attributes, 2, 1)); kputs("\n");
    }
    return;
}