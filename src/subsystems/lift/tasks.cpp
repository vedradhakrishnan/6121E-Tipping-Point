#include "main.h"

const int DEFAULT_SPEED = 100;

void bar_lift_digital() {
  int power = DEFAULT_SPEED * (controller.get_digital(E_CONTROLLER_DIGITAL_L1) - controller.get_digital(E_CONTROLLER_DIGITAL_L2));
  set_bar_lift(power);
}

void bar_lift_task(void *parameter) {
  while (true) {
    controller.set_text(1, 1, "LIFT: " + std::to_string((int)(bar_lift.get_position())));

    if (!competition::is_autonomous()) {
      bar_lift_digital();
    }

    delay(10);
  }
}
