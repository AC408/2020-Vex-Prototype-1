#include "main.h"

//Motors
pros::Motor LB(11, MOTOR_GEARSET_18, true);
pros::Motor LF(12, MOTOR_GEARSET_18, true);
pros::Motor RF(9, MOTOR_GEARSET_18);
pros::Motor RB(10, MOTOR_GEARSET_18);
pros::Motor l_intake(19, MOTOR_GEARSET_18);
pros::Motor r_intake(17, MOTOR_GEARSET_18, true);
pros::Motor l_convey(8, MOTOR_GEARSET_18);
pros::Motor r_convey(15, MOTOR_GEARSET_18, true);

//Sensors
pros::ADIPotentiometer tray_pot(1);
pros::ADIPotentiometer auton_selector(2);

//Math
int sgn(int input)
{
    if (input > 0)
        return 1;
    else if (input < 0)
        return -1;
    return 0;
}

int clipnum(int input, int clip)
{
    if (input > clip)
        return clip;
    else if (input < clip)
        return -clip;
    return input;
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

void set_tank(double input_l, double input_r){
    LB.move(input_l);
    LF.move(input_l);
    RF.move(input_r);
    RB.move(input_r);
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

void intake_relative(int pos, int vel)
{
    l_intake.move_relative(pos, vel);
    r_intake.move_relative(pos, vel);
}

void set_intake_speed(int32_t input)
{
    l_intake.set_voltage_limit(input);
    r_intake.set_voltage_limit(input);
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

int get_left_drive_pos()
{
    return LB.get_position();
}

int get_right_drive_pos()
{
    return RB.get_position();
}

int get_left_drive_spe()
{
    return LB.get_actual_velocity() / 200 * 127;
}

int get_right_drive_spe()
{
    return RB.get_actual_velocity() / 200 * 127;
}

int get_left_intake_pos()
{
    return l_intake.get_position();
}
int get_right_intake_pos()
{
    return r_intake.get_position();
}

void sensors(void* param){
    while(true){
        std::cout << "left:  "<<chassisController->getModel()->getSensorVals()[0] << std::endl;
        std::cout << "right: "<<chassisController->getModel()->getSensorVals()[1] << std::endl;

        pros::delay(10);
    }
}

void turnAng(float ang, float vel){
    LB.move_relative(ang*5, vel);
    LF.move_relative(ang*5, vel);
    RB.move_relative(-ang*5, vel);
    RF.move_relative(-ang*5, vel);
}

void swingTurn(float lAng, float rAng, float lVel, float rVel){
    LB.move_relative(lAng*5, lVel);
    LF.move_relative(lAng*5, lVel);
    RB.move_relative(rAng*5, rVel);
    RF.move_relative(rAng*5, rVel);
}

void reset_all_encoders()
{
    reset_drive_encoder();
	reset_tray_encoder();
	reset_arm_encoder();
	reset_intake_encoder();
}
