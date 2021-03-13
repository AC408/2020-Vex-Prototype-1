#include "main.h"

int intake_state = 0;
int cata_state = 0;
pros::Controller master(CONTROLLER_MASTER);

int left = 0;
int right = 0;
float CURVE_SCALE = 2.2;

float curve_function(int x)
{
    if (CURVE_SCALE != 0)
        return (powf(2.718, -(CURVE_SCALE/10)) + powf(2.718, (abs(x)-127)/10) * (1-powf(2.718, -(CURVE_SCALE/10))))*x;
    return x;
}

void drive_control(void *)
{
    drive_coast();
    while(true)
    {
        //non curved
        //left = master.get_analog(ANALOG_LEFT_Y);
        //right = master.get_analog(ANALOG_RIGHT_Y);

        //curved
        left = curve_function(master.get_analog(ANALOG_LEFT_Y));
        right = curve_function(master.get_analog(ANALOG_RIGHT_Y));

        //normal
        set_tank(left, right);

        //backwards
        //set_tank(-right, -left);
    }
    pros::delay(20);
}

void intake_control(void *)
{
    intake_coast();
    while(true){
        switch(intake_state){
            case 1: //intake
                set_intake(127);
                break;
            case 2: //outtake
                set_intake(-127);
                break;
            case 0: //stop
                set_intake(0);
                break;
            case 3: //auton functions
                break;
        }
        pros::delay(20);
    }
}

void cata_control(void *)
{
    cata_coast();
    while(true)
    {
        if(master.get_digital(DIGITAL_L1)){
			set_cata(127);
			pros::delay(600);
			while (!cata_pressed())
			{
				pros::delay(10);
			}
			set_cata(10);
		}
        pros::delay(10);
    }
}

void sensors(void*){
    while(1){
        pros::lcd::set_text(1, "heading"+std::to_string(get_angle()));
        pros::lcd::set_text(2, "l_encoder"+std::to_string(get_left_pos()));
        pros::lcd::set_text(3, "r_encoder"+std::to_string(get_right_pos()));
        pros::lcd::set_text(4, "intake"+std::to_string(get_intake_pos()));
        pros::lcd::set_text(5, "cata"+std::to_string(get_cata_pos()));
        pros::delay(100);
    }
}