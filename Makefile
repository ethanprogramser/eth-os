ISO_NAME=ethos.iso

include config.mk

.PHONY: all bootloader kernel link grub iso run clean

all: dirs bootloader kernel link grub iso

# Create build directory
dirs:
	mkdir -p $(BUILD_DIR)/
	mkdir -p $(OBJ_DIR)/
	mkdir -p $(OUT_DIR)/

# Bootloader
bootloader:
	@echo "Compiling bootloader..."
	$(MAKE) -C $(SRC_DIR)/bootloader

# Kernel
kernel:
	@echo "Compiling kernel..."
	$(MAKE) -C $(SRC_DIR)/kernel

# Link everything
link: bootloader kernel
	@echo "Linking..."
	$(LD) $(LDFLAGS) -T $(abspath linker.ld) -o $(BUILD_DIR)/kernel $(wildcard $(OBJ_DIR)/*.o)

# Place GRUB config
grub: link
	@echo "Placing GRUB config..."
	$(MAKE) -C $(SRC_DIR)/grub

# Make an `.iso` file
iso: link grub
	@echo "Making an iso..."
	mkdir -p $(OUT_DIR)/ethos/boot/kernel
	cp $(BUILD_DIR)/kernel $(OUT_DIR)/ethos/boot/kernel/kernel
	mkdir -p $(OUT_DIR)/iso
	grub-mkrescue -o $(OUT_DIR)/iso/$(ISO_NAME) $(OUT_DIR)/ethos/

# Run qemu
run: all
	qemu-system-i386 $(OUT_DIR)/iso/$(ISO_NAME)

# Clean
clean:
	rm -rf $(BUILD_DIR)/*
	rm -rf $(OBJ_DIR)/*
	rm -rf $(OUT_DIR)/*
