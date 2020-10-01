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

	// Logger::setDefaultLogger(
    // 	std::make_shared<Logger>(
	// 		TimeUtilFactory::createDefault().getTimer(), // It needs a Timer
	// 		"/ser/sout", // Output to the PROS terminal
	// 		Logger::LogLevel::debug // Show errors and warnings
	// 	)
	// );

	// reset_all_encoders();
	// calibrate();
	pros::delay(200);
	// pros::Task conveyor_control_t(conveyor_control, nullptr, "name");
	// pros::Task intake_control_t(intake_control, nullptr, "name");
}

void disabled() {}

void competition_initialize() {}

void autonomous()
{
}

// pros::Controller master(CONTROLLER_MASTER);

// void button(pros::controller_digital_e_t btn){
// 	while(master.get_digital(btn)){
// 		pros::delay(10);
// 	}
// }

void opcontrol()
{
	
	pros::Controller master(CONTROLLER_MASTER);


	// pros::Task drive_control_t(drive_control, nullptr, "name");

	// while (true)
	// {
	// 	pros::delay(20);
	// 	if(master.get_digital(DIGITAL_RIGHT)){
	// 		button(DIGITAL_RIGHT);
	// 		ball = 1;
	// 	} else if(master.get_digital(DIGITAL_LEFT)){
	// 		button(DIGITAL_LEFT);
	// 		ball = 2;
	// 	}

	// 	if(master.get_digital(DIGITAL_L1)){
	// 		button(DIGITAL_L1);
	// 		intake_state = 1;
	// 	} else if(master.get_digital(DIGITAL_L2)){
	// 		button(DIGITAL_L2);
	// 		intake_state = -1;
	// 	} else{
	// 		intake_state = 0;
	// 	}
	// }

	while(true){
		
		//presets
		drive_coast();
		intake_coast();

		//chassis
		
		//lin motion
		float leftBack = master.get_analog(ANALOG_RIGHT_Y)-master.get_analog(ANALOG_RIGHT_X);
		float leftFront = master.get_analog(ANALOG_RIGHT_Y)+master.get_analog(ANALOG_RIGHT_X);
		float rightFront = master.get_analog(ANALOG_RIGHT_Y)-master.get_analog(ANALOG_RIGHT_X);
		float rightBack = master.get_analog(ANALOG_RIGHT_Y)+master.get_analog(ANALOG_RIGHT_X);
		float motorPwd[4] = {leftBack,leftFront,rightFront,rightBack};
		if(abs(master.get_analog(ANALOG_RIGHT_X)+abs(master.get_analog(ANALOG_RIGHT_Y)))>(127*2)){
			float max = abs(master.get_analog(ANALOG_RIGHT_X))+abs(master.get_analog(ANALOG_LEFT_X));
			for(int i = 0; i < 4; i++){
				motorPwd[i]*= 127/max; //proportion motor to each other and max voltage
			}
		}

		//add rotation
		float max = 0;
		leftBack+=master.get_analog(ANALOG_LEFT_Y);
		leftFront+=master.get_analog(ANALOG_LEFT_Y);
		rightFront-=master.get_analog(ANALOG_LEFT_Y);
		rightBack-=master.get_analog(ANALOG_LEFT_Y);
		for(int i = 0; i < 4; i++){ //find max power
			if(abs(motorPwd[i])>127){
				max = abs(motorPwd[i]);
			}
		} if(max>0){
			for(int i = 0; i<4; i++){
				motorPwd[i]*=127/max; //proportion motor to each other and max voltage
			}
		}

		//set drive motor
		set_left_back(leftBack);
		set_left_front(leftFront);
		set_right_front(rightFront);
		set_right_back(rightBack);
		

		//intake
		if(master.get_digital(DIGITAL_L1)){
			set_intake(127);
		} else if(master.get_digital(DIGITAL_L2)){
			set_intake(-127);
		} else {
			set_intake(0);
		}

		//conveyor
		if(master.get_digital(DIGITAL_R1)){
			set_convey(127);
		} else if(master.get_digital(DIGITAL_R2)){
			set_convey(-127);
		} else {
			set_convey(0);
		}

		pros::delay(20);
	}
}