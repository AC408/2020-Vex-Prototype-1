#include "main.h"
void on_center_button()
{
	static bool pressed = false;
	pressed = !pressed;
	if (pressed)
		pros::lcd::set_text(2, "I was pressed!");
	else
		pros::lcd::clear_line(2);
}

void initialize()
{
	pros::lcd::initialize();
	pros::lcd::register_btn1_cb(on_center_button);

	Logger::setDefaultLogger(
    	std::make_shared<Logger>(
			TimeUtilFactory::createDefault().getTimer(), // It needs a Timer
			"/ser/sout", // Output to the PROS terminal
			Logger::LogLevel::debug // Show errors and warnings
		)
	);

	reset_all_encoders();
	calibrate();
	pros::delay(200);
	pros::Task conveyor_control_t(conveyor_control, nullptr, "name");
	pros::Task intake_control_t(intake_control, nullptr, "name");
}

void disabled() {}

void competition_initialize() {}

void autonomous()
{
}

pros::Controller master(CONTROLLER_MASTER);

void button(pros::controller_digital_e_t btn){
	while(master.get_digital(btn)){
		pros::delay(10);
	}
}

void opcontrol()
{
	

	pros::Task drive_control_t(drive_control, nullptr, "name");

	while (true)
	{
		pros::delay(20);
		if(master.get_digital(DIGITAL_RIGHT)){
			button(DIGITAL_RIGHT);
			ball = 1;
		} else if(master.get_digital(DIGITAL_LEFT)){
			button(DIGITAL_LEFT);
			ball = 2;
		}

		if(master.get_digital(DIGITAL_L1)){
			button(DIGITAL_L1);
			intake_state = 1;
		} else if(master.get_digital(DIGITAL_L2)){
			button(DIGITAL_L2);
			intake_state = -1;
		} else{
			intake_state = 0;
		}
	}
}