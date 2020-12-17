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