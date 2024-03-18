[BITS 32]

section .asm

global _start

_start:
    push message
    mov eax, 1      ; Command 1 is to print message from message label
    int 0x80
    add esp, 4
    jmp $

section .data
message: db 'Hello World from the Process!', 0