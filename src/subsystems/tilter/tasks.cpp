#include "main.h"

bool back_clamp_down = true;
bool button_press = true;
int top_timer = 0;

void toggle_tilter() {
  back_clamp_down = !back_clamp_down;
}


void tilter_task(void *parameter) {
  while (true) {

    if (!competition::is_autonomous()) {
      if (controller.get_digital(E_CONTROLLER_DIGITAL_R1)) tilter_up();
      if (controller.get_digital(E_CONTROLLER_DIGITAL_R2)) tilter_down();
    }

    tilter_macro(back_clamp_down);
    top_timer += 10;
    delay(10);
  }
}

void tilter_macro(bool state) {
  if (state) {
    if (top_timer < 200) {
      set_tilter(LOW);
      set_top_clamp(LOW);
    } else {
      set_tilter(HIGH);
      set_top_clamp(LOW);
    }
  } else {
    if (top_timer < 600) {
      set_tilter(HIGH);
      set_top_clamp(HIGH);
    } else if (top_timer < 1200) {
      set_tilter(LOW);
      set_top_clamp(HIGH);
    } else {
      set_tilter(LOW);
      set_top_clamp(LOW);
    }
  }
}


void tilter_up() {
  back_clamp_down = LOW;
  top_timer = 0;
}

void tilter_down() {
  back_clamp_down = HIGH;
  top_timer = 0;
}
