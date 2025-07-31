FLASH_PARAMS?=-f interface/stlink.cfg -f target/stm32g0x.cfg

build: clean
	make -C output bip3gn.elf bip3gn.siz

clean:
	make -C output clean

./output/bip3gn.elf: build

flash: ./output/bip3gn.elf
	openocd $(FLASH_PARAMS) -c 'init; reset init; flash probe 0;' \
		-c 'stm32g0x mass_erase 0; sleep 250;' \
		-c "program $< verify reset;" \
		-c 'shutdown' 2>/dev/null

.PHONY: build clean flash
