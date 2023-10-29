#include "Robo_Square.h"
#include<thread>
#include<Arduino.h>
RoboSquare RBS;
void setup() {
  rkConfig cfg;
  cfg.motor_max_power_pct = 100; // limit the power
  cfg.motor_wheel_diameter = RBS.wheel_diameter;
  cfg.motor_max_ticks_per_second = 10000;
  cfg.motor_max_acceleration = 17500;
  rkSetup(cfg);
  Serial.begin(115200);//starts serial communication
  //std::thread thread1(&RoboSquare::check_battery, &RBS);// example of using thread 
  //RBS.check_battery();
  //RBS.arc(90,250,20,"left");
  //RBS.turn(90,100);//nefunguje
  //RBS.forward(1000,80);//funguje 
 // int count = 5;
 // for (size_t i = 0; i < count; i++)
 // {
 //    Serial.println("69");
  //while (true)
 // {
   // int number = Serial.parseInt();
   // if (number==1){
   //   break;
  //  }
 // }
  //popojeti virtual 
 // rkLedBlue(true);
 // delay(8000);
  //rkLedBlue(false);
 // delay(1000);
  //Serial.println("69");
  //}


}



void loop() {

}