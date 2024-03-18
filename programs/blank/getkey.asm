[BITS 32]

section .asm

global _start

_start:

_loop:
    call get_key
    ; push message --> this is commented and instead of 'push message' we did 'push eax'
    ;              --> This commented line is for printing the message db value.
    push eax
    mov eax, 3  ; This 3 is for putchar
    int 0x80
    add esp, 4
    jmp _loop

get_key:
    mov eax, 2      ; Command 2  to get the key from key pressed
    int 0x80
    cmp eax, 0x00
    je get_key
    ret

section .data
message: db 'I can talk with kernel!', 0