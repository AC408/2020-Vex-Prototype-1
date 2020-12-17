#include "main.h"

int score_state = 0;

void score_control(void *)
{
    intake_coast();
    index_coast();
    while(true){
        switch(score_state){
            case 1: //full score
                set_index(127);
                set_intake(127);
                break;
            case 2: //score
                set_index(127);
                set_intake(0);
                break;
            case 3: //hold balls
                set_index(-127);
                set_intake(127);
                break;
            case 4: //de-intake
                set_index(0);
                set_intake(-127);
                break;
            case 0: 
                set_intake(0);
                set_index(0);
                break;
            case 5: //auton functions
                break;
        } pros::delay(20);
    }
}

void sensors(void*){
    while(1){
        pros::lcd::set_text(1, "heading"+std::to_string(get_angle()));
        pros::lcd::set_text(2, "l_encoder"+std::to_string(get_left_pos()));
        pros::lcd::set_text(3, "r_encoder"+std::to_string(get_right_pos()));
        pros::lcd::set_text(4, "intake"+std::to_string(get_intake_pos()));
        pros::lcd::set_text(5, "indexer"+std::to_string(get_index_pos()));
        pros::delay(100);
    }
}