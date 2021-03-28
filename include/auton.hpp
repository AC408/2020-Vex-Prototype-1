#ifndef AUTON_HPP
#define AUTON_HPP

#define LEFT 1
#define RIGHT -1
#define STARTING_ANGLE 18

void chassis_control(void *);

void deploy();
void home_row(int side);
void center_row(int side);

void skill();
void test();

#endif