#include "main.h"


//MOTORS
//drive

extern Motor drive_lb;
extern Motor drive_lc;
extern Motor drive_lf;

extern Motor drive_rb;
extern Motor drive_rc;
extern Motor drive_rf;

//clamps
extern Motor front_clamp;
extern ADIDigitalOut back_left_piston;
extern ADIDigitalOut back_right_piston;
extern ADIDigitalOut back_top_piston;
extern ADIDigitalOut front_piston;

//4bar
extern Motor bar_lift;

extern Motor conveyor;

//CONTROLLER
extern Controller controller;

//SENSOR(S)
extern Imu inertial;
