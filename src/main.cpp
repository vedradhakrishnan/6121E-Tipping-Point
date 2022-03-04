#include "main.h"

void on_center_button() {
	static bool center_press = false;
	center_press = !center_press;
	if (center_press) {
		lcd::set_text(2, "Starting Auton!");
		delay(1000);
		autonomous();
	} else {
		lcd::clear_line(2);
	}
}

void on_right_button() {
	static bool left_press = false;
	left_press = !left_press;
	if (left_press) {
		lcd::set_text(2, "Starting Driver!");
		delay(1000);
		autonomous();
	} else {
		lcd::clear_line(2);
	}
}

void initialize() {
	lcd::initialize();
	lcd::set_text(1, "Hello PROS User!");

	lcd::register_btn1_cb(on_center_button);

	controller.set_text(0, 0, "Calibrating...");

	Imu inertial(14);
	inertial.reset();

	// while (inertial.is_calibrating()) {
	// 	delay(10);
	// }
	delay(2000);

	//RESET NECESARY ENCODERS
	front_clamp.tare_position();
	bar_lift.tare_position();


	//BRAKE MODE STUFF
	chassis_unlock();
	bar_lift.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	front_clamp.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	conveyor.set_brake_mode(E_MOTOR_BRAKE_HOLD);

	controller.set_text(1, 0, "Ready to Go!");
	// delay(500);



	Task chassis(chassis_task);
	Task clamp(front_clamp_task);
	Task lift(bar_lift_task);
	Task intake(intake_task);
	Task tilter(tilter_task);

	set_tilter(false);

	// opcontrol();

}

void disabled() { /* ~crickets~ */ }

void competition_initialize() { /* ~more crickets~ */ }

void autonomous() {
	delay(3000); //need this if not comp switch
	// lcd::set_text(2, "AMIL IS A CARTI STAN");

	// left_win_point();
	right_win_point();
	// left_compound_rush();

	// delay(15000);

	// auton_skills();
}

void opcontrol() {}
