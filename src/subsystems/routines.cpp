#include "main.h"

void auton_skills() {
  front_clamp_up();
  straight_pid(50.0, 100);
  delay(2300);

  front_clamp_down();
  delay(200);


  bar_lift_pos(800, 200);
  delay(400);
  // straight_pid(-34.0, 100);
  straight_pid(-25.0, 100);

  delay(1500);

  // front_clamp_up();

  turn_const(-28.0, 127);

  delay(2000);

  straight_pid(-12.0, 100);

  delay(2000);

  tilter_down();

  delay(2000);

  intake_toggle();
  straight_pid(45.0, 100);
  delay(2000);


  turn_const(-28.0, 127);
  delay(2000);

  straight_pid(10.0, 100);
  bar_lift_pos(2800, 200);
  delay(2000);

  bar_lift_pos(2400, 200);
  delay(2000);

  front_clamp_up();
  delay(100);
  bar_lift_pos(2800, 200);
  straight_pid(-10.0, 100);
  delay(2000);

  // arc_pid(4.0, 60.0, 80);
  delay(4000);
}

void left_compound_rush() {
  front_clamp_up();
  straight_const(38.0, 120);
  delay(1800);

  front_clamp_down();
  delay(200);

  straight_pid(-34.0, 100);
  delay(300);

  bar_lift_pos(1800, 200);
  delay(2000);

  turn_const(-22.5, 120);
  delay(2300);

  straight_pid(-15.0, 100);
  delay(2300);

  tilter_up();
  delay(700);

  straight_pid(15.0, 100);
  intake_toggle();

  delay(2300);
}

void left_win_point() {
  front_clamp_down();
  straight_trap(12.0, 60, 800);
  bar_lift_pos(1000, 200);

  delay(1000);

  turn_trap(12.0, 60, 800);
  delay(1000);

  straight_trap(18.0, 60, 800);
  delay(1500);

  front_clamp_up();

  // toggle_tilter();


}

void right_win_point() {
  turn_gyro(25.0, 120);
  delay(1000);

  turn_gyro(-50.0, 120);
}
