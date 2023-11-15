#include<thread>
#include<Arduino.h>
#include "RBCX.h"
void drive_strait(){
   auto& man = rb::Manager::get();
   while(true){
   man.motor(rb::MotorId::M1).speed(320);
   man.motor(rb::MotorId::M4).speed(-320);
   }
}


void setup() {

auto& man = rb::Manager::get(); // get manager instance as singleton
man.install(); // install manager
//int wheel_diameter = 72;
drive_strait();
double ticks_to_mm = (72*PI)/1796;//to do 
////////////////////////////////driving forward 
   int32_t dist1 = 0;
   int32_t dist4 = 0;
   int32_t distance = 1780;
   Serial.println(ticks_to_mm);
while(distance>dist1){
man.motor(rb::MotorId::M1).speed(320);
man.motor(rb::MotorId::M4).speed(-320);

man.motor(rb::MotorId::M1).requestInfo([&dist1](rb::Motor& info) {
            dist1 = info.position();
            printf("M1: position:%d\n", info.position());
        });
man.motor(rb::MotorId::M4).requestInfo([&dist4,&ticks_to_mm](rb::Motor& info) {
            dist4 = info.position();
            dist4=-dist4;
            double distance = dist4*ticks_to_mm;
            printf("M4: position:%d\n", dist4);
            Serial.println(distance); 
        }); 
        
        delay(100);
   }
}



void loop(){
  //Serial.print("L: ");
}