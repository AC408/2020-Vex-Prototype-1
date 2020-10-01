#include "main.h"

//Motors
pros::Motor lb_drive(11, MOTOR_GEARSET_18, true);
pros::Motor lf_drive(12, MOTOR_GEARSET_18, true);
pros::Motor rf_drive(9, MOTOR_GEARSET_18);
pros::Motor rb_drive(10, MOTOR_GEARSET_18);
pros::Motor l_intake(19, MOTOR_GEARSET_18);
pros::Motor r_intake(17, MOTOR_GEARSET_18, true);
pros::Motor tray(8, MOTOR_GEARSET_18);
pros::Motor arm(15, MOTOR_GEARSET_18, true);

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
void set_tank(double input_l, double input_r){
    lb_drive.move(input_l);
    lf_drive.move(input_l);
    rf_drive.move(input_r);
    rb_drive.move(input_r);
}

void drive_hold()
{
    lb_drive.set_brake_mode(MOTOR_BRAKE_HOLD);
    lf_drive.set_brake_mode(MOTOR_BRAKE_HOLD);
    rf_drive.set_brake_mode(MOTOR_BRAKE_HOLD);
    rb_drive.set_brake_mode(MOTOR_BRAKE_HOLD);
}

void drive_coast()
{
    lb_drive.set_brake_mode(MOTOR_BRAKE_COAST);
    lf_drive.set_brake_mode(MOTOR_BRAKE_COAST);
    rf_drive.set_brake_mode(MOTOR_BRAKE_COAST);
    rb_drive.set_brake_mode(MOTOR_BRAKE_COAST);
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
   lb_drive.set_zero_position(0);
   rb_drive.set_zero_position(0);
}

void reset_intake_encoder()
{
    l_intake.set_zero_position(0);
    r_intake.set_zero_position(0);
}

int get_left_drive_pos()
{
    return lb_drive.get_position();
}

int get_right_drive_pos()
{
    return rb_drive.get_position();
}

int get_left_drive_spe()
{
    return lb_drive.get_actual_velocity() / 200 * 127;
}

int get_right_drive_spe()
{
    return rb_drive.get_actual_velocity() / 200 * 127;
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
    lb_drive.move_relative(ang*5, vel);
    lf_drive.move_relative(ang*5, vel);
    rb_drive.move_relative(-ang*5, vel);
    rf_drive.move_relative(-ang*5, vel);
}

void swingTurn(float lAng, float rAng, float lVel, float rVel){
    lb_drive.move_relative(lAng*5, lVel);
    lf_drive.move_relative(lAng*5, lVel);
    rb_drive.move_relative(rAng*5, rVel);
    rf_drive.move_relative(rAng*5, rVel);
}

void reset_all_encoders()
{
    reset_drive_encoder();
	reset_tray_encoder();
	reset_arm_encoder();
	reset_intake_encoder();
}
