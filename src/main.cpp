#include<thread>
#include<Arduino.h>
#include"RBCX.h"

double tics_to_mm = 0.125943580767519;//to do (72*PI)/1796
int wheel_base = 170;
 int last_M1 = 0;
 int last_M4 = 0;

void strait(int distance, int speed){
   auto& man = rb::Manager::get(); //this needs to be there 

   int tics1 = 0; //counter for ticks on motor 1
   int tics4 = 0; //counter for ticks on motor 4
   while((tics1<(distance/tics_to_mm)) & (tics4<(distance/tics_to_mm)) ){ //checking if ticks on encoder is smaller than set value 
   man.motor(rb::MotorId::M1).speed(speed); //setting motor 1 speed
   man.motor(rb::MotorId::M4).speed(-speed); //setting motor 4 speed
   man.motor(rb::MotorId::M4).requestInfo([&tics4](rb::Motor& info){
         tics4 = info.position();
         Serial.print("M4:");
         Serial.println(tics4);
   });
   man.motor(rb::MotorId::M1).requestInfo([&tics1](rb::Motor& info){
         tics1 = info.position();
         Serial.print("M1:");
         Serial.println(tics1);
   });
   }
   //man.motor(rb::MotorId::M1).speed(0); //setting motor 1 speed
   //man.motor(rb::MotorId::M4).speed(0); //setting motor 4 speed
}

void arc(double angle, double radius, int speed, int calibration, std::string side){
   auto& man = rb::Manager::get(); //this needs to be there
   angle = angle + calibration;
   double inner_length = ((2 * PI * radius) / 360 * angle) / tics_to_mm;
   double outer_lenght = ((2 * PI * (wheel_base + radius)) / 360 * angle )/ tics_to_mm;
   Serial.println(inner_length);
   Serial.println(outer_lenght);

   if(side == "left"){
      int speed_M1 = speed;
      int speed_M4 = -speed_M1*(inner_length/outer_lenght); //there is minus because moror is twisted so they need to rotate sane direction 
      Serial.println(speed_M4);
      Serial.println(speed_M1);
      int tics1 = 0; //counter for ticks on motor 1
      int tics4 = 0; //counter for ticks on motor 4
      while((tics1<inner_length) & (tics4<outer_lenght)){
          man.motor(rb::MotorId::M1).speed(speed_M1); //setting motor 1 speed
          man.motor(rb::MotorId::M4).speed(speed_M4); //setting motor 4 speed
          man.motor(rb::MotorId::M4).requestInfo([&tics4](rb::Motor& info){ //reading motor 4 encoder 
          tics4 = info.position()-last_M4;
          //Serial.print("M4:");
          //Serial.println(tics4);
         });
         man.motor(rb::MotorId::M1).requestInfo([&tics1](rb::Motor& info){ //reading moror 1 encoder 
         tics1 = info.position()-last_M1;
         //Serial.print("M1:");
         //Serial.println(tics1);
         });
         delay(10);
      }
      last_M1 = tics1;
      last_M4 = tics4;
         Serial.print("lastM1: ");
         Serial.println(last_M1);
         Serial.print("lastM4: ");
         Serial.println(last_M4);
  }
  if(side == "right"){
      int tics11 = 0; //counter for ticks on motor 1
      int tics44 = 0; //counter for ticks on motor 4
      int speed_M4 = -speed;
      int speed_M1 = -speed_M4*(inner_length/outer_lenght);
      Serial.println(speed_M1);
      while((tics11<inner_length) & (tics44<outer_lenght)){
          man.motor(rb::MotorId::M1).speed(speed_M1); //setting motor 1 speed
          man.motor(rb::MotorId::M4).speed(speed_M4); //setting motor 4 speed
          man.motor(rb::MotorId::M4).requestInfo([&tics44](rb::Motor& info){ //reading motor 4 encoder 
          tics44 = info.position()-last_M4;
          //Serial.print("M4:");
          //Serial.println(tics44);
         });
         man.motor(rb::MotorId::M1).requestInfo([&tics11](rb::Motor& info){ //reading moror 1 encoder 
         tics11 = info.position()-last_M1;
         //Serial.print("M1:");
         //Serial.println(tics11);
         });
         delay(10);
         
      }
      last_M1 = tics11;
      last_M4 = tics44;
         Serial.print("lastM1: ");
         Serial.println(last_M1);
         Serial.print("lastM4: ");
         Serial.println(last_M4);
    //rkMotorsDriveRightAsync(inner_length, speed*(inner_length/outer_lenght), []() {Serial.print("Dojel jsem!\n");});
    //rkMotorsDriveLeftAsync(outer_lenght, speed, []() {Serial.print("Dojel jsem!\n");});
  }
  if((side!="right") || (side!="left")){
    Serial.println("error, used wrong argument");
  }
}



void setup() {

auto& man = rb::Manager::get(); // get manager instance as singleton
man.install(); // install manager
//int wheel_diameter = 72;
Serial.begin(115200);
//strait(500,32767);
arc(180,150,3150,0,"left");
arc(180,150,3150,0,"right");
}

void loop(){
  //Serial.print("L: ");
}