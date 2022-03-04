#include "main.h"

//ALL CONSTANTS
//voltage setting
extern const int DRIVE_BRAKE_TIME;

extern const int MAX_STRAIGHT_VOLTAGE;
extern const int MAX_TURN_VOLTAGE;
extern const int MAX_ARC_VOLTAGE;

extern const int GYRO_COMPENSATE;

//driving modes
extern const int DRIVE_PID;
extern const int DRIVE_CONST;
extern const int DRIVE_TRAP;
extern const int DRIVE_LOCK;


//measurmeants
extern const double WHEEL_DIAMETER;
extern const double DRIVE_GEAR_RATIO;

//targeting
extern const double STRAIGHT_KP;
extern const double STRAIGHT_KI;
extern const double STRAIGHT_KD;

extern const double TURN_KP;
extern const double TURN_KI;
extern const double TURN_KD;

extern const double ARC_KP;
extern const double ARC_KI;
extern const double ARC_KD;


void reset_targeting(int left, int right);

double chassis_rot();

double chassis_rot_error();

void straight_const(double inches, int power);

void turn_const(double kims, int power);

void arc_const(double radius, double kims, int power);

void straight_trap(double inches, int power, int accel_units);

void turn_trap(double kims, int power, int accel_units);

void straight_pid(double inches, int power);

void turn_pid(double kims, int power);

void arc_pid(double radius, double kims, int power);

void chassis_auton();
