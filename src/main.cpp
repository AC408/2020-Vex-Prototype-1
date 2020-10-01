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
	pros::delay(200);

	intake_hold();

	auto_selector();
	pros::delay(100);
	if (selector == 1)
		init_unprotect();
	if (selector == 2)
		init_unprotect();
	if (selector == 3)
		init_protect();
	if (selector == 4)
		init_protect();
	if (selector == 5)
	{
		tank = false;
		init_skills();
	}
	if(selector == 6){

	}
}

void disabled() {}

void competition_initialize() {}

void autonomous()
{
	pros::Task output(sensors, nullptr, "name");

	if (selector == 1)
		unprotect(RED);
	if (selector == 2)
		unprotect(BLUE);
	if (selector == 3)
		protect(RED);
	if (selector == 4)
		protect(BLUE);
	if (selector == 5)
		skill();
	if (selector == 6) //TESTING SLOT
		one_cube();
}

void opcontrol()
{
	
	pros::Controller master(CONTROLLER_MASTER);
	master.set_text(0, 0, "#ThankYou448X");
	start_driver();

	stacking_state();

	pros::Task drive_control_t(drive_control, nullptr, "name");
	pros::Task tray_control_t(tray_control, nullptr, "name");
	pros::Task arm_control_t(arm_control, nullptr, "name");

	while (true)
	{
		pros::lcd::set_text(1, "Selector Value: " + std::to_string(selector));
		pros::lcd::set_text(2, "Tray Sensor:" + std::to_string(get_tray_pos()));
		pros::lcd::set_text(3, "Arm Sensor:" + std::to_string(get_arm_pos()));

		std::cout<<get_tray_pos()<<std::endl; //print to terminal 
		std::cout<<get_tray_pos()<<std::endl; 

		pros::delay(20);
	}
}