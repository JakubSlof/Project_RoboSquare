#include "Robo_Square.h"

void RoboSquare::check_battery(){
  int battery_percent = 0;
  int battery_mid = 50;
  int battery_low = 20;
  battery_percent = rkBatteryPercent();
  if(battery_percent > battery_mid){//if battery have more than 50% 
    rkLedGreen(true); // turn on green LED
  }
  if((battery_percent > battery_low) && (battery_percent < battery_mid)){//if baterry have 20 - 50%
    rkLedYellow(true); // turn on yellow LED
  }
  else{//if battery has less than 20%
    rkLedRed(true); // turn on red LED
  }
}

void RoboSquare::forward(double lenght, int speed){
  rkMotorsDrive(lenght * gears_ratio, lenght * gears_ratio, speed);
}

void RoboSquare::turn(double angle,int speed){
  angle = angle + 11;//for repairing unpercised calculations 
  rkMotorsDrive(-((PI * wheel_base) / 360) * angle*gears_ratio, ((PI * wheel_base) / 360) * angle*gears_ratio ,speed);
}

void RoboSquare::arc(double angle, double radius, int speed, std::string side){
    double inner_length = (2 * PI * radius) / 360 * angle * gears_ratio;
    double outer_lenght = (2 * PI * (wheel_base + radius)) / 360 * angle * gears_ratio;
  if(side == "left"){
    rkMotorsDriveLeftAsync(inner_length, speed, []() {Serial.print("Dojel jsem!\n");});
    rkMotorsDriveRightAsync(outer_lenght, (speed * outer_lenght) / inner_length, []() {Serial.print("Dojel jsem!\n");});
  }
  if(side == "right"){
    rkMotorsDriveRightAsync(inner_length, speed, []() {Serial.print("Dojel jsem!\n");});
    rkMotorsDriveLeftAsync(outer_lenght, (speed*outer_lenght)/inner_length, []() {Serial.print("Dojel jsem!\n");});
  }
  else{
    Serial.println("error, used wrong argument");
  }
}

void RoboSquare::receve_data(){
while (true){
   int data = Serial.parseInt();
}

}