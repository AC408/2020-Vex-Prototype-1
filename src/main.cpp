#include "main.h"

pros::Task drive_control_t(drive_control, nullptr, "name");

void initialize()
{
	pros::delay(200);
	pros::lcd::initialize();
	reset_all_encoders();
	calibrate();
	pros::delay(200);
	pros::Task score_control_t(score_control, nullptr, "name");
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

		//rest
	    intake_coast();
	    index_coast();
		if(master.get_digital(DIGITAL_L1)){
			score_state = 1; //full score
		} else if(master.get_digital(DIGITAL_L2)){
			score_state = 2; //score, no intake
		} else if(master.get_digital(DIGITAL_R1)){
			score_state = 3; //no score, intake
		} else if(master.get_digital(DIGITAL_R2)){
			score_state = 4; //de-intake
		} else{
			score_state = 0; //stop
		}
		pros::delay(20);
	}
}