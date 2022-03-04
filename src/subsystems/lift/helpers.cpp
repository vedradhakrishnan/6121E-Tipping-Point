#include "main.h"

const int BAR_LIFT_UPPER = 1000;
const int BAR_LIFT_LOWER = 0;

void set_bar_lift(int voltage) {
  bar_lift = voltage;
}

void bar_lift_pos(int pos, int voltage) {
  bar_lift.move_absolute(pos, voltage);
}
