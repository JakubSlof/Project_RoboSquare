#include "Robo_Square.h"

const int wheel_diameter = DEAFULT_WHEEL_DIAMETER; //wheel diameter of robot 
const int wheel_base = DEAFULT_WHEEL_BASE; //wheel base of robot 

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

