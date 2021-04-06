#include "main.h"

pros::Controller master(CONTROLLER_MASTER);

int intake_state = 0;
int sensor_state = 0;
int left = 0,
    right = 0;

float curve_function(int x)
{
    if(CURVE_SCALE!=0)
        return (powf(2.718,-(CURVE_SCALE/10))+powf(2.718, (abs(x)-127)/10)*(1-powf(2.718,-(CURVE_SCALE/10))))*x;
    return x;
}

void drive_control(void *)
{
    set_drive_brake(MOTOR_BRAKE_COAST);
    while(true)
    {
        //tank
        left = curve_function(master.get_analog(ANALOG_LEFT_Y));
        right = curve_function(master.get_analog(ANALOG_RIGHT_Y));
        
        //arcade
        // left = curve_function(master.get_analog(ANALOG_LEFT_Y)) + master.get_analog(ANALOG_RIGHT_X);
        // right = curve_function(master.get_analog(ANALOG_LEFT_Y)) - master.get_analog(ANALOG_RIGHT_X);
        set_tank(left,right);
    }
    pros::delay(20);
}

void intake_control(void *)
{
    set_intake_brake(MOTOR_BRAKE_COAST);
    while(true){
        double intake_input = abs((left+right)/2);
        if(intake_input<10){
            intake_input = 127;
        }
        switch(intake_state)
        {
            case IN:
                set_intake(intake_input);
                break;
            case OUT:
                set_intake(-intake_input);
                break;
            case STOP:
                set_intake(0);
                break;
            case SLOW_OUT:
                set_intake(-80);
                break;
        }
        pros::delay(20);
    }
}

void display_sensors(){
    pros::lcd::set_text(1, "heading"+std::to_string(get_angle()));
    pros::lcd::set_text(2, "l_encoder"+std::to_string(get_left_pos()));
    pros::lcd::set_text(3, "r_encoder"+std::to_string(get_right_pos()));
    pros::lcd::set_text(4, "intake"+std::to_string(get_intake_pos()));
}

void display_temp(){
    pros::lcd::set_text(0, "LIntake"+std::to_string(get_lintake_temp()));
    pros::lcd::set_text(1, "RIntake"+std::to_string(get_rintake_temp()));
    pros::lcd::set_text(2, "LBD"+std::to_string(get_lbd_temp()));
    pros::lcd::set_text(3, "LBU"+std::to_string(get_lbu_temp()));                
    pros::lcd::set_text(4, "LF"+std::to_string(get_lf_temp()));
    pros::lcd::set_text(5, "RBD"+std::to_string(get_rbd_temp()));
    pros::lcd::set_text(6, "RBU"+std::to_string(get_rbu_temp()));
    pros::lcd::set_text(7, "RF"+std::to_string(get_rf_temp()));                
}

void sensors(void*){
    while(true)
    {
        if(sensor_state = TEMP){
            display_temp();
        } else {
            display_sensors();
        }
        pros::delay(100);
    }
}