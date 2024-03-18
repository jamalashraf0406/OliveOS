[BITS 32]

section .asm

global _start

; This lebel is for add two number
_start:
    push 20
    push 30
    mov eax, 0 ; Command 0 SUM
    int 0x80   ; Called int 0x80
    add esp, 8 ; pop eax and pop eax instead of add esp, 8

    jmp $