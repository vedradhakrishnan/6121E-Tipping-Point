#include "main.h"

Motor drive_lb(1, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_COUNTS);
// Motor drive_lc(2, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_COUNTS);
Motor drive_lf(2, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_COUNTS);
Motor drive_rb(3, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_COUNTS);
// Motor drive_rc(4, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_COUNTS);
Motor drive_rf(4, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_COUNTS);

Motor front_clamp(11, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_COUNTS);
ADIDigitalOut back_left_piston('A');
ADIDigitalOut back_right_piston('B');
ADIDigitalOut back_top_piston('C');
ADIDigitalOut front_piston('D');


Motor bar_lift(6, E_MOTOR_GEARSET_36, false, E_MOTOR_ENCODER_COUNTS);

Motor conveyor(10, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_COUNTS);


Controller controller(E_CONTROLLER_MASTER);

Imu inertial(14);
