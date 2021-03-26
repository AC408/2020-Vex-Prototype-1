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
        last_desired = 0,
        in_to_encoder = 50;

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
    last_desired = targetTheta;
}

void set_dist(double dist, double speed = 110, double accel = 5, double tol = 100, double gain = .15){ //100 dist is approx 1 inch
    reset_drive_encoder();
    targetLeft = targetRight = dist * in_to_encoder;
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

void deploy()
{
    intake_state = OUT;
    pros::delay(450);
//    pros::delay(600);
}

void waitUntilSettled()
{
    while(!isSettled){
		pros::delay(20); 
	} pros::delay(50);
}

void descore(int balls)
{
    for (int i = 0; i < balls; i++)
    {
        set_dist(8, 110, 10, 100, .3);
        waitUntilSettled();
        set_dist(-8);
        waitUntilSettled();
    }
}

void outtake()
{
    intake_state = SLOW_OUT;
    pros::delay(100);
    set_intake_brake(MOTOR_BRAKE_HOLD);
    intake_state = STOP;
}

void test()
{
    set_dist(30);
    waitUntilSettled();
    set_angle(-90);
    waitUntilSettled();
    set_dist(10);
    waitUntilSettled();
    set_angle(-180);
    waitUntilSettled();
    set_dist(10);
    waitUntilSettled();
    set_angle(-270);
    waitUntilSettled();
    set_dist(10);
    waitUntilSettled();
    set_angle(-180);
    waitUntilSettled();
    set_dist(20);
    waitUntilSettled();

    intake_state = IN;
}

void skill()
{
}

void home_row(int side)
{
    intake_state = IN;

    //drive to middle goal
    set_dist(50);
    waitUntilSettled();

    //turn to face middle goal
    set_angle(side * (90 + STARTING_ANGLE));
    waitUntilSettled();

    //descore
    set_dist(13.5, 110, 10, 100, .3);
    waitUntilSettled();
    descore(2);

    //let go of one ball
    set_angle(side * (130 + STARTING_ANGLE), 110, 15, 5, 2);
    waitUntilSettled();
    outtake();
    set_angle(side * (90 + STARTING_ANGLE));
    waitUntilSettled();

    //score a ball into the goal
    intake_state = IN;
    set_dist(7);
    waitUntilSettled();
    intake_state = OUT;
    pros::delay(600);
    set_dist(-10);
    waitUntilSettled();
    set_intake_brake(MOTOR_BRAKE_COAST);
    intake_state = IN;

    //revised code
    //turn to face corner goal
    set_dist(-24);
    waitUntilSettled();
    set_angle(side * (30+STARTING_ANGLE), 100, 5, 2, 1.1);
    waitUntilSettled();

    //drive to corner goal
    set_dist(55,110,5,100,.15);
    waitUntilSettled();

    //descore
    descore(2);

    //let go of one ball
    set_angle(side * (180 + STARTING_ANGLE)/*, 110, 11, 5, 2*/);
    waitUntilSettled();
    outtake();
    set_angle(side * (45 + STARTING_ANGLE));
    waitUntilSettled();

/*
    //turn to be parallel to wall
    set_angle(side * STARTING_ANGLE, 100, 5, 2, 1.1);
    waitUntilSettled();

    //drive to corner goal
    set_dist(43, 110, 5, 100, .15);
    waitUntilSettled();
    
    //turn to face corner goal
    set_angle(side * (45 + STARTING_ANGLE), 100, 7, 2, 1.4);
    waitUntilSettled();

    //drive into corner
    set_dist(15, 110, 10, 100, .3);
    waitUntilSettled();

    //descore
    descore(2);
*/
    // //let go of one ball
    // set_angle(side * (120 + STARTING_ANGLE)/*, 110, 11, 5, 2*/);
    // waitUntilSettled();
    // outtake();
    // set_angle(side * (45 + STARTING_ANGLE));
    // waitUntilSettled();

    //score a ball into the goal
    intake_state = IN;
    set_dist(7);
    waitUntilSettled();
    intake_state = OUT;
    pros::delay(600);
    set_dist(-10);
    waitUntilSettled();
    set_intake_brake(MOTOR_BRAKE_COAST);
    intake_state = IN;

    //back away from goal
    set_dist(-8);
    waitUntilSettled();
}

void center_row(int side)
{
    intake_state = IN;

    //turn towards goal
    set_angle(-80 * side);
    waitUntilSettled();

    //drive to goal
    set_dist(44);
    waitUntilSettled();

    //descore
    descore(3);

    //release one ball
    set_angle(STARTING_ANGLE, 110, 15, 5, 2);
    waitUntilSettled();
    outtake();
    set_angle(-80 * side);
    waitUntilSettled();

    //score
    intake_state = IN;
    set_dist(7);
    waitUntilSettled();
    intake_state = OUT;
    pros::delay(600);
    set_dist(-10);
    waitUntilSettled();    
}