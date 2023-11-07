extern c_divide_zero
extern c_debug
extern c_double_fault

%macro isr 3
    align 16, db 0
    global %1
%1:
    cld
%if %2 == 0
    push 0
%endif
    ;push all regs
    push rax
    push rdi
    push rsi
    push rdx 
    push rcx
    push r8
    push r9
    push r10
    push r11

    mov rdi, rsp
    call %3

    ;pop all regs
    ;add rsp, 8

    pop r11
    pop r10 
    pop r9
    pop r8 
    pop rcx
    pop rdx 
    pop rsi 
    pop rdi 
    pop rax

    add rsp, 8

    leave
    iretq

%endmacro

isr divide_zero, 0, c_divide_zero
isr debug, 0, c_debug
isr double_fault, 1, c_double_fault


