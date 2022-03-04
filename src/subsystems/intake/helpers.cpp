#include "main.h"

bool intake = false;

const int INTAKE_FORWARD = 120;
const int INTAKE_BACKWARD = -120;

void set_intake(int voltage) {
  conveyor = voltage;
}

void intake_control() {
  if(controller.get_digital(DIGITAL_UP) && !intake) {
    intake = true;
    set_intake(INTAKE_FORWARD);
  } else if (controller.get_digital(DIGITAL_UP) && intake) {
    intake = false;
    set_intake(0);
  } else
    intake = false;
}

void intake_toggle() {
  intake = !intake;
  set_intake(intake ? INTAKE_FORWARD : 0);
}
