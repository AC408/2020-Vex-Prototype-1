#ifndef MOTOR_HPP
#define MOTOR_HPP

#include "okapi/api.hpp"
using namespace okapi;

int sgn(int input);

//drive
void set_tank(double l, double r);
void set_drive_brake(pros::motor_brake_mode_e brake);
void reset_drive_encoder();
double get_left_pos();
double get_right_pos();

//imu
void calibrate();
double get_angle();
void reset_imu();

//intakes
void set_intake(int input);
void set_intake_brake(pros::motor_brake_mode_e brake);
double get_intake_pos();
void reset_intake();

//all
void reset_all_encoders();

//get_temp
double get_lintake_temp();
double get_rintake_temp();
double get_rbu_temp();
double get_rbd_temp();
double get_rf_temp();
double get_lbu_temp();
double get_lbd_temp();
double get_lf_temp();

#endif