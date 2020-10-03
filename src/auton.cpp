#include "main.h"

double d_ratio = 3.25;

void forward_time(double volt, double time){
    set_left_back(volt);
    set_left_front(volt);
    set_right_back(volt);
    set_right_front(volt);
    pros::delay(time);

    set_left_front(0);
    set_left_back(0);
    set_right_front(0);
    set_right_back(0);
}

void turn_time(double volt, double time){ //clockwise is positive
    set_left_back(volt);
    set_left_front(volt);
    set_right_back(-volt);
    set_right_front(-volt);
    pros::delay(time);
    set_left_front(0);
    set_left_back(0);
    set_right_front(0);
    set_right_back(0);
}

void convey_time(double volt, double time){
    set_convey(volt);
    pros::delay(time);
    set_intake(0);
}

void intake_time(double volt, double time){
    set_intake(volt);
    pros::delay(time);
    set_intake(0);
}













void turn(double target)
{
    //clockwise
    target = target*d_ratio;
    double curr = (get_left_front_pos() + get_right_back_pos())/2;
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
        set_right_back(sign*-spe[input]);
        set_right_front(sign*-spe[input]);
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

void score(int ball){
    convey_time(100,400);
    intake_time(100,100*ball);
    forward_time(-50,100);
    turn_time(50,200);
    intake_time(-127,100*ball+100);

}


//----------------------------------------------------------------

void preauton()
{
    drive_hold();
    intake_time(100,100);
}

void test(){
}


void skill(){
    preauton(); //first goal

    set_intake(127); //second goal
    forward_time(70,700);
    convey_time(100,100);
    turn_time(50,200);
    forward_time(50,700);
    convey_time(100,100);
    forward_time(-50,700);
    turn_time(50,600);
    set_intake(0);
    forward_time(50,750);
    score(2);
    forward_time(-100,1000);
    turn_time(-50,600);

    set_intake(127); //third goal
    forward_time(50,600);
    convey_time(100,100);
    turn_time(50,600);
    forward_time(50,400);
    convey_time(100,100);
    set_intake(0);
    forward_time(50,200);
    score(1);
    turn_time(-70,600);

    set_intake(127); //fourth goal
    forward_time(70,1200);
    convey_time(100,100);
    turn_time(50,400);
    forward_time(70,700);
    convey_time(100,100);
    forward_time(-70,700);
    turn_time(-50,200);
    set_intake(0);
    forward_time(50,750);
    score(2);
    turn_time(-70,850);

    set_intake(127); //fifth goal
    forward_time(70,1200);
    convey_time(100,100);
    turn_time(50,400);
    set_intake(0);
    forward_time(50,700);
    score(1);
    turn_time(-50,400);
 
    set_intake(127); //sixth goal
    forward_time(70,700);
    convey_time(100,100);
    turn_time(-50,200);
    forward_time(70,700);
    convey_time(100,100);
    forward_time(-70,500);
    turn_time(50,300);
    set_intake(0);
    forward_time(50,700);
    score(2);
    forward_time(-100,1000);
    turn_time(-50,600);

    set_intake(127); //seventh goal
    forward_time(70,600);
    convey_time(100,100);
    turn_time(50,600);
    forward_time(70,400);
    convey_time(100,100);
    set_intake(0);
    forward_time(50,200);
    score(1);
    turn_time(-70,600);

    set_intake(127); //eighth goal
    forward_time(70,1200);
    convey_time(100,100);
    turn_time(50,400);
    forward_time(70,700);
    convey_time(100,100);
    forward_time(-70,700);
    turn_time(-50,200);
    set_intake(0);
    forward_time(50,750);
    score(2);
    turn_time(-70,850);

    set_intake(127); //ninth goal
    forward_time(70,900);
    convey_time(100,100);
    turn_time(50,600);
    set_intake(0);

    //descore mid
    double sign = 0;
    for(int i = 0; i<5; i++){
        if(i%2==0){
            sign = -1;
        } else {
            sign = 1;
        }
        forward_time(50*sign,400);
    }
    
    //descore first goal
    forward_time(50,700);
    intake_time(100,100);

    //score mid
    forward_time(-70,300);
    intake_time(-127,100);
    turn_time(50,800);
    forward_time(50,1200);
    convey_time(100,400);

}

void auton_1(){

}

void auton_2(){

}