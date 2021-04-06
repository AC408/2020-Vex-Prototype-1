#ifndef SUBSYSTEMS_HPP
#define SUBSYSTEMS_HPP

#define IN 1
#define OUT 2
#define STOP 0
#define SLOW_OUT 3
#define CURVE_SCALE 2.2
#define TEMP 1
#define SENSOR 2

void drive_control(void *);
void intake_control(void *);
void sensors(void *);
void drive_control(void *);

extern int intake_state;
extern pros::Controller master;
extern int sensor_state;
#endif