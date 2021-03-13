#include "main.h"

//pros::Task drive_control_t(drive_control, nullptr, "name");

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
	for_avi();
}

void opcontrol()
{
	pros::Task drive_control_t(drive_control, nullptr, "name");
	pros::Task intake_control_t(intake_control, nullptr, "name");
	pros::Task cata_control_t(cata_control, nullptr, "name");
	//drive_control_t.remove();

	while(true)
	{
		//intake
	    intake_coast();
		if(master.get_digital(DIGITAL_R1))
			intake_state = 1; //intake
		else if(master.get_digital(DIGITAL_R2))
			intake_state = 2; //outtake
		else
			intake_state = 0; //stop
		pros::delay(20);
	}
}