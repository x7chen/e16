MAKE := make
CLEAN := make clean

.PHONY: all app bootloader clean
all: app bootloader
app:
	$(MAKE) -C ./app
bootloader:
	$(MAKE) -C ./bootloader
flash-app:
	$(MAKE) flash -C ./app
flash-sd:
	$(MAKE) flash_softdevice -C ./app
flash-bl:
	$(MAKE) flash -C ./bootloader
clean:
	$(CLEAN) -C ./app
	$(CLEAN) -C ./bootloader
help:
	@echo the target file in the app and bootloader folder
