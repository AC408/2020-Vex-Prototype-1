#ifndef SUBSYSTEMS_HPP
#define SUBSYSTEMS_HPP

void intake_control(void *);
void sensors(void *);
void drive_control(void *);

extern int intake_state;
extern pros::Controller master;

#endif