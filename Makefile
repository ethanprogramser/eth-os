gcc = ~/opt/cross/bin/i686-elf-gcc
ld = ~/opt/cross/bin/i686-elf-ld
flags = -c -ffreestanding

all: kernel boot assemble

kernel:
	### Kernel #####
	$(gcc) $(flags) src/kernel.c -o build/kernel.o
	$(gcc) $(flags) src/stdlib/stdio.c -o build/stdio.o
	$(gcc) $(flags) src/vga.c -o build/vga.o
	$(gcc) $(flags) src/gdt.c -o build/gdt.o
	$(gcc) $(flags) src/timer.c -o build/timer.o
	$(gcc) $(flags) src/util.c -o build/util.o
	$(gcc) $(flags) src/idt.c -o build/idts.o
	$(gcc) $(flags) src/keyboard.c -o build/keyboard.o
	$(gcc) $(flags) src/malloc.c -o build/malloc.o
	$(gcc) $(flags) src/mem.c -o build/mem.o

boot:
	## bootloader ###
	nasm -f elf32 src/boot.s -o build/boot.o
	nasm -f elf32 src/gdt.s -o build/gdts.o
	nasm -f elf32 src/idt.s -o build/idt.o

	### else #####

assemble:
	$(ld) -T linker.ld -o kernel build/boot.o build/kernel.o build/vga.o build/gdts.o build/gdt.o build/idts.o build/idt.o  build/util.o build/timer.o build/stdio.o build/keyboard.o build/malloc.o build/mem.o
	mv kernel src/ethos/boot/kernel
	grub-mkrescue -o build/ethos.iso src/ethos/
	qemu-system-i386 build/ethos.iso
