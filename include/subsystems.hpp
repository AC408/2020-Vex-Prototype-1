#ifndef SUBSYSTEMS_HPP
#define SUBSYSTEMS_HPP

void drive_control(void *);
void intake_control(void *);
void sensors(void *);
void drive_control(void *);

extern int intake_state;
extern pros::Controller master;

#endif