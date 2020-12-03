#ifndef MOTOR_HPP
#define MOTOR_HPP

#include "okapi/api.hpp"
using namespace okapi;

int sgn(int input);

void set_left(double input);
void set_right(double input);
void drive_hold();
void drive_coast();
void reset_drive_encoder();
double get_left_pos();
double get_right_pos();

void calibrate();
void get_angle();
void reset_imu();

void set_intake(int input);
void intake_hold();
void intake_coast();
double get_intake_pos();
void reset_intake();

double get_index_pos();
void set_index(double target);
void reset_index();
void index_coast();
void index_hold();

void reset_all_encoders();

#endif