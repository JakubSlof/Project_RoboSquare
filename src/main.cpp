#include "Robo_Square.h"
 
RoboSquare RBS;

void setup() {
  rkConfig cfg;
  cfg.motor_max_power_pct = 100; // limit the power
  cfg.motor_wheel_diameter = RBS.wheel_diameter;
  cfg.motor_max_ticks_per_second = 10000;
  cfg.motor_max_acceleration = 15000;
  rkSetup(cfg);
  Serial.begin(115200);//starts serial communication
  RBS.check_battery();
}

void loop() {
}

