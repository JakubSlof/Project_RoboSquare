#include <Arduino.h>
#include "SmartServoBus.hpp"
#include <robotka.h>
const int wheel_diameter = 62;

//to do upravit parametry
//void turn(int degrees,int speed){
//  rkMotorsDrive(100, PI * wheel_diameter * degrees/360 ,speed);
//}
void check_battery(){
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

void setup() {
  rkConfig cfg;
  cfg.motor_max_power_pct = 100; // limit the power
  cfg.motor_wheel_diameter = wheel_diameter;
  cfg.motor_max_ticks_per_second = 10000;
  cfg.motor_max_acceleration = 15000;
  rkSetup(cfg);
  Serial.begin(115200);//starts serial communication
}

void loop() {
}

