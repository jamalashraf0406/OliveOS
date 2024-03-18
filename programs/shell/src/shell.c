#include "shell.h"
#include "stdio.h"
#include "stdlib.h"
#include "oliveos.h"


int main(int argc, char** argv) {

    print("OliveOs v1.0.0\n");
    while(1) {
        print("# ");
        char buf[1014];
        oliveos_terminal_readline(buf, sizeof(buf), true);
        print("\n");
        oliveos_system_run(buf);
        print("\n");
    }
}