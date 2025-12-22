BITS 32

global isr0

global irq0
global irq1

extern isr_handler

isr0:
    cli
    push byte 0     ; kod błędu
    push byte 0     ; numer przerwania
    pushad          

    call isr_handler

    popad
    add esp, 8
    sti
    iret

irq0:
    cli 
    push byte 0
    push dword 32
    pushad
    
    call isr_handler
   
    popad
    add esp,8
    sti
    iret

irq1:
    cli

    push byte 0
    push dword 33
    pushad

    call isr_handler

    popad
    add esp, 8  
    sti
    iret