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
void set_angle(double angle, double omega = 118, double alpha = 5, double theta_tol = 2, double theta_gain = 1.2){ //counter-clockwise is negative
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

void set_dist(double dist, double speed = 118, double accel = 5, double tol = 100, double gain = .15){ //100 dist is approx 1 inch
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
    pros::delay(200);
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
    pros::delay(600);
    set_intake_brake(MOTOR_BRAKE_HOLD);
    intake_state = STOP;
}

void test()
{
    intake_state = IN;

    //turn towards goal
    set_angle(-80 * -1, 40, 5, 1, 2.1);
    waitUntilSettled();

    //drive to goal
    set_dist(45, 118, 5, 120, .15);
    waitUntilSettled();

    //descore
    descore(3);

    //release one ball
    set_angle(STARTING_ANGLE - 30, 110, 15, 5, 2);
    waitUntilSettled();
    outtake();
    set_angle(-80 * -1);
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

void skill()
{
    intake_state = IN;

    //drive to middle goal
    set_dist(50);
    waitUntilSettled();

    //turn to face middle goal
    set_angle(-1 * (90 + STARTING_ANGLE));
    waitUntilSettled();

    //descore
    set_dist(13.5, 118, 10, 100, .3);
    pros::delay(1200);
    descore(1);
    set_dist(-10);
    waitUntilSettled();

    //turn to be parallel to wall
    set_angle(-1 * STARTING_ANGLE, 118, 5, 2, 1.2);
    waitUntilSettled();

    //drive to corner goal
    set_dist(46, 118, 5, 100, .15);
    waitUntilSettled();
    
    //turn to face corner goal
    set_angle(-1 * (45 + STARTING_ANGLE), 118, 7, 2, 1.4);
    waitUntilSettled();

    //drive into corner
    set_dist(12.5, 118, 10, 100, .3);
    pros::delay(1200);

    //descore
    descore(2);
    set_dist(-10);
    waitUntilSettled();

    //parallel to left wall
    set_angle(90 - STARTING_ANGLE, 118, 7, 2, 1.4);
    waitUntilSettled();

    //drive to left center
    set_dist(50);
    waitUntilSettled();

    //turn towards left center
    set_angle(-1 * STARTING_ANGLE, 118, 7, 2, 1.4);
    waitUntilSettled();

    //descore
    set_dist(13.5, 118, 10, 100, .3);
    pros::delay(1200);
    descore(1);
    set_dist(-10);
    waitUntilSettled();

    //turn to be parallel to wall
    set_angle(90 - STARTING_ANGLE, 118, 5, 2, 1.2);
    waitUntilSettled();

    //drive to corner goal
    set_dist(46, 118, 5, 100, .15);
    waitUntilSettled();
    
    //turn to face corner goal
    set_angle((45 - STARTING_ANGLE), 118, 7, 2, 1.4);
    waitUntilSettled();

    //drive into corner
    set_dist(12.5, 118, 10, 100, .3);
    pros::delay(1200);

    //descore
    descore(2);
    set_dist(-10);
    waitUntilSettled();

    //parallel to top wall
    set_angle(180 - STARTING_ANGLE, 118, 7, 2, 1.4);
    waitUntilSettled();

    //drive to top center
    set_dist(50);
    waitUntilSettled();

    //turn towards left center
    set_angle(90 - STARTING_ANGLE, 118, 7, 2, 1.4);
    waitUntilSettled();

    //descore
    set_dist(13.5, 118, 10, 100, .3);
    pros::delay(1200);
    descore(1);
    set_dist(-10);
    waitUntilSettled();

    //turn to be parallel to wall
    set_angle(180 - STARTING_ANGLE, 118, 5, 2, 1.2);
    waitUntilSettled();

    //drive to corner goal
    set_dist(46, 118, 5, 100, .15);
    waitUntilSettled();
    
    //turn to face corner goal
    set_angle((135 - STARTING_ANGLE), 118, 7, 2, 1.4);
    waitUntilSettled();

    //drive into corner
    set_dist(12.5, 118, 10, 100, .3);
    pros::delay(1200);

    //descore
    descore(2);
    set_dist(-10);
    waitUntilSettled();

    //parallel to right wall
    set_angle(270 - STARTING_ANGLE, 118, 7, 2, 1.4);
    waitUntilSettled();

    //drive to right center
    set_dist(50);
    waitUntilSettled();

    //turn towards left center
    set_angle(180 - STARTING_ANGLE, 118, 7, 2, 1.4);
    waitUntilSettled();

    //descore
    set_dist(13.5, 118, 10, 100, .3);
    pros::delay(1200);
    descore(1);
    set_dist(-10);
    waitUntilSettled();

    //facing center center with a slant
    set_angle(STARTING_ANGLE, 118, 7, 2, 1.4);
    waitUntilSettled();

    //drive to center center
    set_dist(38);
    waitUntilSettled();
    set_tank(70,70); //already poked out one ball, using volt bc dont know how long the dist is
    pros::delay(1000);
    set_tank(0,0);
    pros::delay(100);

    //descore
    descore(2);
    set_dist(-10);
    waitUntilSettled();

    //turn to face front-mid ball
    set_angle(-1 * (45 + STARTING_ANGLE), 118, 7, 2, 1.4);
    waitUntilSettled();

    //get front-mid ball
    set_dist(34);
    waitUntilSettled();

    //turn towards front-mid goal
    set_angle(-1 * (90 + STARTING_ANGLE), 118, 7, 2, 1.4);
    waitUntilSettled();

    //score
    set_dist(36);
    waitUntilSettled();
    set_tank(70,70);
    pros::delay(1000);
    set_tank(0,0);
    pros::delay(100);
    outtake();
    set_dist(-36);
    waitUntilSettled();

    //turn towards left-mid ball
    set_angle((45 - STARTING_ANGLE), 118, 7, 2, 1.4);
    waitUntilSettled();

    //get ball
    set_dist(34);
    waitUntilSettled();

    //turn towards left-mid goal
    set_angle(-1 * STARTING_ANGLE, 118, 7, 2, 1.4);
    waitUntilSettled();

    //score
    set_dist(36);
    waitUntilSettled();
    set_tank(70,70);
    pros::delay(1000);
    set_tank(0,0);
    pros::delay(100);
    outtake();
    set_dist(-36);
    waitUntilSettled();

    //turn towards back-mid ball
    set_angle((135 - STARTING_ANGLE), 118, 7, 2, 1.4);
    waitUntilSettled();

    //get ball
    set_dist(34);
    waitUntilSettled();

    //turn towards back-mid goal
    set_angle(90 - STARTING_ANGLE, 118, 7, 2, 1.4);
    waitUntilSettled();

    //score
    set_dist(36);
    waitUntilSettled();
    set_tank(70,70);
    pros::delay(1000);
    set_tank(0,0);
    pros::delay(100);
    outtake();
    set_dist(-36);
    waitUntilSettled();

    //turn towards right-mid ball
    set_angle((225 - STARTING_ANGLE), 118, 7, 2, 1.4);
    waitUntilSettled();

    //get ball
    set_dist(34);
    waitUntilSettled();

    //turn towards right-mid goal
    set_angle(180 - STARTING_ANGLE, 118, 7, 2, 1.4);
    waitUntilSettled();

    //score
    set_dist(36);
    waitUntilSettled();
    set_tank(70,70);
    pros::delay(1000);
    set_tank(0,0);
    pros::delay(100);
    outtake();
    set_dist(-36);
    waitUntilSettled();

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
    set_dist(13.5, 118, 10, 100, .3);
    pros::delay(600);
    descore(2);

    //let go of one ball
    set_angle(side * (130 + STARTING_ANGLE), 118, 16, 8, 2.1);
    waitUntilSettled();
    outtake();
    set_angle(side * (90 + STARTING_ANGLE), 118, 20, 8, 2.4);
    pros::delay(200);
    intake_state = IN;
    waitUntilSettled();

    //score a ball into the goal
    set_dist(7);
    waitUntilSettled();
    intake_state = OUT;
    pros::delay(600);
    set_dist(-10);
    waitUntilSettled();
    set_dist(-10);
    waitUntilSettled();
    set_intake_brake(MOTOR_BRAKE_COAST);
    intake_state = IN;

    //turn to be parallel to wall
    set_angle(side * STARTING_ANGLE, 118, 5, 2, 1.2);
    waitUntilSettled();
   
    //drive to corner goal
    set_dist(46, 118, 5, 100, .15);
    waitUntilSettled();
    
    //turn to face corner goal
    set_angle(side * (45 + STARTING_ANGLE), 118, 7, 2, 1.4);
    waitUntilSettled();

    //drive into corner
    set_dist(23, 118, 10, 100, .3);
    pros::delay(600);

    //descore
    descore(2);

    //let go of one ball
    set_angle(side * (120 + STARTING_ANGLE), 118, 11, 5, 2.1);
    waitUntilSettled();
    outtake();
    set_angle(side * (45 + STARTING_ANGLE));
    pros::delay(200);
    intake_state = IN;
    waitUntilSettled();

    //score a ball into the goal
    intake_state = IN;
    set_dist(7);
    waitUntilSettled();
    intake_state = OUT;
    pros::delay(600);

    //back away from goal
    set_dist(-13);
    waitUntilSettled();
}

void center_row(int side)
{
    intake_state = IN;

    //turn towards goal
    set_angle(-79 * side, 40, 5, 1, 2.1);
    waitUntilSettled();

    //drive to goal
    set_dist(44.5, 118, 5, 120, .15);
    waitUntilSettled();

    //descore
    descore(3);

    //release one ball
    set_angle(STARTING_ANGLE - 30, 110, 15, 5, 2);
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
    set_dist(-12.5);
    waitUntilSettled();    
    
    // //turn to center
    // set_angle(12, 110, 15, 1, 2);
    // waitUntilSettled();
    // set_dist(34);
    // waitUntilSettled();
    // set_tank(80,80);
    // pros::delay(500);
    // set_tank(0,0);
}