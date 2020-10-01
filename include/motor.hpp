#ifndef MOTOR_HPP
#define MOTOR_HPP

#include "okapi/api.hpp"
using namespace okapi;

extern std::shared_ptr<ChassisController> chassisController;
extern std::shared_ptr<AsyncMotionProfileController> profileController;


extern int selector;

int sgn(int input);
int clipnum(int input, int clip);

void set_left_back(double input);
void set_left_front(double input);
void set_right_back(double input);
void set_right_front(double input);
void set_tank(double input_l, double input_r);
void drive_hold();
void drive_coast();
void set_intake(int input);
void intake_relative(int pos, int vel);
void set_intake_speed(int32_t input);
void intake_hold();
void intake_coast();
void reset_drive_encoder();
void reset_intake_encoder();
void reset_tray_encoder();
void reset_arm_encoder();
int get_left_drive_pos();
int get_right_drive_pos();
int get_left_drive_spe();
int get_right_drive_spe();
int get_left_intake_pos();
int get_right_intake_pos();

void sensors(void *);

void reset_all_encoders();

void turnAng(float ang, float vel);


#endif