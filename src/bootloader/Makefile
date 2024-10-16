BOOTLOADER_SRCS=$(wildcard $(SRC_DIR)/bootloader/*.s)
BOOTLOADER_OBJS=$(patsubst $(SRC_DIR)/bootloader/%.s, $(OBJ_DIR)/%.o, $(BOOTLOADER_SRCS))

all: bootloader

bootloader: $(BOOTLOADER_OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/bootloader/%.s
	$(ASM) $(ASMFLAGS) -o $@ $<
