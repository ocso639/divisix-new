extern koops
extern kpanic

extern c_divide_zero
extern c_debug
extern c_double_fault
extern c_generalprotection_fault
extern c_page_fault
extern c_invalid_opcode
extern c_system_call

%macro pushaq 0
    ;push rsp 
    mov r10, rsp
    push rax 
    push rcx
    push rdx 
    push rbx
    push r10
    push rbp
    push rsi 
    push rdi
%endmacro

%macro popaq 0
    pop rdi 
    pop rsi 
    pop rbp
    add rsp, 8
    pop rbx 
    pop rdx 
    pop rcx
    pop rax
%endmacro

%macro isr 3
    global %1
    align 8
%1:
    cld
%if %2 == 0
    push 0
%endif
    ;push all regs
    pushaq

    mov rdi, rsp
    call %3

    ;pop all regs
    popaq

    leave
    iretq

%endmacro

isr divide_zero, 0, c_divide_zero
isr double_fault, 1, c_double_fault
isr debug, 1, c_debug
isr general_protection_fault, 1, c_generalprotection_fault
isr page_fault, 1, c_page_fault
isr invalid_opcode, 0, c_invalid_opcode
;isr system_utilities, 0, c_system_call
