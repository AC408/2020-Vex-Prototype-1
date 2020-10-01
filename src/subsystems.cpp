#include "main.h"

int ball = 0;
int intake_state = 0;

void drive_control(void *)
{
    pros::Controller master(CONTROLLER_MASTER);
    drive_coast(); //motor isnt running
    while (true)
    {
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