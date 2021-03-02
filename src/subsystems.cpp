#include "main.h"

int intake_state = 0;
bool cata_bool = false;

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

void cata_control(void *)
{
    cata_hold();
    bool cocked = false;
    while(true){
        if(!cocked){ //auto cock the cata
            while(!cata_pressed()){
                set_cata(127);
                pros::delay(20);
            } cocked = true;
        } 
        if(cata_bool){ //shoot
            set_cata(127);
            cocked = false;
            cata_bool = false;
        } else{
            set_cata(25); //tune constant
        }    
        pros::delay(20);
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