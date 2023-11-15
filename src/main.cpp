#include<thread>
#include<Arduino.h>
#include "RBCX.h"
double tics_to_mm = 300; // todo calculate the right value 

void strait(int distance, int speed){
   auto& man = rb::Manager::get(); //this needs to be there 

   int tics1 = 0; //counter for ticks on motor 1
   int tics4 = 0; //counter for ticks on motor 4
   while(tics1<(distance*tics_to_mm) & tics4<(distance*tics_to_mm) ){ //checking if ticks on encoder is smaller than set value 
   man.motor(rb::MotorId::M1).speed(speed); //setting motor 1 speed
   man.motor(rb::MotorId::M4).speed(-speed); //setting motor 4 speed
   man.motor(rb::MotorId::M4).requestInfo([&tics4](rb::Motor& info){
         tics4 = info.position();
         Serial.print("M4:");
         Serial.println(tics4);
   });
   man.motor(rb::MotorId::M1).requestInfo([&tics1](rb::Motor& info){
         tics1 = info.position();
         Serial.print("M4:");
         Serial.println(tics1);
   });
   }
}


void setup() {

auto& man = rb::Manager::get(); // get manager instance as singleton
man.install(); // install manager
//int wheel_diameter = 72;
strait(500,32767);
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