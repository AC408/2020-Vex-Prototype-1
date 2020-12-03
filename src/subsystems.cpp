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
            case 2: //score
                set_index(127);
                set_intake(0);
            case 3: //hold balls
                set_index(-50);
                set_intake(127);
            case 4: //de-intake
                set_index(-50);
                set_intake(-127);
            case 0: 
                set_intake(0);
                set_index(0);
            case 5: //auton functions
        } pros::delay(20);
    }
}