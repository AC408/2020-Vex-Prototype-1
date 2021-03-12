#ifndef SUBSYSTEMS_HPP
#define SUBSYSTEMS_HPP

void intake_control(void *);
void sensors(void *);
void cata_control(void *);

extern int intake_state;
extern int cata_state;
extern pros::Controller master;

#endif