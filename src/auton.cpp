#include "main.h"

//states
int state = 0;

//global params
double targetTheta = 0,
        targetLeft = 0,
        targetRight = 0,
        
        velCap = 0,
        accelLimit = 0,
        speedLimit = 0,
        tolerance = 0,

        omegaCap = 0,
        alphaLimit = 0,
        omegaLimit = 0,
        theta_tolerance = 0,
        last_desired = 0;

bool isSettled = false;

//gains
double kP_turn = 0,
        kP = 0,
        kP_heading = 1.1;

//drive function
void set_angle(double angle, double omega = 100, double alpha = 5, double theta_tol = 2, double theta_gain = 1.1){ //counter-clockwise is negative
//    reset_imu();
    targetTheta = angle;
    omegaLimit = omega;
    alphaLimit = alpha;
    kP_turn = theta_gain;
    theta_tolerance = theta_tol;
    isSettled = false;
    state = 1;
    last_desired += targetTheta;
}

void set_dist(double dist, double speed = 100, double accel = 5, double tol = 100, double gain = .1){ //100 dist is approx 1 inch
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
void chassis_control(void *)
{

    set_drive_brake(MOTOR_BRAKE_HOLD);

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
            case 1: //absolute angle
                {
                    errorTheta = targetTheta - get_angle();

                    signTheta = errorTheta / abs(errorTheta);

                    outputTheta = errorTheta * kP_turn;

                    omegaCap += alphaLimit;

                    if (omegaCap > omegaLimit)
                        omegaCap = omegaLimit;

                    if (abs(outputTheta) > omegaCap)
                        outputTheta = omegaCap * signTheta;

                    if (abs(errorTheta) < theta_tolerance)
                    {
                        isSettled = true;
                        targetTheta = signTheta = outputTheta = errorTheta = 0;
                        state = 0;
                        set_tank(0, 0);
                        break;
                    }
                    pros::lcd::set_text(5, "left"+std::to_string(outputTheta));
                    pros::lcd::set_text(6, "right"+std::to_string(-outputTheta));
                    set_tank(outputTheta, -outputTheta);    
                    break;

                }
            case 2: //drive
                {
                    errorLeft = targetLeft - get_left_pos();
                    errorRight = targetRight - get_right_pos();

                    signLeft = errorLeft / abs(errorLeft);
                    signRight = errorRight / abs(errorRight);

                    double heading_output = (last_desired - get_angle()) * kP_heading;

                    outputLeft = (errorLeft * kP) + ((errorLeft * kP)/ 90 * heading_output);
                    outputRight = (errorRight * kP) - ((errorRight * kP)/ 90 * heading_output);

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
                        set_tank(0,0);
                        reset_imu();
                        break;
                    }
                    pros::lcd::set_text(5, "left"+std::to_string(outputLeft));
                    pros::lcd::set_text(6, "right"+std::to_string(outputRight));
                    set_tank(outputLeft, outputRight);    
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
}

//im lazy
void waitUntilSettled()
{
    while(!isSettled){
		pros::delay(20); 
	} pros::delay(100);
}

//test
void test()
{
    set_dist(3000);
    waitUntilSettled();
    set_angle(-90);
    waitUntilSettled();
    set_dist(1000);
    waitUntilSettled();
    set_angle(-180);
    waitUntilSettled();
    set_dist(1000);
    waitUntilSettled();
    set_angle(-270);
    waitUntilSettled();
    set_dist(1000);
    waitUntilSettled();
    set_angle(-180);
    waitUntilSettled();
    set_dist(2000);
    waitUntilSettled();

    intake_state = IN;
}

//skill
void skill()
{

}

void home_row(int side)
{
    intake_state = IN;
    set_dist(24);
    while(!isSettled){
        pros::delay(20);
    } set_angle(side * 90);
    while(!isSettled){
        pros::delay(20);
    } set_dist(48);
    while(!isSettled){
        pros::delay(20);
    } set_angle(90); //turn towards center goal
    while(!isSettled){
        pros::delay(20);
    } set_dist(5);
    while(!isSettled){
        pros::delay(20);
    } pros::delay(200); //wait for center goal to descore
    set_dist(-5);
    while(!isSettled){
        pros::delay(20);
    } set_angle(10);
    while(!isSettled){
        pros::delay(20);
    } set_intake(-100); //descore one ball
    pros::delay(100);
    set_intake(0);
    set_angle(-10);
    while(!isSettled){
        pros::delay(20);
    } set_intake(-127); //descore to score one ball
    pros::delay(100);
    set_intake(0);
    set_angle(-90);
    while(!isSettled){
        pros::delay(20);
    } set_dist(48);
    while(!isSettled){
        pros::delay(20);
    } set_angle(45);
    while(!isSettled){
        pros::delay(20);
    } set_intake(127);
    set_tank(50,50); //descore goal
    pros::delay(500);
    set_tank(-50,-50);
    pros::delay(200);
    set_tank(-50,50);
    pros::delay(200);
    set_intake(-127);
    pros::delay(100);
    set_intake(0);
    set_tank(50,-50);
    pros::delay(200);
    set_tank(50,50);
    pros::delay(200);
    set_intake(-127);
    pros::delay(100);
    set_tank(-70,-70);
    set_intake(0);
    pros::delay(200);
    set_tank(0,0);
}

void center()
{
    set_intake(100);
    set_dist(48); //drive to center
    while(!isSettled){ //wait until settled
        pros::delay(20);
    } set_angle(90); //turn towards center goal
    while(!isSettled){
        pros::delay(20); 
    } set_dist(24); //drive to center goal
    while(!isSettled){
        pros::delay(20);
    } set_intake(-100); //score
    pros::delay(500);
    set_intake(0);
    set_dist(-24); //back away
    while(!isSettled){
        pros::delay(20);
    }
}

//no poking for descore
//back and forth motion for descore
//preauton or cata to score preload 

//where is starting location for cata to shoot?
