all:
	nasm -f bin ./src/stage1.asm -o ./bin/stage1.bin
	nasm -f bin ./src/stage2.asm -o ./bin/stage2.bin
	cat ./bin/boot.bin ./bin/stage2.bin > ./bin/os-image.img

clean:
	rm -f /bin/boot.bin

qemu:
	qemu-system-x86_64 -hda ./bin/os-image.img 

qemu-debug:
	qemu-system-x86_64 -hda ./bin/os-image.img -S -s

qemu-log:
	qemu-system-x86_64 -hda ./bin/os-image.img -d int,cpu_reset -D qemu.log
