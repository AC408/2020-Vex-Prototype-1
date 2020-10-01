#ifndef SUBSYSTEMS_HPP
#define SUBSYSTEMS_HPP

void drive_control(void *);
void intake_control(void *);
void conveyor_control(void *);

extern int ball;
extern int intake_state;

#endif