# Leonardo
MCU = atmega32u4

# Interrupt driven control endpoint task(+60)
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT

BOOTLOADER = catalina

BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = no        # Mouse keys(+4700)
EXTRAKEY_ENABLE = no        # Audio control and System control(+450)
CONSOLE_ENABLE = yes        # Console for debug(+400)
COMMAND_ENABLE = yes        # Commands for debug and configuration
NKRO_ENABLE = no            # Nkey Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
MIDI_ENABLE = no            # MIDI controls
AUDIO_ENABLE = no           # Audio output on port C6
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight.
API_SYSEX_ENABLE = no
SPLIT_KEYBOARD = no
WAIT_FOR_USB = yes
LAYOUTS_HAS_RGB = no
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
CUSTOM_MATRIX = yes

SRC = matrix.c

HARDWARE_SERIAL = yes
SRC += protocol/serial_uart.c
