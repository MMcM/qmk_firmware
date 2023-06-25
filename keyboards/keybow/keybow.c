
#include "quantum.h"

void keyboard_pre_init_kb(void) {
    // No CS support in APA102 driver; just enable always.
    setPinOutput(RGB_CS_PIN);
    writePinLow(RGB_CS_PIN);

    keyboard_pre_init_user();
}
