#include "main.h"

//ASYNC DOESNT BLOCK, REGULAR BLOCK..... for CHASSISCONTROLLER
void init_protect(){
    profileController -> generatePath({{0_ft, 0_ft, 0_deg}, {10_in, 0_in, 0_deg}}, "A");
    profileController -> generatePath({{0_ft, 0_ft, 0_deg}, {24_in, 0_in, 0_deg}}, "B");
    profileController -> generatePath({{0_ft, 0_ft, 0_deg}, {20_in, 0_in, 0_deg}}, "C");
    profileController -> generatePath({{0_ft, 0_ft, 0_deg}, {22_in, 0_in, 0_deg}}, "D");
}

void init_skills()
{
    profileController -> generatePath({{0_ft, 0_ft, 0_deg}, {40_in, 0_in, 0_deg}},"A");
    profileController -> generatePath({{0_ft, 0_ft, 0_deg}, {16_in, 0_in, 0_deg}},"B");
    profileController -> generatePath({{0_ft, 0_ft, 0_deg}, {20_in, 0_in, 0_deg}},"C");
    profileController -> generatePath({{0_ft, 0_ft, 0_deg}, {30_in, 0_in, 0_deg}},"D");
    profileController -> generatePath({{0_ft, 0_ft, 0_deg}, {4_in, 0_in, 0_deg}},"E");
}

void init_unprotect(){
    profileController -> generatePath({{0_ft, 0_ft, 0_deg}, {20_in, 0_in, 0_deg}}, "A");
    profileController -> generatePath({{0_ft, 0_ft, 0_deg}, {27_in, 0_in, 0_deg}}, "B");
    profileController -> generatePath({{0_ft, 0_ft, 0_deg}, {155_in, 0_in, 0_deg}}, "C");
    profileController -> generatePath({{0_ft, 0_ft, 0_deg}, {80_in, 0_in, 0_deg}}, "D");
}