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