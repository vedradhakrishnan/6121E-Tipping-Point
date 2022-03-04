#include "main.h"

void set_chassis(int left, int right) {
  drive_lb = left;
  // drive_lc = left;
  drive_lf = left;

  drive_rb = right;
  // drive_lc = left;
  drive_rf = right;
}

double left_chassis_pos() {
  return (drive_lb.get_position()
          + drive_lf.get_position()) / 2.0;

  // return (drive_lb.get_position()
  //         + drive_lc.get_position()
  //         + drive_lf.get_position()) / 3.0;
}

double right_chassis_pos() {
  return (drive_rb.get_position()
          + drive_rf.get_position()) / 2.0;

  // return (drive_rb.get_position()
  //         + drive_rc.get_position()
  //         + drive_rf.get_position()) / 3.0;
}

void reset_drive_encoders() {
  drive_lb.tare_position();
  // drive_lc.tare_position();
  drive_lf.tare_position();

  drive_rb.tare_position();
  // drive_rc.tare_position();
  drive_rf.tare_position();
}

void chassis_lock() {
  drive_lb.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  // drive_lc.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  drive_lf.set_brake_mode(E_MOTOR_BRAKE_HOLD);

  drive_rb.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  // drive_lc.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  drive_rf.set_brake_mode(E_MOTOR_BRAKE_HOLD);
}

void chassis_unlock() {
  drive_lb.set_brake_mode(E_MOTOR_BRAKE_COAST);
  // drive_lc.set_brake_mode(E_MOTOR_BRAKE_COAST);
  drive_lf.set_brake_mode(E_MOTOR_BRAKE_COAST);

  drive_rb.set_brake_mode(E_MOTOR_BRAKE_COAST);
  // drive_lc.set_brake_mode(E_MOTOR_BRAKE_COAST);
  drive_rf.set_brake_mode(E_MOTOR_BRAKE_COAST);
}
