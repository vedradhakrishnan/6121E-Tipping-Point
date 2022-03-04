#include "main.h"

bool driver_reverse = false;

void arcade_drive() {
  int left_stick = controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
  int right_stick = controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);

  if(abs(left_stick) < 10) left_stick = 0;
  if(abs(right_stick) < 10) left_stick = 0;

  if (driver_reverse) {
    set_chassis(-right_stick, -left_stick);
  } else {
    set_chassis(left_stick, right_stick);
  }
}

void toggle_reverse() {
  driver_reverse = !driver_reverse;
}

void chassis_task(void *parameter) {
  int time = 0;
  while (true) {
    // controller.set_text(2, 0, "IMU: " + std::to_string(chassis_rot_error()));

    if (!competition::is_autonomous()) {
      arcade_drive();

      if (controller.get_digital(E_CONTROLLER_DIGITAL_X)) {
        toggle_reverse();
      }

    } else {
      time += 10;
      lcd::set_text(3, "TIME: " + std::to_string(time));
      chassis_auton();
    }
    delay(10);
  }
}
