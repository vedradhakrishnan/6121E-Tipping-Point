#define _USE_MATH_DEFINES

#include "main.h"
#include <cmath>

//CONSTANTS
//voltage setting
const int DRIVE_BRAKE_TIME = 40;

const int MAX_STRAIGHT_VOLTAGE = 110;
const int MAX_TURN_VOLTAGE = 80;
const int MAX_ARC_VOLTAGE = 60;

const int INTL_TRAP = 40;
const int FINAL_TRAP = 10;

const int GYRO_COMPENSATE = 10;
const double IMU_SCALE = 30.0;

//driving modes
const int DRIVE_PID = 0;
const int DRIVE_CONST = 1;
const int DRIVE_TRAP = 2;
const int DRIVE_LOCK = 3;


//measurmeants
const double WHEEL_DIAMETER = 4.05;
const double DRIVE_GEAR_RATIO = (36.0 / 12.0) * (36.0 / 60.0);
const double CHASSIS_WIDTH = 13.11;

//targeting
const double STRAIGHT_KP = 0.08;
const double STRAIGHT_KI = 0.001;
const double STRAIGHT_KD = 2.5;

const double TURN_KP = 0.52;
const double TURN_KI = 0.001;
const double TURN_KD = 2.5;

const double ARC_KP = 0.04;
const double ARC_KI = 0.0;
const double ARC_KD = 0.0;

const double MAX_INTEGRAL = 20.0;
const double PID_ERROR = 100.0;

int chassis_mode = DRIVE_TRAP;

int left_target = 0;
int left_pos = 0;
int left_prev_error = left_target - left_pos; //aka 0
int left_integral = 0;
double left_power = 0.0;

int right_target = 0;
int right_pos = 0;
int right_prev_error = right_target - right_pos; //aka 0
int right_integral = 0;
double right_power = 0.0;

double rot_target = 0.0;

int max_power = MAX_STRAIGHT_VOLTAGE;
int accel_dist = 300;

void reset_targeting(int left, int right) {
	reset_drive_encoders();
	inertial.tare_rotation();

	left_target = left;
	left_pos = 0;
	left_prev_error = left_target - left_pos; //aka 0
	left_integral = 0;

	right_target = right;
	right_pos = 0;
	right_prev_error = right_target - right_pos; //aka 0
	right_integral = 0;
}

double chassis_rot() {
	return (100.0 / 360.0) * inertial.get_rotation();
}

double chassis_rot_error() {
  double left_comp = left_chassis_pos() / (double)(left_target);
	double right_comp = left_chassis_pos() / (double)(left_target);

	double correct_angle;
	if (left_comp > right_comp) {
		correct_angle = left_comp * rot_target;
	} else {
		correct_angle = right_comp * rot_target;
	}

	return chassis_rot() - correct_angle;
}

void straight_const(double inches, int power) {
	chassis_mode = DRIVE_CONST;
	max_power = power;

	int e_units = (inches * 900) / (M_PI * WHEEL_DIAMETER * DRIVE_GEAR_RATIO);
	reset_targeting(e_units, e_units);
	rot_target = 0.0;
}

void turn_const(double kims, int power) {
	chassis_mode = DRIVE_CONST;
	max_power = power;

	int e_units = (9 * kims * CHASSIS_WIDTH) / (WHEEL_DIAMETER * DRIVE_GEAR_RATIO);
	reset_targeting(e_units, -e_units);
	rot_target = kims;
}

void arc_const(double radius, double kims, int power) {
	chassis_mode = DRIVE_CONST;
	max_power = power;

	double left_units = 3600.0 * kims * (radius + CHASSIS_WIDTH / 2) / (WHEEL_DIAMETER * DRIVE_GEAR_RATIO);
	double right_units = 3600.0 * kims * (radius - CHASSIS_WIDTH / 2) / (WHEEL_DIAMETER * DRIVE_GEAR_RATIO) ;
	lcd::set_text(3, std::to_string((int)36.0 * kims * (radius + CHASSIS_WIDTH / 2) / (WHEEL_DIAMETER * DRIVE_GEAR_RATIO)) + " - " + std::to_string((int)right_units));



	reset_targeting(left_units, right_units);
	rot_target = kims;
}

void straight_trap(double inches, int power, int accel_units) {
	chassis_mode = DRIVE_TRAP;
	max_power = power;
	accel_dist = accel_units;

	int e_units = (inches * 900) / (M_PI * WHEEL_DIAMETER * DRIVE_GEAR_RATIO);
	reset_targeting(e_units, e_units);
	rot_target = 0.0;
}

void turn_trap(double kims, int power, int accel_units) {
	chassis_mode = DRIVE_PID;
	max_power = power;
	accel_dist = accel_units;

	int e_units = (9 * kims * CHASSIS_WIDTH) / (WHEEL_DIAMETER * DRIVE_GEAR_RATIO);
	reset_targeting(e_units, -e_units);
	rot_target = kims;
}

void straight_pid(double inches, int power) {
	chassis_mode = DRIVE_PID;
	max_power = power;

	int e_units = (inches * 900) / (M_PI * WHEEL_DIAMETER * DRIVE_GEAR_RATIO);
	reset_targeting(e_units, e_units);
	rot_target = 0.0;
}

void turn_pid(double kims, int power) {
	chassis_mode = DRIVE_PID;
	max_power = power;

	int e_units = (9 * kims * CHASSIS_WIDTH) / (WHEEL_DIAMETER * DRIVE_GEAR_RATIO);
	reset_targeting(e_units, -e_units);
	rot_target = kims;
}

void arc_pid(double radius, double kims, int power) {
	chassis_mode = DRIVE_PID;
	max_power = power;

	int left_units = 36.0 * kims / (WHEEL_DIAMETER * DRIVE_GEAR_RATIO) * (radius + CHASSIS_WIDTH / 2);
	int right_units = 36.0 * kims / (WHEEL_DIAMETER * DRIVE_GEAR_RATIO) * (radius - CHASSIS_WIDTH / 2);
	lcd::set_text(3, std::to_string((int)left_units) + " - " + std::to_string((int)right_units));


	reset_targeting(left_units, right_units);
	rot_target = kims;
}

void chassis_auton() {
	left_pos = left_chassis_pos();
	right_pos = right_chassis_pos();
	controller.set_text(2, 0, std::to_string(left_power) + "|" + std::to_string(right_power));

	if (chassis_mode == DRIVE_CONST) {
		int right_dir = right_target / abs(right_target);
		int left_dir = left_target / abs(left_target);

		if (abs(left_pos) < abs (left_target)) {
			// left_power = left_dir * max_power;
			// right_power = right_dir * max_power;
			if (abs(left_target) > abs(right_target)) {
				left_power = left_dir * max_power;
				right_power = right_dir * max_power * (abs(right_target) / fabs((double)(left_target)));
			} else {
				right_power = right_dir * max_power;
				left_power = left_dir * max_power * (abs(left_target) / fabs((double)(right_target)));
			}
		} else {
			left_power = -10 * left_dir;
			right_power = -10 * right_dir;
		}

		if (abs(left_pos) + abs(right_pos) < abs (left_target) + abs(right_target)) {
			// left_power = left_dir * max_power;
			// right_power = right_dir * max_power;
			if (abs(left_target) > abs(right_target)) {
				left_power = left_dir * max_power;
				right_power = right_dir * max_power * (abs(right_target) / fabs((double)(left_target)));
			} else {
				right_power = right_dir * max_power;
				left_power = left_dir * max_power * (abs(left_target) / fabs((double)(right_target)));
			}
		} else {
			left_power = -10 * left_dir;
			right_power = -10 * right_dir;
		}
		// set_chassis(left_power, right_power);

	} else if (chassis_mode == DRIVE_TRAP) {
		int right_dir = right_target / abs(right_target);
		int left_dir = left_target / abs(left_target);

		double power;
		double pos = (double)(abs(left_pos) + abs(right_pos)) / 2;
		double target = (double)(abs(left_target) + abs(right_target)) / 2;

		if (pos < target) {
			if (pos < accel_dist && pos < target / 2) {
				power = INTL_TRAP + ((accel_dist - pos) / accel_dist) * (max_power - INTL_TRAP);
			} else if (pos < target - accel_dist) {
				power = max_power;
			} else {
				double error = target - pos;
				power = max_power - ((accel_dist - error) / accel_dist) * (max_power - FINAL_TRAP);
			}

			double left_scale = 1.0;
			double right_scale = 1.0;
			if (abs(left_target) > abs(right_target)) {
				right_scale = fabs((double)(right_target) / left_target);
			} else if (abs(left_target) < abs(right_target)) {
				left_scale = fabs((double)(left_target) / right_target);
			}
			left_power =  left_scale * left_dir * power;
			right_power =  right_scale * right_dir * power;
		} else {
			left_power = -10 * left_dir;
			right_power = -10 * right_dir;
		}
		// set_chassis(left_power, right_power);
		// left_prev_error
	} else if (chassis_mode == DRIVE_PID) {
		int right_dir = right_target / abs(right_target);
		int left_dir = left_target / abs(left_target);

		double KP;
		double KI;
		double KD;
		if (left_target == right_target) {
			KP = STRAIGHT_KP;
			KI = STRAIGHT_KI;
			KD = STRAIGHT_KD;
		} else if (abs(left_target) == abs(right_target)) {
			KP = TURN_KP;
			KI = TURN_KI;
			KD = TURN_KD;
		} else {
			KP = ARC_KP;
			KI = ARC_KI;
			KD = ARC_KD;
		}

		if (left_dir * (left_target - left_pos) > PID_ERROR) {
			int left_error = left_target - left_pos;
			int left_deriv = left_error - left_prev_error;
			left_integral += left_error;

			double p_power = KP * left_error;
			double i_power = KP * left_integral;
			if (left_dir * i_power > MAX_INTEGRAL) {
				i_power = left_dir * MAX_INTEGRAL;
			}
			double d_power = KP * left_deriv;

			left_power = p_power + i_power + d_power;
		} else {
			left_power = -10 * left_dir;
		}

		if (right_dir * (right_target - right_pos) > PID_ERROR) {
			int right_error = right_target - right_pos;
			int right_deriv = right_error - right_prev_error;
			right_integral += right_error;

			double p_power = KP * right_error;
			double i_power = KP * right_integral;
			if (right_dir * i_power > MAX_INTEGRAL) {
				i_power = right_dir * MAX_INTEGRAL;
			}
			double d_power = KP * right_deriv;

			right_power = p_power + i_power + d_power;
		} else {
			right_power = -10 * right_dir;
		}

		//limits
		if (fabs(left_power) > fabs(right_power) && fabs(left_power) > max_power) {
			right_power = right_dir * fabs(right_power / left_power) * max_power;
			// right_power = right_dir * fabs((double)(right_target) / left_target) * max_power;
			left_power = left_dir * max_power;
		} else if (fabs(right_power) > max_power) {
			left_power = left_dir * fabs(left_power / right_power) * max_power;
			// left_power = left_dir * fabs((double)(left_target) / right_target) * max_power;
			right_power = right_dir * max_power;
		}
	}


	//gyro correction
	// if (left_target != 0 or right_target != 0) {
	// 	set_chassis(left_power + IMU_SCALE * chassis_rot_error(),
	// 	 						right_power - IMU_SCALE * chassis_rot_error());
	// } else {
	// 	set_chassis(0, 0);
	// }

	set_chassis(left_power, right_power);

	left_prev_error = left_target - left_pos;
	right_prev_error = right_target - right_pos;
}
