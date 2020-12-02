#include "main.h"

int ball = 0;
int intake_state = 0;

void drive_control(void *)
{
    pros::Controller master(CONTROLLER_MASTER);
    drive_coast(); //motor isnt running
    while (true)
    {
        //set drive motor
        set_left(master.get_analog(ANALOG_LEFT_Y));
        set_right(master.get_analog(ANALOG_RIGHT_Y));
        
        pros::delay(20);
    }
}

void intake_control(void *)
{
    intake_coast();
    while(true){
        if(intake_state == 1){
            set_intake(127);
        } else if (intake_state == -1){
            set_intake(-127);
        } else {
            set_intake(0);
        }
    }
}

void conveyor_control(void *)
{
    double count = 0;
    while(true){
        if(ball == 4) { //reindex 

        } else if(count<ball){
            if(get_convey_line()>=100){ //run full speed until ball is detected
                set_convey(127);
            } else {
                while(get_convey_line()<100){ //slows down to accurately track ball
                    set_convey(70);
                    pros::delay(10);
                }
                count++;
            }
        } else{
            while(get_intake_line()<100){ //primes next ball
                set_convey(127);
                pros::delay(10);
            } set_convey(0);
            count = 0;
            ball = 0;
        }
        pros::delay(10);
    }
}