#include "kernel.h"
#include <stdint.h>
#include <stddef.h>
#include "idt/idt.h"
#include "io/io.h"
#include "string/string.h"
#include "memory/memory.h"
#include "memory/heap/kheap.h"
#include "memory/paging/paging.h"
#include "disk/disk.h"
#include "fs/pparser.h"
#include "fs/file.h"
#include "isr80h/isr80h.h"
#include "disk/streamer.h"
#include "gdt/gdt.h"
#include "config.h"
#include "task/tss.h"
#include "task/task.h"
#include "task/process.h"
#include "status.h"
#include "keyboard/keyboard.h"


uint16_t* video_men = 0;
uint16_t terminal_row = 0;
uint16_t terminal_col = 0;

uint16_t terminal_make_char(char c, char colour) {
    return (colour << 8) | c;
}

void terminal_putchar(int x, int y, char c, char colour) {
    video_men[(y * VGA_WIDTH) + x] = terminal_make_char(c, colour);
}

void terminal_backspace() {

    if (terminal_row == 0 && terminal_col == 0) {
        return;
    }

    if (terminal_col == 0) {
        terminal_row -= 1;
        terminal_col = VGA_WIDTH;
    }
    terminal_col -=1;
    terminal_writechar(' ', 15);
    terminal_col -=1;
}

void terminal_writechar(char c, char colour) {

    if (c == '\n') {
        terminal_col = 0;
        terminal_row += 1;
        return;
    }

    if (c == 0x08) {
        terminal_backspace();
        return;
    }

    terminal_putchar(terminal_col, terminal_row, c, colour);
    terminal_col += 1;
    if (terminal_col >= VGA_WIDTH) {
        terminal_col = 0;
        terminal_row += 1;
    }
}

void terminal_initialize() {
    video_men = (uint16_t*)(0xB8000);
    for(int y = 0; y < VGA_HEIGHT; y++) {
        
        for(int x = 0; x < VGA_WIDTH; x++) {
            terminal_putchar(x, y, ' ', 0);
        }
    }
}

void print(const char* str) {
    size_t len = strlen(str);
    for (int i = 0; i < len; i++) {
        terminal_writechar(str[i], 15);
    }
}

void panic(const char* message) {
    print(message);
    while(1){}
}

static struct paging_4gb_chunk* kernel_chunk = 0; 
void kernel_page() {
    kernel_registers();
    paging_swtich(kernel_chunk);
}

struct tss tss;
struct gdt gdt_real[OLIVEOS_TOTAL_GDT_SEGMENTS];
struct gdt_structured gdt_structured[OLIVEOS_TOTAL_GDT_SEGMENTS] = {
    
    {.base = 0x00, .limit = 0x00, .type = 0x00 },               // Null Segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0x9a },         // Kernel Code segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0x92 },         // Kernel data segment

    {.base = 0x00, .limit = 0xffffffff, .type = 0xf8},          // User Code Segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0xf2},          // User data segment
    {.base = (uint32_t)&tss, .limit = sizeof(tss), .type = 0xE9}// TSS segment
};

void kernel_main() {
    
    terminal_initialize();

    // Load Global Descriptor Table(GDT)
    memset(gdt_real, 0x00, sizeof(gdt_real));
    gdt_structured_to_gdt(gdt_real, gdt_structured, OLIVEOS_TOTAL_GDT_SEGMENTS);
    gdt_load(gdt_real, sizeof(gdt_real));

    // Initialize the Kernel Heap
    kheap_init();

    // Initialize filesystem
    fs_init();

    // Search and Initialize the disks
    disk_search_init();

    // Initialize the interrupt descriptor table
    idt_init();

    // Setup the TSS
    memset(&tss, 0x00, sizeof(tss));
    tss.esp0 = 0x600000;
    tss.ss0 = KERNEL_DATA_SELECTOR;
    
    // Load TSS
    tss_load(0x28);

    // Setup Paging
    kernel_chunk = paging_new_4gb(PAGING_IS_WRITEABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL);

    // switch to kernel paging chunk
    paging_swtich(kernel_chunk);

    // Enable paging
    enable_paging();

    // Enable the system interrupts 
    // --> Comment below enable_interrupts() because we have to enable it after loading the user program
    // enable_interrupts();

    
    // Register the command
    isr80h_register_commands();

    // Initialize all the system keyboards
    keyboard_init();

    // Process 1
    struct process* process = 0;
    int res = process_load_switch("0:/shell.elf", &process);
    if (res != OLIVEOS_ALL_OK) {
        panic("\nFailed to load shell.elf");
    } 

    struct command_argument argument;
    strcpy(argument.argument, "Testing");
    argument.next = 0x00;

    process_inject_arguments(process, &argument);


    task_run_first_ever_task();
    while(1){}
   
}

