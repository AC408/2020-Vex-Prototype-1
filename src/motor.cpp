#include "main.h"

//Motors
pros::Motor LB(11, MOTOR_GEARSET_18);
pros::Motor LF(12, MOTOR_GEARSET_18);
pros::Motor RF(19, MOTOR_GEARSET_18, true);
pros::Motor RB(18, MOTOR_GEARSET_18, true);
pros::Motor LB2(10, MOTOR_GEARSET_18, true);
pros::Motor RB2(9, MOTOR_GEARSET_18);
pros::Motor Intake(14, MOTOR_GEARSET_6, true);
pros::Motor Convey(13, MOTOR_GEARSET_18, true);

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

//Sensors
void reset_drive_encoder()
{
    LB.set_zero_position(0);
    RB.set_zero_position(0);
    RB2.set_zero_position(0);
    LB2.set_zero_position(0);
    RF.set_zero_position(0);
    LF.set_zero_position(0);
}

void reset_intake_encoder()
{
    Intake.set_zero_position(0);
}

int get_left_pos()
{
    return (LB.get_position()+LF.get_position()+LB2.get_position())/3;
}

int get_right_pos()
{
    return (RB.get_position()+RF.get_position()+RB2.get_position())/3;
}

int get_intake_pos()
{
    return Intake.get_position();
}

double get_convey_line(){
    return convey.get_value();
}

double get_intake_line(){
    return intake.get_value();
}

void set_convey(double target){
    Convey.move(target);
}

double get_convey_pos(){
    return Convey.get_position();
}

void reset_convey(){
    Convey.set_zero_position(0);
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
