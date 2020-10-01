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
}

void disabled() {}

void competition_initialize() {}

void autonomous()
{
}

void opcontrol()
{
	
	pros::Controller master(CONTROLLER_MASTER);

	pros::Task drive_control_t(drive_control, nullptr, "name");
	pros::Task intake_control_t(intake_control, nullptr, "name");
	pros::Task conveyor_control_t(conveyor_control, nullptr, "name");

	while (true)
	{
		pros::delay(20);
	}
}