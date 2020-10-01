#ifndef MOTOR_HPP
#define MOTOR_HPP

#include "okapi/api.hpp"
using namespace okapi;

int sgn(int input);

void set_left_back(double input);
void set_left_front(double input);
void set_right_back(double input);
void set_right_front(double input);
void drive_hold();
void drive_coast();
void set_intake(int input);
void intake_hold();
void intake_coast();
void reset_drive_encoder();
int get_left_back_pos();
int get_right_front_pos();
int get_left_front_spe();
int get_right_back_spe();
int get_intake_pos();

void reset_all_encoders();

void turnAng(float ang, float vel);


#endif