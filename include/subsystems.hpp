#ifndef SUBSYSTEMS_HPP
#define SUBSYSTEMS_HPP

extern bool tank;

void tray_outtake();
void fast_outtake();
void drive_control(void *);
void tray_control(void *);
void arm_control(void *);
void stacking_state();

#endif