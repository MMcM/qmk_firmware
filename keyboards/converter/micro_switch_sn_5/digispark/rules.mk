# Digispark
MCU = attiny85

BOOTLOADER = micronucleus
OPT_DEFS += -DBOOTLOADER_SIZE=1862
PROGRAM_CMD = micronucleus --run $(BUILD_DIR)/$(TARGET).hex

# Save as much space as we can...
LTO_ENABLE = yes
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no
SPACE_CADET_ENABLE = no
