[BITS 32]

section .asm

global _start

extern c_start
extern oliveos_exit

_start:
    call c_start
    call oliveos_exit
    ret