#ifndef MOTOR_HPP
#define MOTOR_HPP

#include "okapi/api.hpp"
using namespace okapi;

int sgn(int input);

void set_tank(double l, double r);
void set_drive_brake(pros::motor_brake_mode_e brake);
void reset_drive_encoder();
double get_left_pos();
double get_right_pos();

void calibrate();
double get_angle();
void reset_imu();

void set_intake(int input);
void set_intake_brake(pros::motor_brake_mode_e brake);
double get_intake_pos();
void reset_intake();

void reset_all_encoders();

#endif