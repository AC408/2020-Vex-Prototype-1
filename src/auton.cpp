#include "main.h"

double d_ratio = 3.25;

//power
double left = 0;
double right = 0;
double left_ang = 0;
double right_ang = 0;

//states
int state = 0;
bool angle_state = false;
bool drive_state = false; 

//drive function
double desired_angle = 0;
void set_angle(double angle){
    desired_angle = angle;
    angle_state = true;
}

double desired_dist = 0;
void set_dist(double dist){
    desired_dist = dist;
    drive_state = true;
    angle_state = true;
}

double velCap = 0;
double dist = 0;
void target_drive(double distance){
   dist = distance;
   velCap = 0;
}
 
void forward(void*){
   double kp = 10;
   double kd = 10;
   double kp_theta = 10;
   double curr_angle = get_angle();
   double theta_threshold = 0;
   double dist_threshold = 0;
   double curr_left = get_left_pos();
   double acc = 10;
   double vel_lim = 100;
   while(true){
       double left = 0;
       double right = 0;
       if(abs(curr_angle-get_angle())>theta_threshold){
           double theta_err = get_angle()-curr_angle;
           right += kp_theta*theta_err;
           left -= kp_theta*theta_err;
       }
       double relative = get_left_pos()-curr_left;
       if(abs(relative-dist)>dist_threshold){
           double err = relative-dist;
           double left_dist = err*kp;
           velCap+=acc;
           if(velCap>vel_lim){
               velCap = vel_lim;
           }
           if(abs(left_dist) > velCap){
               left_dist = velCap * sgn(left_dist);
           }
           right += left_dist;
           left += left_dist;
       } set_left(left);
       set_right(right);
       pros::delay(20);
   }
}
 
double omegaCap = 0;
double angle = 0;
void target_theta(double theta){
   angle = theta;
   omegaCap = 0;
}
 
void turn(void*){
   double kp = .1;
   double kd = .1;
   double curr_angle = get_angle();
   double theta_threshold = 0;
   double alpha = 10;
   double omega_lim = 100;
   while(true){
       if(abs(get_angle() - curr_angle) > theta_threshold){
           double theta_err = get_angle() - curr_angle;
           double right = theta_err * kp;
           omegaCap += alpha; //increments angular velocity with accel value
           if(omegaCap > omega_lim){
               omegaCap = omega_lim; //checks for values greater than the speed limit
           }
           if(abs(right) > omegaCap){
               right = omegaCap * sgn(right);
           }
       }
       printf("%f", right);
       set_left(-right);
       set_right(right);
       pros::delay(20);
   }
}

void drive_control(void *)
{
    double kp_theta = 0;
    double kd_theta = 0;
    double kp = 0;
    double kd = 0;
    while(true){
        switch(state){
            case 1: //angle
                {
                    double curr = get_angle();
                    double target_angle = desired_angle;
                    double tol = 10;
                    double err = 0;
                    if(abs(err)>tol){
                        double last_err = 0;
                        err = target_angle - curr;
                        double proportion = kp_theta*err;
                        double derivative = (err-last_err)*kd_theta;
                        last_err = err;
                        double power = proportion + derivative;
                        left_ang = -(power);
                        right_ang = power;
                        angle_state = true; //angle not at position
                        state = 1; 
                    } else{ //angle at position
                        state = 0;
                        angle_state = false;
                    } if(drive_state){ //drive necessity overwrites
                        state = 2;
                    } break;
                }
            case 2: //drive
                {
                    double curr = get_left_pos();
                    double target_dist = desired_dist*d_ratio;
                    double tol = 10;
                    double err = 0;
                    if(abs(err)>tol){
                        double last_err = 0;
                        err = target_dist - curr;
                        double proportion = kp*err;
                        double derivative = (err-last_err)*kd;
                        last_err = err;
                        double power = proportion + derivative;
                        left = right = power;
                        drive_state = true; //drive not at position
                        state = 1; //relies on angle to exit loop -> if initially no error, drive will still check angle
                    } else{
                        drive_state = false;
                    } break;
                }
            case 0: //no movement
                left = right = left_ang = right_ang = 0;
                break;
        } set_left(left+left_ang);
        set_right(right+right_ang);
        pros::delay(20);
    }
}

void score(int ball){
    // convey_time(100,400);
    // intake_time(100,100*ball);
    // forward_time(-50,100);
    // turn_time(8,100);
    // intake_time(-127,100*ball+100);

}

//----------------------------------------------------------------

void preauton()
{
    // drive_hold();
    // intake_time(100,100);
}

void test(){
}


void skill(){
    // preauton(); //first goal

    // set_intake(127); //second goal
    // forward_time(70,700);
    // convey_time(100,100);
    // turn_time(80,270);
    // forward_time(50,700);
    // convey_time(100,100);
    // forward_time(-50,700);
    // turn_time(80,270);
    // set_intake(0);
    // forward_time(50,750);
    // score(2);
    // forward_time(-100,1000);
    // turn_time(-80,370);

    // set_intake(127); //third goal
    // forward_time(50,600);
    // convey_time(100,100);
    // turn_time(80,270);
    // forward_time(50,400);
    // convey_time(100,100);
    // set_intake(0);
    // forward_time(50,200);
    // score(1);
    // turn_time(-80,645);

    // set_intake(127); //fourth goal
    // forward_time(70,1200);
    // convey_time(100,100);
    // turn_time(80,545);
    // forward_time(70,700);
    // convey_time(100,100);
    // forward_time(-70,700);
    // turn_time(-80,270);
    // set_intake(0);
    // forward_time(50,750);
    // score(2);
    // turn_time(-80,880);

    // set_intake(127); //fifth goal
    // forward_time(70,1200);
    // convey_time(100,100);
    // turn_time(80,780);
    // set_intake(0);
    // forward_time(50,700);
    // score(1);
    // turn_time(-80,645);
 
    // set_intake(127); //sixth goal
    // forward_time(70,700);
    // convey_time(100,100);
    // turn_time(-80,270);
    // forward_time(70,700);
    // convey_time(100,100);
    // forward_time(-70,500);
    // turn_time(80,270);
    // set_intake(0);
    // forward_time(50,700);
    // score(2);
    // forward_time(-100,1000);
    // turn_time(-80,370);

    // set_intake(127); //seventh goal
    // forward_time(70,600);
    // convey_time(100,100);
    // turn_time(80,270);
    // forward_time(70,400);
    // convey_time(100,100);
    // set_intake(0);
    // forward_time(50,200);
    // score(1);
    // turn_time(-80,645);

    // set_intake(127); //eighth goal
    // forward_time(70,1200);
    // convey_time(100,100);
    // turn_time(80,545);
    // forward_time(70,700);
    // convey_time(100,100);
    // forward_time(-70,700);
    // turn_time(-80,270);
    // set_intake(0);
    // forward_time(50,750);
    // score(2);
    // turn_time(-80,880);

    // set_intake(127); //ninth goal
    // forward_time(70,900);
    // convey_time(100,100);
    // turn_time(80,780);
    // set_intake(0);

    // //descore mid
    // double sign = 0;
    // for(int i = 0; i<5; i++){
    //     if(i%2==0){
    //         sign = -1;
    //     } else {
    //         sign = 1;
    //     }
    //     forward_time(50*sign,400);
    // }
    
    // //descore first goal
    // forward_time(50,700);
    // intake_time(100,100);

    // //score mid
    // forward_time(-70,300);
    // intake_time(-127,100);
    // turn_time(80,1050);
    // forward_time(50,1200);
    // convey_time(100,400);

}

void auton_1(){

}

void auton_2(){

}