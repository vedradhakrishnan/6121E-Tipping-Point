#include "main.h"


void front_clamp_driver() {
 if (controller.get_digital(DIGITAL_Y)) {
   front_clamp_up();
 } else if (controller.get_digital(DIGITAL_A)) {
   front_clamp_down();
 }
}

void front_clamp_task(void *parameter) {
  while (true) {
    controller.set_text(0, 0, "CLAW: " + std::to_string((int)(front_clamp.get_position())));

    if (!competition::is_autonomous()) {
      front_clamp_driver();
    }
    front_clamp_digital();
    delay(10);
  }
}
