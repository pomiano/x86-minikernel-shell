all:
	nasm -f elf32 kernel_entry.asm -o kernel_entry.o
	gcc -m32 -ffreestanding -fno-stack-protector -c kernel.c -o kernel.o
	ld -m elf_i386 -T linker.ld kernel_entry.o kernel.o -o kernel.bin --oformat binary