#include "main.h"

pros::Task drive_control_t(drive_control, nullptr, "name");

void initialize()
{
	pros::delay(200);
	pros::lcd::initialize();
	reset_all_encoders();
	calibrate();
	pros::delay(200);
	pros::Task intake_control_t(intake_control, nullptr, "name");
	pros::Task cata_control_t(cata_control, nullptr, "name");
	pros::Task sensor_t(sensors, nullptr, "name");

}

void disabled() {}
void competition_initialize() {}

void autonomous()
{
	test();
}

void opcontrol()
{
	drive_control_t.remove();

	pros::Controller master(CONTROLLER_MASTER);

	while(true){
		//drive
		drive_coast();
		set_left(master.get_analog(ANALOG_LEFT_Y));
        set_right(master.get_analog(ANALOG_RIGHT_Y));

		//intake
	    intake_coast();
		if(master.get_digital(DIGITAL_R1)){
			intake_state = 1; //intake
		} else if(master.get_digital(DIGITAL_R2)){
			intake_state = 2; //outtake
		} else{
			intake_state = 0; //stop
		}

		if(master.get_digital(DIGITAL_L1)){
			cata_state = 1;
		}

		pros::delay(20);
	}
}