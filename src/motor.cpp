#include "main.h"

//Motors
//Ded ports - 1, 5, 10
pros::Motor LB(1, MOTOR_GEARSET_6, true),
        LF(7, MOTOR_GEARSET_6, true),
        RF(17, MOTOR_GEARSET_6),
        RB(11, MOTOR_GEARSET_6),
        LB2(2, MOTOR_GEARSET_6),
        RB2(12, MOTOR_GEARSET_6, true),
        Intake(8, MOTOR_GEARSET_6, true),
        Intake2(18, MOTOR_GEARSET_6);

pros::Imu imu(1);

//Math
int sgn(int input)
{
    if (input > 0)
        return 1;
    else if (input < 0)
        return -1;
    return 0;
}

void set_tank(double l, double r){
    LB.move(l);
    LF.move(l);
    LB2.move(l);
    RF.move(r);
    RB.move(r);
    RB2.move(r);
}

void drive_hold()
{
    LB.set_brake_mode(MOTOR_BRAKE_HOLD);
    LF.set_brake_mode(MOTOR_BRAKE_HOLD);
    RF.set_brake_mode(MOTOR_BRAKE_HOLD);
    RB.set_brake_mode(MOTOR_BRAKE_HOLD);
    RB2.set_brake_mode(MOTOR_BRAKE_HOLD);
    LB2.set_brake_mode(MOTOR_BRAKE_HOLD);
}

void drive_coast()
{
    LB.set_brake_mode(MOTOR_BRAKE_COAST);
    LF.set_brake_mode(MOTOR_BRAKE_COAST);
    RF.set_brake_mode(MOTOR_BRAKE_COAST);
    RB.set_brake_mode(MOTOR_BRAKE_COAST);
    RB2.set_brake_mode(MOTOR_BRAKE_COAST);
    LB2.set_brake_mode(MOTOR_BRAKE_COAST);
}

double get_left_pos()
{
    return (LB.get_position()+LF.get_position()+LB2.get_position())/3;
}

double get_right_pos()
{
    return (RB.get_position()+RF.get_position()+RB2.get_position())/3;
}

void reset_drive_encoder()
{
    LB.tare_position();
    RB.tare_position();
    RB2.tare_position();
    LB2.tare_position();
    RF.tare_position();
    LF.tare_position();
}

//imu
void calibrate(){
    imu.reset();
}

void reset_imu(){
    imu.tare();
}

double get_angle(){
    return imu.get_heading();
}

//intake
void set_intake(int input)
{
    Intake.move(input);
    Intake2.move(input);
}

void intake_hold()
{
    Intake.set_brake_mode(MOTOR_BRAKE_HOLD);
    Intake2.set_brake_mode(MOTOR_BRAKE_HOLD);
}

void intake_coast()
{
    Intake.set_brake_mode(MOTOR_BRAKE_COAST);
    Intake2.set_brake_mode(MOTOR_BRAKE_COAST);
}

double get_intake_pos()
{
    return (Intake.get_position()+Intake2.get_position())/2;
}

void reset_intake(){
    Intake.set_zero_position(0);
    Intake2.set_zero_position(0);
}

//all
void reset_all_encoders()
{
    reset_drive_encoder();
	reset_intake();
}