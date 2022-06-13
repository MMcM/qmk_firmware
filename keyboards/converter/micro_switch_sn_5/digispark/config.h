
#pragma once

#include "config_common.h"

#define PRODUCT           Micro Switch SN-series 5(3)-key keypad converter

#define MATRIX_ROWS 1
#define MATRIX_COLS 3

// The Hall effect sensors behave closely enough to a switch to ground.
// 1 is LED; 3 & 4 are needed by USB.
#define DIRECT_PINS {{ B0, B2, B5 }}

// The stepped black PB up/down keys are sink pulse, so low for less than 50us.
#define DEBOUNCE 0

// Save as much space as we can...
#define LAYER_STATE_8BIT
#define NO_ACTION_LAYER
#define NO_ACTION_TAPPING
#define NO_ACTION_ONESHOT
#define NO_RESET

// usbconfig.h overrides
#define USB_CFG_IOPORTNAME B
#define USB_CFG_DMINUS_BIT 3
#define USB_CFG_DPLUS_BIT 4
#define USB_COUNT_SOF 0
#define USB_INTR_CFG PCMSK
#define USB_INTR_CFG_SET (1<<USB_CFG_DPLUS_BIT)
#define USB_INTR_ENABLE_BIT PCIE
#define USB_INTR_PENDING_BIT PCIF
#define USB_INTR_VECTOR SIG_PIN_CHANGE
