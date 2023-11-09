default rel

extern koops
extern kpanic

extern c_double_fault
extern c_generalprotection_fault
extern c_page_fault
extern c_invalid_opcode

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
    align 16, db 0
    global %1
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

;isr divide_zero, 0, c_divide_zero
global divide_zero


divide_zero:
    cld
    pushaq

    mov rdi, [division_string]
    call koops

    popaq
    add rsi, 1
    leave 
    iretq

isr double_fault, 1, c_double_fault
isr general_protection_fault, 1, c_generalprotection_fault
isr page_fault, 1, c_page_fault
isr invalid_opcode, 0, c_invalid_opcode

section .data
division_string:
    db 'Division by zero', 0x0A, 0x0