#include "main.h"

pros::Task chassis_control_t(chassis_control, nullptr, "name");

void initialize()
{
	pros::delay(200);
	pros::lcd::initialize();
	reset_all_encoders();
	calibrate();
	pros::delay(200);
	pros::Task sensor_t(sensors, nullptr, "name");
}

void disabled() {}
void competition_initialize() {}

void autonomous()
{
//	test();
	auton_timed_left();
//auton_timed_right();
}

void opcontrol()
{
	chassis_control_t.remove();

	pros::Task drive_control_t(drive_control, nullptr, "name");
	pros::Task intake_control_t(intake_control, nullptr, "name");

	while(true)
	{
		//intake
		if(master.get_digital(DIGITAL_R1))			intake_state = IN;
		else if(master.get_digital(DIGITAL_R2))		intake_state = OUT;
		else										intake_state = STOP;
		
		pros::delay(20);
	}
}