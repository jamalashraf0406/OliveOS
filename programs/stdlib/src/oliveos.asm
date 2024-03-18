[BITS 32]

global print:function
global oliveos_getkey:function
global oliveos_malloc:function
global oliveos_free: function
global oliveos_putchar: function
global oliveos_process_load_start: function
global oliveos_process_get_arguments: function
global oliveos_system: function
global oliveos_exit: function

; void print(const char* filename)
print:
    push ebp
    mov ebp, esp
    push dword[ebp+8]
    mov eax, 1              ; This is the print command 1
    int 0x80
    add esp, 4
    pop ebp
    ret

; int oliveos_getkey()
oliveos_getkey:
    push ebp
    mov ebp, esp
    mov eax, 2             ; This is the getkey command
    int 0x80
    pop ebp
    ret

; int oliveos_putchar(int c)
oliveos_putchar:
    push ebp
    mov ebp, esp
    mov eax, 3              ; Command 3 for print the character
    push dword[ebp+8]       ; Variable C
    int 0x80
    add esp, 4
    pop ebp
    ret

; void* oliveos_malloc(size_t size)
oliveos_malloc:
    push ebp
    mov ebp, esp
    mov eax, 4              ; Command malloc(Allocates memory for the process)
    push dword[ebp+8]       ; Variable "Size"
    int 0x80
    add esp, 4
    pop ebp
    ret

; void oliveos_free(void* ptr)
oliveos_free:
    push ebp
    mov ebp, esp
    mov eax, 5              ; Command 5 free(Frees the allocated memory for this process)
    push dword[ebp+8]       ; Varaible "ptr"
    int 0x80
    add esp, 4
    pop ebp
    ret

; void oliveos_process_load_start(const char* filename)
oliveos_process_load_start:
    push ebp
    mov ebp, esp
    mov eax, 6              ; Command 6 process load start ( starts a process )
    push dword[ebp+8]       ; Variable "filename"
    int 0x80
    add esp, 4
    pop ebp
    ret

; int oliveos_system(struct command_argument* arguments)
oliveos_system:
    push ebp
    mov ebp, esp
    mov eax, 7              ; Command 7 process system ( Run system command on the argument)
    push dword[ebp+8]       ; Variable "arguments"
    int 0x80
    add esp, 4
    pop ebp
    ret


; void oliveos_process_get_arguments(struct process_arguments* arguments)
oliveos_process_get_arguments:
    push ebp
    mov ebp, esp
    mov eax, 8              ; Command 8 Get the process arguments
    push dword[ebp+8]       ; Variable "arguments"
    int 0x80
    add esp, 4
    pop ebp
    ret

; void pachos_exit() 
oliveos_exit:
    push ebp
    mov ebp, esp
    mov eax, 9              ; Command 9 process exit
    int 0x80
    pop ebp
    ret


