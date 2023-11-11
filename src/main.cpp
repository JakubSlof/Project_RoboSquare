#include "Robo_Square.h"
#include<thread>
#include<Arduino.h>
RoboSquare RBS;


void forward_f(int distance){
    distance = distance * RBS.gears_ratio;
    double left = 0;
    double right =0;
    rkMotorsSetSpeed(100,100);
    while (left <= distance & right <= distance) 
    {
     left = rkMotorsGetPositionLeft();
     right = rkMotorsGetPositionRight();
     delay(1);
    }
    rkMotorsSetSpeed(0,0);  
}

void arc_f(double angle, double radius, int speed, int calibration, std::string side){
    angle = angle + calibration;
        double inner_length = (2 * PI * radius) / 360 * angle * RBS.gears_ratio;
        double outer_lenght = (2 * PI * (RBS.wheel_base + radius)) / 360 * angle * RBS.gears_ratio;
        int inner_speed = speed * (inner_length/outer_lenght);
        int outer_speed = speed;
    if(side == "left"){
        double left = 0;
        double right = 0;
        rkMotorsSetSpeedLeft(inner_speed);
        rkMotorsSetSpeedRight(outer_speed);
        while (left <= inner_length & right <= outer_lenght) 
            {
            left = rkMotorsGetPositionLeft();
            right = rkMotorsGetPositionRight();
            delay(1);
            }
             rkMotorsSetSpeed(0,0);  
        //rkMotorsDriveLeftAsync(inner_length, speed * (inner_length/outer_lenght), []() {Serial.print("Dojel jsem!\n");});
        //rkMotorsDriveRightAsync(outer_lenght, speed, []() {Serial.print("Dojel jsem!\n");});
    }
    if(side == "right"){
        double left = 0;
        double right = 0;
        rkMotorsSetSpeedLeft(outer_speed);
        rkMotorsSetSpeedRight(inner_speed);
        while (left <= outer_lenght & right <= inner_length) 
            {
            left = rkMotorsGetPositionLeft();
            right = rkMotorsGetPositionRight();
            delay(1);
            }
             rkMotorsSetSpeed(0,0);  
        //rkMotorsDriveRightAsync(inner_length, speed*(inner_length/outer_lenght), []() {Serial.print("Dojel jsem!\n");});
        //rkMotorsDriveLeftAsync(outer_lenght, speed, []() {Serial.print("Dojel jsem!\n");});
    }
    else{
        Serial.println("error, used wrong argument");
    }
}

void setup() {
  rkConfig cfg;
  cfg.motor_max_power_pct = 50; // limit the power
  cfg.motor_wheel_diameter = RBS.wheel_diameter;
  cfg.motor_max_ticks_per_second = 10000;
  cfg.motor_max_acceleration = 17500;
  rkSetup(cfg);
  Serial.begin(115200);//starts serial communication
  //std::thread thread1(&RoboSquare::check_battery, &RBS);// example of using thread 
  RBS.check_battery();
  //RBS.arc(80,250,20,"left");
  //RBS.turn(80,100);//nefunguje
  //RBS.forward(1000,80);//funguje 
  //int count = 15;
  // Serial.println("69");
  // for (size_t i = 0; i < count; i++){
  //    while (true){
  //       int number = Serial.parseInt();
  //       if (number==1){
  //       break;
  //       }
  //    }
  // start tlacitko
    while (true) {
        if (rkButtonIsPressed(BTN_UP)) {
            break;
        }
    } 
        //esko s oblouky
    RBS.forward(500,100);
    RBS.arc(180,150,100,0,"right");
    delay(3000);
    RBS.forward(100,100);
    RBS.arc(180,150,100,-1,"left");
    delay(3000);  
    RBS.forward(1000,100);  
}

void loop(){
  //Serial.print("L: ");
}