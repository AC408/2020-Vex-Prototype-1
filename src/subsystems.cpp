#include "main.h"

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

}

void conveyor_control(void *)
{
    
}