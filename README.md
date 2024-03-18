Command:
--------
/> nasm -f bin ./boot.asm -o ./boot.bin
/> ndisasm ./boot.bin
/> qemu-system-x86_64 -hda ./boot.bin
/> hexeditor ./boot.bin
/> gdb
/> target remote | qemu-system-x86_64 -hda ./boot.bin -S -gdb stdio
/> layout asm
/> info register
/> $HOME/opt/cross/bin/$TARGET-gcc --version
/> add-symbol-file ./build/kernelfull.o 0x100000
/> break _start
/> target remote | qemu-system-x86_64 -hda ./bin/os.bin -S -gdb stdio
/> ndisasm -b32 ./blank.bin

Run OS Command:
---------------
/> cd ./goto/OliveOS
/> make clean
/> ./build.sh
/> qemu-system-x86_64 -hda ./bin/boot.bin
/> qemu-system-i386 -hda ./bin/os.bin

install packages:
--------------
sudo apt install ?
bless -- hexeditor
gdb   -- kerel debugger
qemu  -- emulator
nasm  -- c compiler
pax-utils  -- it is dumpelf file.(dumpelf ./getkey.elf)
readelf -- to print all info of elf file(readelf -a ./programs/blank/getkey.elf)


Burn bootloader to a USB:
---
sudo dd if=./boot.bin of=/dev/sdb

Help URL:
---------
build cross compiler: just have a look in osdev wiki guide
http://www.ctyme.com/rbrown.html
https:/wiki.osdev.org/FAT
https://faydoc.tripod.com/cpu/insw.htm
https://wiki.osdev.org/Memory_Map_(x86)
https://wiki.osdev.org/GCC_Cross-Compiler



Topics:
-------
emu8086 processor simulator
A20 Line
ATA
Interrupt Descriptor[table] in protected mode
Interrupt Gate Types
Programmable Interrupt
Cross Compiler
FAT16 or file allocation table
GDT - Global Descriptor table
PS/2 Keyboard
ELF specification PDF to implement ELF in kernel
(https://refspecs.linuxfoundation.org/elf/elf.pdf)




Assembly:
---------
https://www.falstad.com/circuit/circuitjs.html
https://dragonzap.com/downloads


Debugg Kernelfull.o:
--------------------
/> cd bin
/> gdb
/> add-symbol-file ../build/kernelfull.o 0x100000 
/> break kernel.c:96
/> target remote | qemu-system-i386 -hda ./os.bin -S -gdb stdio
/> c it for continue
/> next
/> print stream
/> next
/> print variable_of_c_code


And use hex editor:
------
/> hexeditor ./bin/os.bin 


target remote | qemu-system-x86_64 -hda ./os.bin -S -gdb stdio
