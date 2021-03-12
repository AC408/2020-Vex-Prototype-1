#include "main.h"

int intake_state = 0;
int cata_state = 0;

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
        } pros::delay(20);
    }
}

void auto_cock(){
    set_cata(127);
    while (!cata_pressed())
    {
        pros::delay(10);
    }
    set_cata(-50);
    pros::delay(100);
}

void cata_control(void *)
{
    cata_coast();
    while(true)
    {
        switch(cata_state){
            case 1: //driver control
                auto_cock();
                set_cata(20);
                cata_state = 0;
                break;
            case 2: //auton
                set_cata(20);
                pros::delay(1000); //tunable
                auto_cock();
                cata_state = 3;
                break;
            case 0:
                break;        
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