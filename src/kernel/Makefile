KERNEL_SRCS=$(wildcard $(SRC_DIR)/kernel/*.c)
KERNEL_OBJS=$(patsubst $(SRC_DIR)/kernel/%.c, $(OBJ_DIR)/%.o, $(KERNEL_SRCS))

all: $(KERNEL_OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/kernel/%.c
	$(CC) $(CFLAGS) -c $< -o $@
