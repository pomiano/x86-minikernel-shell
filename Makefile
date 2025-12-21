# Kompilatory i narzędzia
ASM = nasm
CC = gcc
LD = ld

# Ścieżki do folderów
BOOTLOADER_DIR = bootloader/src
KERNEL_DIR = kernel
KERNEL_SRC = $(KERNEL_DIR)/src
KERNEL_BOOT = $(KERNEL_DIR)/boot
KERNEL_INC = $(KERNEL_DIR)/include
BIN_DIR = bin

# Pliki wynikowe
BOOT_BIN = $(BIN_DIR)/stage1.bin
STAGE2_BIN = $(BIN_DIR)/stage2.bin
KERNEL_BIN = $(BIN_DIR)/kernel.bin
OS_IMAGE = $(BIN_DIR)/os-image.img

# Flagi kompilacji
# -I$(KERNEL_INC) pozwala na używanie #include "kernel.h" bez podawania pełnej ścieżki
CFLAGS = -m32 -ffreestanding -fno-stack-protector -nostdlib -fno-builtin \
         -I$(KERNEL_INC) -fno-pic -fno-pie -fno-asynchronous-unwind-tables

LDFLAGS = -m elf_i386 -T linker.ld -no-pie

# Główny cel
all: $(OS_IMAGE)

# 1. Sklejanie wszystkiego w obraz obrazu dysku
$(OS_IMAGE): $(BOOT_BIN) $(STAGE2_BIN) $(KERNEL_BIN)
	@mkdir -p $(BIN_DIR)
	cat $(BOOT_BIN) $(STAGE2_BIN) $(KERNEL_BIN) > $(OS_IMAGE)
	truncate -s 1M $(OS_IMAGE)
	@echo "--- Gotowe! Obraz: $(OS_IMAGE) ---"

# 2. Kompilacja Stage 1 (boot.asm)
$(BOOT_BIN): $(BOOTLOADER_DIR)/stage1.asm
	@mkdir -p $(BIN_DIR)
	$(ASM) -f bin $< -o $@

# 3. Kompilacja Stage 2 (boot2.asm)
$(STAGE2_BIN): $(BOOTLOADER_DIR)/stage2.asm
	@mkdir -p $(BIN_DIR)
	$(ASM) -f bin $< -o $@

# 4. Kompilacja Kernela (Linkowanie)
$(KERNEL_BIN): kernel_entry.o kernel.o
	$(LD) $(LDFLAGS) $^ -o $@

# Kompilacja wejścia kernela (ASM)
kernel_entry.o: $(KERNEL_BOOT)/kernel_entry.asm
	$(ASM) -f elf32 $< -o $@

# Kompilacja kodu źródłowego kernela (C)
kernel.o: $(KERNEL_SRC)/kernel.c
	$(CC) $(CFLAGS) -c $< -o $@

# Uruchomienie w QEMU
run: all
	qemu-system-x86_64 -hda $(OS_IMAGE)

# Czyszczenie plików tymczasowych
clean:
	rm -f *.o
	rm -rf $(BIN_DIR)