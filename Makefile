all:
	## bootloader ###
	nasm -f elf32 src/boot.s -o build/boot.o
	nasm -f elf32 src/gdt.s -o build/gdts.o
	nasm -f elf32 src/idt.s -o build/idt.o
	### Kernel #####
	gcc -m32 -fno-stack-protector -fno-builtin -c src/kernel.c -o build/kernel.o
	gcc -m32 -fno-stack-protector -fno-builtin -c src/stdlib/stdio.c -o build/stdio.o
	gcc -m32 -fno-stack-protector -fno-builtin -c src/vga.c -o build/vga.o
	gcc -m32 -fno-stack-protector -fno-builtin -c src/gdt.c -o build/gdt.o
	gcc -m32 -fno-stack-protector -fno-builtin -c src/timer.c -o build/timer.o
	gcc -m32 -fno-stack-protector -fno-builtin -c src/util.c -o build/util.o
	gcc -m32 -fno-stack-protector -fno-builtin -c src/idt.c -o build/idts.o
	gcc -m32 -fno-stack-protector -fno-builtin -c src/keyboard.c -o build/keyboard.o
	### else #####
	ld -m elf_i386 -T linker.ld -o kernel build/boot.o build/kernel.o build/vga.o build/gdts.o build/gdt.o build/idts.o build/idt.o  build/util.o build/timer.o build/stdio.o build/keyboard.o
	mv kernel ethos/boot/kernel
	grub-mkrescue -o build/ethos.iso ethos/
	qemu-system-i386 build/ethos.iso
