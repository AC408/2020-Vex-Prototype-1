#include "main.h"

void drive_control(void *)
{
    pros::Controller master(CONTROLLER_MASTER);
    drive_coast(); //motor isnt running
    while (true)
    {
        set_tank((master.get_analog(ANALOG_LEFT_X) + master.get_analog(ANALOG_RIGHT_Y)), (-master.get_analog(ANALOG_LEFT_X) + master.get_analog(ANALOG_RIGHT_Y)));
        pros::delay(20);
    }
}
