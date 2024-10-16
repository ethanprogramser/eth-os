GRUB_CFG_LOCATION=$(OUT_DIR)/ethos/boot/grub

all: $(OUT_DIR)/ethos/boot/grub/grub.cfg

$(GRUB_CFG_LOCATION)/grub.cfg: $(SRC_DIR)/grub/grub.cfg
	mkdir -p $(GRUB_CFG_LOCATION)
	cp $< $@
