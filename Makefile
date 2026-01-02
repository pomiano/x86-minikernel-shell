#AI pomogło mi w więkoszsci linijek tego pliku 

ASM = nasm
CC = gcc
LD = ld

BOOTLOADER_DIR = bootloader/src
KERNEL_DIR = kernel
KERNEL_SRC = $(KERNEL_DIR)/src
KERNEL_BOOT = $(KERNEL_DIR)/boot
KERNEL_INC = $(KERNEL_DIR)/include
BIN_DIR = bin

SRC_DIRS = $(KERNEL_SRC) \
           $(KERNEL_SRC)/arch \
           $(KERNEL_SRC)/drivers \
           $(KERNEL_SRC)/lib

C_SOURCES = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))
ASM_SOURCES = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.asm))

OBJ = $(C_SOURCES:.c=.o) $(ASM_SOURCES:.asm=.o)

BOOT_BIN = $(BIN_DIR)/stage1.bin
STAGE2_BIN = $(BIN_DIR)/stage2.bin
KERNEL_BIN = $(BIN_DIR)/kernel.bin
OS_IMAGE = $(BIN_DIR)/os-image.img

# flagi
CFLAGS = -g -m32 -ffreestanding -fno-stack-protector -nostdlib -fno-builtin \
         -I$(KERNEL_INC) -fno-pic -fno-pie -fno-asynchronous-unwind-tables

# flagi Linkera
LDFLAGS = -m elf_i386 -T linker.ld -no-pie

all: $(OS_IMAGE)

# Budowanie obrazu dysku
$(OS_IMAGE): $(BOOT_BIN) $(STAGE2_BIN) $(KERNEL_BIN)
	@mkdir -p $(BIN_DIR)
	cat $(BOOT_BIN) $(STAGE2_BIN) $(KERNEL_BIN) > $(OS_IMAGE)
	truncate -s 1M $(OS_IMAGE)

# Bootloader Stage 1
$(BOOT_BIN): $(BOOTLOADER_DIR)/stage1.asm
	@mkdir -p $(BIN_DIR)
	$(ASM) -f bin $< -o $@ 

# Bootloader Stage 2
$(STAGE2_BIN): $(BOOTLOADER_DIR)/stage2.asm
	@mkdir -p $(BIN_DIR)
	$(ASM) -f bin $< -o $@

# Linkowanie Kernela
$(KERNEL_BIN): kernel_entry.o $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $^

# Kompilacja wejścia kernela
kernel_entry.o: $(KERNEL_BOOT)/kernel_entry.asm
	$(ASM) -f elf32 $< -o $@


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.asm
	$(ASM) -f elf32 $< -o $@


run: all
	qemu-system-x86_64 -hda $(OS_IMAGE)

clean:
	rm -f $(OBJ) kernel_entry.o
	rm -rf $(BIN_DIR)