#include "Robo_Square.h"
#include<thread>
#include<Arduino.h>
RoboSquare RBS;
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



   


void loop() {
}