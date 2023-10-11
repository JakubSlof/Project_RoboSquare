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

void RoboSquare::turn(int degrees,int speed){
  rkMotorsDrive(- ((PI * wheel_base) / 360) * degrees, ((PI * wheel_base) / 360) * degrees ,speed);
}
void RoboSquare::arc(int angle, int radius, int speed, char side){
    int inner_length = (2 * PI * radius) / 360 * degrees;
    int outer_lenght = (2*PI*(wheel_base+radius)) / 360 * degrees;
  if(side == 'left'){
    rkMotorsDriveLeftAsync(inner_length, speed, []() {printf("Dojel jsem!\n");});
    rkMotorsDriveRightAsync(outer_lenght, (speed*outer_lenght)/inner_length, []() {printf("Dojel jsem!\n");});
  }
  if(side == 'right'){
    rkMotorsDriveRightAsync(inner_length, speed, []() {printf("Dojel jsem!\n");});
    rkMotorsDriveLeftAsync(outer_lenght, (speed*outer_lenght)/inner_length, []() {printf("Dojel jsem!\n");});
  }
  else{
    Serial.println('wrong argument in function arc please insert left or right in argument side');
  }
  
}