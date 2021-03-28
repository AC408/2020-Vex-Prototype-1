#include "main.h"

//Motors
//Ded ports - 1, 5, 10
pros::Motor LBd(1, MOTOR_GEARSET_6, true),
            LBu(2, MOTOR_GEARSET_6),
            LF(7, MOTOR_GEARSET_6, true),
            
            RBd(11, MOTOR_GEARSET_6),
            RBu(12, MOTOR_GEARSET_6, true),
            RF(17, MOTOR_GEARSET_6),

            LIntake(8, MOTOR_GEARSET_6, true),
            RIntake(18, MOTOR_GEARSET_6);

pros::Imu imu(3);

//Math
int sgn(int input)
{
    if (input > 0)
        return 1;
    else if (input < 0)
        return -1;
    return 0;
}

//drive -----------------------------------------------------------------------
void set_tank(double l, double r)
{
    LBd.move(l);
    LF.move(l);
    LBu.move(l);
    RF.move(r);
    RBd.move(r);
    RBu.move(r);
}

void set_drive_brake(pros::motor_brake_mode_e brake)
{
    LBd.set_brake_mode(brake);
    LF.set_brake_mode(brake);
    RF.set_brake_mode(brake);
    RBd.set_brake_mode(brake);
    RBu.set_brake_mode(brake);
    LBu.set_brake_mode(brake);
}

double get_left_pos()
{
    return (LBd.get_position() + LF.get_position() + LBu.get_position()) / 3;
}

double get_right_pos()
{
    return (RBd.get_position() + RF.get_position() + RBu.get_position()) / 3;
}

void reset_drive_encoder()
{
    LBd.tare_position();
    RBd.tare_position();
    RBu.tare_position();
    LBu.tare_position();
    RF.tare_position();
    LF.tare_position();
}

//imu -----------------------------------------------------------------------
void calibrate()
{
    imu.reset();
}

void reset_imu()
{
    imu.set_rotation(0);
}

double get_angle()
{
    return imu.get_rotation();
}

//intakes -----------------------------------------------------------------------
void set_intake(int input)
{
    LIntake.move(input);
    RIntake.move(input);
}

void set_intake_brake(pros::motor_brake_mode_e brake)
{
    LIntake.set_brake_mode(brake);
    RIntake.set_brake_mode(brake);
}

double get_intake_pos()
{
    return (LIntake.get_position() + RIntake.get_position()) / 2;
}

void reset_intake()
{
    LIntake.set_zero_position(0);
    RIntake.set_zero_position(0);
}

//all -----------------------------------------------------------------------
void reset_all_encoders()
{
    reset_drive_encoder();
	reset_intake();
}

//temperature -----------------------------------------------------------------------
double get_lintake_temp(){
    return LIntake.get_temperature();
}

double get_rintake_temp(){
    return RIntake.get_temperature();
}

double get_rbu_temp(){
    return RBu.get_temperature();
}

double get_rbd_temp(){
    return RBd.get_temperature();
}

double get_rf_temp(){
    return RF.get_temperature();
}

double get_lbd_temp(){
    return LBd.get_temperature();
}

double get_lbu_temp(){
    return LBu.get_temperature();
}

double get_lf_temp(){
    return LF.get_temperature();
}

