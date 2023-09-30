#include <Arduino.h>
#include "SmartServoBus.hpp"
#include <robotka.h>
const int wheel_diameter = 62;

//to do upravit parametry
void turn(int degrees,int speed){
  rkMotorsDrive(100, PI * wheel_diameter * degrees/360 ,speed);
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
   float command = Serial.parseFloat();// reads data from serial port 

}

