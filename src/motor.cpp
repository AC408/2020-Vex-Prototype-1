#include "main.h"

//Motors
pros::Motor LB(11, MOTOR_GEARSET_18);
pros::Motor LF(12, MOTOR_GEARSET_18);
pros::Motor RF(19, MOTOR_GEARSET_18, true);
pros::Motor RB(18, MOTOR_GEARSET_18, true);
pros::Motor l_intake(14, MOTOR_GEARSET_6, true);
pros::Motor r_intake(15, MOTOR_GEARSET_6);
pros::Motor l_convey(13, MOTOR_GEARSET_18, true);
pros::Motor r_convey(17, MOTOR_GEARSET_18);

//Sensors
pros::ADIAnalogIn intake(1);
pros::ADIAnalogIn convey(2);

//Math
int sgn(int input)
{
    if (input > 0)
        return 1;
    else if (input < 0)
        return -1;
    return 0;
}

//Set Motors
void set_left_back(double input){
    LB.move(input);
}

void set_left_front(double input){
    LF.move(input);
}

void set_right_back(double input){
    RB.move(input);
}

void set_right_front(double input){
    RF.move(input);
}

void drive_hold()
{
    LB.set_brake_mode(MOTOR_BRAKE_HOLD);
    LF.set_brake_mode(MOTOR_BRAKE_HOLD);
    RF.set_brake_mode(MOTOR_BRAKE_HOLD);
    RB.set_brake_mode(MOTOR_BRAKE_HOLD);
}

void drive_coast()
{
    LB.set_brake_mode(MOTOR_BRAKE_COAST);
    LF.set_brake_mode(MOTOR_BRAKE_COAST);
    RF.set_brake_mode(MOTOR_BRAKE_COAST);
    RB.set_brake_mode(MOTOR_BRAKE_COAST);
}

void set_intake(int input)
{
    r_intake.move(input);
    l_intake.move(input);
}

void intake_hold()
{
    l_intake.set_brake_mode(MOTOR_BRAKE_HOLD);
    r_intake.set_brake_mode(MOTOR_BRAKE_HOLD);
}

void intake_coast()
{
    l_intake.set_brake_mode(MOTOR_BRAKE_COAST);
    r_intake.set_brake_mode(MOTOR_BRAKE_COAST);
}

//Sensors
void reset_drive_encoder()
{
   LB.set_zero_position(0);
   RB.set_zero_position(0);
}

void reset_intake_encoder()
{
    l_intake.set_zero_position(0);
    r_intake.set_zero_position(0);
}

int get_left_back_pos()
{
    return LB.get_position();
}

int get_right_back_pos()
{
    return RB.get_position();
}

int get_left_front_pos()
{
    return LF.get_position();
}

int get_right_front_pos()
{
    return RF.get_position();
}

int get_left_intake_pos()
{
    return l_intake.get_position();
}
int get_right_intake_pos()
{
    return r_intake.get_position();
}

double get_convey_line(){
    return convey.get_value();
}

double get_intake_line(){
    return intake.get_value();
}

void set_convey(double target){
    l_convey.move(target);
    r_convey.move(target);
}

double get_convey_pos(){
    return (l_convey.get_position()+r_convey.get_position())/2;
}

void reset_convey(){
    l_convey.set_zero_position(0);
    r_convey.set_zero_position(0);
}

void reset_all_encoders()
{
    reset_drive_encoder();
	reset_intake_encoder();
    reset_convey();
}

void calibrate(){
    intake.calibrate();
    convey.calibrate();
}
