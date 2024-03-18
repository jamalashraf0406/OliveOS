#ifndef OLIVEOS_H
#define OLIVEOS_H

#include <stddef.h>
#include <stdbool.h>

struct command_argument {
    char argument[512];
    struct command_argument* next;
};

struct process_arguments {
    int argc;
    char** argv;
};

void print(const char* filename);
int oliveos_getkey();

void* oliveos_malloc(size_t size);
void oliveos_free(void* ptr);

int oliveos_putchar(int c);

int oliveos_getkeyblock();
void oliveos_terminal_readline(char* out, int max, bool output_while_typing);
void oliveos_process_load_start(const char* filename);

struct command_argument* oliveos_parse_command(const char* command, int max);
void oliveos_process_get_arguments(struct process_arguments* arguments);

int oliveos_system(struct command_argument* arguments);
int oliveos_system_run(const char* command);
void oliveos_exit();


#endif