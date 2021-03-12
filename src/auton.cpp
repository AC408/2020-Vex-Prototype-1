#include "main.h"

//states
int state = 0;

//global params
double targetTheta = 0;
double targetLeft = 0;
double targetRight = 0;

double velCap = 0;
double accelLimit = 0;
double speedLimit = 0;
double tolerance = 0;

double omegaCap = 0;
double alphaLimit = 0;
double omegaLimit = 0;
double theta_tolerance = 0;

bool isSettled = false;

//gains
double kP_turn = .2;
double kP = .1;

//drive function
void set_angle(double angle, double omega = 100, double alpha = 5, double theta_tol = 15, double theta_gain = .2){
    reset_drive_encoder();
    targetTheta = angle;
    omegaLimit = omega;
    alphaLimit = alpha;
    kP_turn = theta_gain;
    theta_tolerance = theta_tol;
    isSettled = false;
    state = 1;
}

void set_dist(double dist, double speed = 100, double accel = 5, double tol = 100, double gain = .1){
    reset_drive_encoder();
    targetLeft = targetRight = dist;
    speedLimit = speed;
    accelLimit = accel;
    kP = gain;
    tolerance = tol;
    isSettled = false;
    state = 2;
}
  
//pid thread
void drive_control(void *)
{

    drive_hold();

    double errorTheta = 0;
    double errorLeft = 0;
    double errorRight = 0;

    double signTheta = 0;
    double signLeft = 0;
    double signRight = 0;

    double outputTheta = 0;
    double outputLeft = 0;
    double outputRight = 0;

    while(true){
        switch(state){
            case 1: //relative angle, not global/absolute
                {
                    errorTheta = targetTheta - get_angle();

                    signTheta = errorTheta / abs(errorTheta);

                    outputTheta = errorTheta * kP_turn;

                    omegaCap += alphaLimit;

                    if (omegaCap > omegaLimit)
                        omegaCap = omegaLimit;

                    if (abs(outputTheta) > velCap)
                        outputTheta = omegaCap * signTheta;

                    if (abs(errorTheta) < theta_tolerance)
                    {
                        isSettled = true;
                        targetTheta = signTheta = outputTheta = errorTheta = 0;
                        state = 0;
                        set_left(0);
                        set_right(0);
                        reset_imu();
                        break;
                    }

                    set_left(outputLeft);
                    set_right(outputRight);
                    break;

                }
            case 2: //drive
                {
                    errorLeft = targetLeft - get_left_pos();
                    errorRight = targetRight - get_right_pos();

                    signLeft = errorLeft / abs(errorLeft);
                    signRight = errorRight / abs(errorRight);

                    outputLeft = errorLeft * kP;
                    outputRight = errorRight * kP;

                    velCap += accelLimit;

                    if (velCap > speedLimit)
                        velCap = speedLimit;

                    if (abs(outputLeft) > velCap)
                        outputLeft = velCap;

                    if (abs(outputRight) > velCap)
                        outputRight = velCap;

                    if (abs(errorLeft) < tolerance && abs(errorRight) < tolerance)
                    {
                        isSettled = true;
                        targetLeft = targetRight = signLeft = signRight = outputLeft = outputRight = errorLeft = errorRight = 0;
                        state = 0;
                        set_left(0);
                        set_right(0);
                        reset_imu();
                        break;
                    }

                    set_left(outputLeft);
                    set_right(outputRight);
                    break;
                }
            case 0: //no movement
            {
                break;
            }
        }
        pros::delay(20);
    }
}

//score macro
void score(){
    set_cata(127);
    pros::delay(200);
    while (!cata_pressed())
    {
        pros::delay(10);
    }
    set_cata(-50);
    pros::delay(100);
    set_cata(20);
}

//----------------------------------------------------------------

//deploy
void preauton()
{
    // drive_hold();
    // intake_time(100,100);
}

//test
void test(){
	set_angle(100);
	while(!isSettled){
		pros::delay(20);
	} set_dist(2000);
}

//skill
void skill(){
    // preauton(); //first goal

    // set_intake(127); //second goal
    // forward_time(70,700);
    // convey_time(100,100);
    // turn_time(80,270);
    // forward_time(50,700);
    // convey_time(100,100);
    // forward_time(-50,700);
    // turn_time(80,270);
    // set_intake(0);
    // forward_time(50,750);
    // score(2);
    // forward_time(-100,1000);
    // turn_time(-80,370);

    // set_intake(127); //third goal
    // forward_time(50,600);
    // convey_time(100,100);
    // turn_time(80,270);
    // forward_time(50,400);
    // convey_time(100,100);
    // set_intake(0);
    // forward_time(50,200);
    // score(1);
    // turn_time(-80,645);

    // set_intake(127); //fourth goal
    // forward_time(70,1200);
    // convey_time(100,100);
    // turn_time(80,545);
    // forward_time(70,700);
    // convey_time(100,100);
    // forward_time(-70,700);
    // turn_time(-80,270);
    // set_intake(0);
    // forward_time(50,750);
    // score(2);
    // turn_time(-80,880);

    // set_intake(127); //fifth goal
    // forward_time(70,1200);
    // convey_time(100,100);
    // turn_time(80,780);
    // set_intake(0);
    // forward_time(50,700);
    // score(1);
    // turn_time(-80,645);
 
    // set_intake(127); //sixth goal
    // forward_time(70,700);
    // convey_time(100,100);
    // turn_time(-80,270);
    // forward_time(70,700);
    // convey_time(100,100);
    // forward_time(-70,500);
    // turn_time(80,270);
    // set_intake(0);
    // forward_time(50,700);
    // score(2);
    // forward_time(-100,1000);
    // turn_time(-80,370);

    // set_intake(127); //seventh goal
    // forward_time(70,600);
    // convey_time(100,100);
    // turn_time(80,270);
    // forward_time(70,400);
    // convey_time(100,100);
    // set_intake(0);
    // forward_time(50,200);
    // score(1);
    // turn_time(-80,645);

    // set_intake(127); //eighth goal
    // forward_time(70,1200);
    // convey_time(100,100);
    // turn_time(80,545);
    // forward_time(70,700);
    // convey_time(100,100);
    // forward_time(-70,700);
    // turn_time(-80,270);
    // set_intake(0);
    // forward_time(50,750);
    // score(2);
    // turn_time(-80,880);

    // set_intake(127); //ninth goal
    // forward_time(70,900);
    // convey_time(100,100);
    // turn_time(80,780);
    // set_intake(0);

    // //descore mid
    // double sign = 0;
    // for(int i = 0; i<5; i++){
    //     if(i%2==0){
    //         sign = -1;
    //     } else {
    //         sign = 1;
    //     }
    //     forward_time(50*sign,400);
    // }
    
    // //descore first goal
    // forward_time(50,700);
    // intake_time(100,100);

    // //score mid
    // forward_time(-70,300);
    // intake_time(-127,100);
    // turn_time(80,1050);
    // forward_time(50,1200);
    // convey_time(100,400);

}

//quals
void auton_1(){

}

//elim
void auton_2(){
    preauton();

    set_intake(100);
    set_dist(18);
    while(!isSettled){
        pros::delay(10);
    }
    set_angle(45);
    while (!isSettled){
        pros::delay(10);
    }
    set_dist(25.5);
    while(!isSettled){
        pros::delay(10);
    } 
    //descored corner goal

    set_intake(0);
    pros::delay(10);
    score(); //scored one ball
    
    set_dist(-25.5);
    while(!isSettled){
        pros::delay(10);
    }
    set_intake(-100);
    pros::delay(500); //tune so it only descore opponent ball

    set_angle(-90);
    while(!isSettled){
        pros::delay(10);
    }
    set_intake(100); 
    set_dist(25.5);
    while(!isSettled){
        pros::delay(10);
    }
    //descore center right goal

    set_intake(0);
    pros::delay(10);
    score(); //scored one ball

    //might need to intake to descore last opponent's ball
    set_dist(-10); //get away from goal
    while(!isSettled){
        pros::delay(10);
    }
}