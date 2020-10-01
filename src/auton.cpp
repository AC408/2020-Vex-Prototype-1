#include "main.h"

double d_ratio = 3.25;

void turn(double target)
{
    target = target*d_ratio;
    double curr = (get_left_front_pos() + get_right_front_pos())/2;
    double err = target - curr;
    double tol = 10;
    int spe[7] = {15,30,45,60,80,100,127};
    while(abs(err) > tol){        
        double sign = sgn(err);
        int input = int(err/10);
        if(input >= 7){
            input = 7;
        }
        set_left_back(sign*spe[input]);
        set_left_front(sign*spe[input]);
        set_right_back(sign*spe[input]);
        set_right_front(sign*spe[input]);
    }
   
}

void forward(double target)
{
    target = target*d_ratio;
    double curr = (get_left_front_pos() + get_right_front_pos())/2;
    double err = target - curr;
    double tol = 10;
    int spe[7] = {15,30,45,60,80,100,127};
    while(abs(err) > tol){        
        double sign = sgn(err);
        int input = int(err/10);
        if(input >= 7){
            input = 7;
        }
        set_left_back(sign*spe[input]);
        set_left_front(sign*spe[input]);
        set_right_back(sign*spe[input]);
        set_right_front(sign*spe[input]);
    }
}

void strafe_left(double target){
    target = target*d_ratio;
    double curr = (-get_left_front_pos() + get_left_back_pos())/2;
    double err = target - curr;
    double tol = 10;
    int spe[7] = {15,30,45,60,80,100,127};
    while(abs(err) > tol){        
        double sign = sgn(err);
        int input = int(err/10);
        if(input >= 7){
            input = 7;
        }
        set_left_back(sign*spe[input]);
        set_left_front(-sign*spe[input]);
        set_right_back(-sign*spe[input]);
        set_right_front(sign*spe[input]);
    }
}

void preauton()
{
    drive_hold();
}

void test(){
}


void skill(){

}

void auton_1(){

}

void auton_2(){

}