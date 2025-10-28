all:
	nasm -f bin ./src/boot.asm -o ./bin/boot.bin
	nasm -f bin ./src/stage2.asm -o ./bin/stage2.bin
	cat ./bin/boot.bin ./bin/stage2.bin > ./bin/os-image.img

clean:
	rm -f /bin/boot.bin

qemu:
	qemu-system-x86_64 -hda ./bin/os-image.img 

qemu-debug:
	qemu-system-x86_64 -hda ./bin/os-image.img -S -s