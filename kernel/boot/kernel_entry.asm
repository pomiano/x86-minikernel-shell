BITS 32

global _start
extern kernel_main

SECTION .text

_start:
    cli
    mov esp, stack_end
    call kernel_main

.hang:
    hlt
    jmp .hang


SECTION .bss
align 16

stack_begin:
    RESB 4096  ;rezerwuje miejsca na stos
stack_end:

