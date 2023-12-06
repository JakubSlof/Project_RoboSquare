#include<thread>
#include<Arduino.h>
#include"RBCX.h"
void measuring(){
   auto& man = rb::Manager::get(); //this needs to be there
   while(true){
   man.motor(rb::MotorId::M4).requestInfo([](rb::Motor& info){
         Serial.println(info.position());
   });
   delay(10);
   }
}
double tics_to_mm = 0.106;//to do (72*PI)/1796 0.125943580767519      500/4710
int wheel_base = 170;
int wheel_diameter = 72; //wheel diameter in mm
 int last_M1 = 0; //total ticks on motor 1 updated at the and of each driving function
 int last_M4 = 0; //total ticks on motor 4 updated at the and of each driving function

void strait(int distance, int speed){
   auto& man = rb::Manager::get(); //this needs to be there 
   int tics_M1 = 0; //counter for ticks on motor 1
   int tics_M4 = 0; //counter for ticks on motor 4
   while((tics_M1 < (distance / tics_to_mm)) & (tics_M4 < (distance / tics_to_mm))){ //checking if ticks on encoder is smaller than set value 
   man.motor(rb::MotorId::M1).speed(speed); //setting motor 1 speed
   man.motor(rb::MotorId::M4).speed(-speed); //setting motor 4 speed
   man.motor(rb::MotorId::M4).requestInfo([&tics_M4](rb::Motor& info){
         tics_M4 = info.position() - last_M4;
         Serial.print("M4: ");
         Serial.println(tics_M4);
   });
   man.motor(rb::MotorId::M1).requestInfo([&tics_M1](rb::Motor& info){
         tics_M1 = info.position() - last_M1;
         Serial.print("M1: ");
         Serial.println(tics_M1);
   });
   }
   last_M1 = tics_M1 + last_M1;
   last_M4 = tics_M4 + last_M4;
   
   Serial.print("lastM1: ");
   Serial.println(last_M1);
   Serial.print("lastM4: ");
   Serial.println(last_M4);
}

void arc(double angle, double radius, int speed, int calibration, std::string side){
   auto& man = rb::Manager::get(); //this needs to be there
   angle = angle + calibration;
   int inner_length = ((2 * PI * radius) * ( angle / 360)) / tics_to_mm;
   int outer_lenght = ((2 * PI * (wheel_base + radius)) * (angle / 360) )/ tics_to_mm;
   Serial.print("inner lenght: ");
   Serial.println(inner_length);
   Serial.print("outer lenght: ");
   Serial.println(outer_lenght);

   if(side == "left"){
      int tics_M1 = 0; //counter for ticks on motor 1
      int tics_M4 = 0; //counter for ticks on motor 4
      int speed_M1 = speed;
      int speed_M4 = - speed_M1 * (inner_length / outer_lenght); //there is minus because moror is twisted so they need to rotate sane direction 
      Serial.print("speed_M4: ");
      Serial.println(speed_M4);
      Serial.print("speed_M1: ");
      Serial.println(speed_M1);
      while((tics_M1 < inner_length) & (tics_M4 < outer_lenght)){
          man.motor(rb::MotorId::M1).speed(speed_M1); //setting motor 1 speed
          man.motor(rb::MotorId::M4).speed(speed_M4); //setting motor 4 speed
          man.motor(rb::MotorId::M4).requestInfo([&tics_M4](rb::Motor& info){ //reading motor 4 encoder 
          tics_M4 = info.position() - last_M4;
          //Serial.print("M4:");
          //Serial.println(tics4);
         });
         man.motor(rb::MotorId::M1).requestInfo([&tics_M1](rb::Motor& info){ //reading moror 1 encoder 
         tics_M1 = info.position() - last_M1;
         //Serial.print("M1:");
         //Serial.println(tics1);
         });
         delay(10);
      }
      last_M1 = tics_M1 + last_M1;
      last_M4 = tics_M4 + last_M4;
      Serial.print("lastM1: ");
      Serial.println(last_M1);
      Serial.print("lastM4: ");
      Serial.println(last_M4);
      Serial.println(tics_M1);
      Serial.println(tics_M4);
  }
  if(side == "right"){
      int tics_M1 = 0; //counter for ticks on motor 1
      int tics_M4 = 0; //counter for ticks on motor 4
      int speed_M4 = -speed;
      int speed_M1 = -speed_M4*(inner_length/outer_lenght);
      Serial.print("speed_M4: ");
      Serial.println(speed_M4);
      Serial.print("speed_M1: ");
      Serial.println(speed_M1);
      while((tics_M1 < inner_length) & (tics_M4 < outer_lenght)){
          man.motor(rb::MotorId::M1).speed(speed_M1); //setting motor 1 speed
          man.motor(rb::MotorId::M4).speed(speed_M4); //setting motor 4 speed
          man.motor(rb::MotorId::M4).requestInfo([&tics_M4](rb::Motor& info){ //reading motor 4 encoder 
          tics_M4 = info.position() - last_M4;
          //Serial.print("M4:");
          //Serial.println(tics44);
         });
         man.motor(rb::MotorId::M1).requestInfo([&tics_M1](rb::Motor& info){ //reading moror 1 encoder 
         tics_M1 = info.position() - last_M1;
         //Serial.print("M1:");
         //Serial.println(tics11);
         });
         delay(10);
      }
      last_M1 = tics_M1 + last_M1;
      last_M4 = tics_M4 + last_M4;
      Serial.print("lastM1: ");
      Serial.println(last_M1);
      Serial.print("lastM4: ");
      Serial.println(last_M4);
  }
  if((side!="right") || (side!="left")){
    Serial.println("error, used wrong argument");
  }
}
void setup() {
auto& man = rb::Manager::get(); // get manager instance as singleton
man.install(); // install manager
Serial.begin(115200);
//strait(500,32767);
arc(180,100,3150,0,"left");
//arc(180,150,3150,0,"left");
//measuring();
}

void loop(){
  //Serial.print("L: ");
}