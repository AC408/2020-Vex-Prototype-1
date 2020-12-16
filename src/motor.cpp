#include "main.h"

//Motors
pros::Motor LB(7, MOTOR_GEARSET_6),
        LF(1, MOTOR_GEARSET_6),
        RF(5, MOTOR_GEARSET_6, true),
        RB(4, MOTOR_GEARSET_6, true),
        LB2(9, MOTOR_GEARSET_6, true),
        RB2(8, MOTOR_GEARSET_6),
        Intake(3, MOTOR_GEARSET_18, true),
        Index(2, MOTOR_GEARSET_6, true);

pros::Imu imu(6);

//Math
int sgn(int input)
{
    if (input > 0)
        return 1;
    else if (input < 0)
        return -1;
    return 0;
}

//chassis
void set_left(double input){
    LB.move(input);
    LB2.move(input);
    LF.move(input);
}

void set_right(double input){
    RB.move(input);
    RB2.move(input);
    RF.move(input);
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
    LB.set_zero_position(0);
    RB.set_zero_position(0);
    RB2.set_zero_position(0);
    LB2.set_zero_position(0);
    RF.set_zero_position(0);
    LF.set_zero_position(0);
}

//imu
void calibrate(){
    imu.reset();
}

double get_angle(){
    return imu.get_heading();
}

//intake
void set_intake(int input)
{
    Intake.move(input);
}

void intake_hold()
{
    Intake.set_brake_mode(MOTOR_BRAKE_HOLD);
}

void intake_coast()
{
    Intake.set_brake_mode(MOTOR_BRAKE_COAST);
}

double get_intake_pos()
{
    return Intake.get_position();
}

void reset_intake(){
    Intake.set_zero_position(0);
}

//index
void set_index(double target){
    Index.move(target);
}

double get_index_pos(){
    return Index.get_position();
}

void reset_index(){
    Index.set_zero_position(0);
}

void index_coast(){
    Index.set_brake_mode(MOTOR_BRAKE_COAST);
}

void index_hold(){
    Index.set_brake_mode(MOTOR_BRAKE_HOLD);
}

//all
void reset_all_encoders()
{
    reset_drive_encoder();
	reset_intake();
    reset_index();
}

