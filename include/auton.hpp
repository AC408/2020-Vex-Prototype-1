#ifndef AUTON_HPP
#define AUTON_HPP

void drive_control(void *);
void forward(void *);
void turn(void *);

void p_turn(int angle);

#endif