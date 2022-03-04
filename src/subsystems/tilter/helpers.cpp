#include "main.h"

void set_tilter(bool state) {
  back_left_piston.set_value(state ? HIGH : LOW);
  back_right_piston.set_value(state ? HIGH : LOW);
}

void set_top_clamp(bool state) {
  back_top_piston.set_value(state ? HIGH : LOW);
}
