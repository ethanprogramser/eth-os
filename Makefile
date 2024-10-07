all:
	## bootloader ###
	nasm -f elf32 src/boot.s -o build/boot.o
	nasm -f elf32 src/gdt.s -o build/gdts.o
	### Kernel #####
	gcc -m32 -fno-stack-protector -fno-builtin -c src/kernel.c -o build/kernel.o
	gcc -m32 -fno-stack-protector -fno-builtin -c src/vga.c -o build/vga.o
	gcc -m32 -fno-stack-protector -fno-builtin -c src/gdt.c -o build/gdt.o
	### else #####
	ld -m elf_i386 -T linker.ld -o kernel build/boot.o build/kernel.o build/vga.o build/gdt.o build/gdts.o
	mv kernel ethos/boot/kernel
	grub-mkrescue -o build/ethos.iso ethos/
	qemu-system-i386 build/ethos.iso
