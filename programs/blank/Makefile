FILES = ./build/program.o
INCLUDES = -I../stdlib/src
FLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc

all: ${FILES}
	# nasm -f elf ./getkey.asm -o ./build/getkey.o
	# i686-elf-gcc -g -T ./linker.ld -o ./getkey.bin -ffreestanding -O0 -nostdlib -fpic -g ./build/getkey.o
	
	i686-elf-gcc -g -T ./linker.ld -o ./program.elf -ffreestanding -O0 -nostdlib -fpic -g ${FILES} ../stdlib/stdlib.elf

./build/program.o: 	
	i686-elf-gcc $(INCLUDES) -I./ $(FLAGS) -std=gnu99 -c ./program.c -o ./build/program.o

clean:
	rm -rf ${FILES}
	rm ./program.elf