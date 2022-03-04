#include "main.h"

const int FRONT_CLAMP_UPPER = 700;
const int FRONT_CLAMP_LOWER = 300;
const int FRONT_CLAMP_ERROR = 20;
bool clamp_down = true;

void set_front_clamp(int voltage) {
  front_clamp = voltage;
}

int front_clamp_pos() {
  return front_clamp.get_position();
}

void front_clamp_up() {
  clamp_down = false;
}

void front_clamp_down() {
  clamp_down = true;
}

void front_clamp_digital() {
  if (clamp_down) {
    if (abs(front_clamp_pos() - FRONT_CLAMP_LOWER) < FRONT_CLAMP_ERROR) {
      set_front_clamp(0);
    } else if (front_clamp_pos() > FRONT_CLAMP_LOWER) {
      set_front_clamp(-80);
    } else {
      set_front_clamp(10);
    }
  } else {
    if (abs(front_clamp_pos() - FRONT_CLAMP_UPPER) < FRONT_CLAMP_ERROR) {
      set_front_clamp(10);
    } else if (front_clamp_pos() > FRONT_CLAMP_UPPER) {
      set_front_clamp(0);
    } else {
      set_front_clamp(80);
    }
  }


}
