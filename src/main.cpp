#include<Arduino.h>
#include"RBCX.h"
double tics_to_mm = 0.106;
int wheel_base = 170;
int last_tics_M4 = 0;
int last_tics_M1 = 0;

void arc_right(int angle, int radius){
   auto& man = rb::Manager::get(); 
   double inner_lenght = (((2*PI*radius)/360)*angle)/tics_to_mm;
   double outer_lenght = (((2*3.14*(radius + wheel_base))/360)*angle) / tics_to_mm;
   Serial.println(inner_lenght);
   int outer_sped = 3200;
   int inner_speed = -(outer_sped*inner_lenght)/outer_lenght;
   Serial.println(inner_speed);
   int tics_M1 = 0;
   int tics_M4 = 0;
   Serial.println(outer_lenght);
       while ((inner_lenght > tics_M4) && (outer_lenght > tics_M1 ) ) { ////inner_lenght < (tics_M1*tics_to_mm)
       man.motor(rb::MotorId::M1).speed(outer_sped);
       man.motor(rb::MotorId::M4).speed(inner_speed);
       man.motor(rb::MotorId::M1).requestInfo([&tics_M1](rb::Motor& info) {
            printf("M1: position:%d\n", info.position());
            tics_M1 = info.position();
        });
        man.motor(rb::MotorId::M4).requestInfo([&tics_M4](rb::Motor& info) {
            printf("M4: position:%d\n", info.position());
            tics_M4 = info.position();
        });
        delay(1);
       }
       last_tics_M1 = last_tics_M1- tics_M1;
       last_tics_M4 = last_tics_M4 - tics_M4;
       man.motor(rb::MotorId::M1).speed(0);
       man.motor(rb::MotorId::M4).speed(0);
}

/**
 * Controls the movement of a robot in an arc to the right.
 * 
 * @param angle: an integer representing the angle of the arc in degrees
 * @param radius: an integer representing the radius of the arc in millimeters
 * 
 * @return None
 */
void arc_left(int angle, int radius){
   auto& man = rb::Manager::get(); 
   double inner_lenght = (((2*PI*radius)/360)*angle)/tics_to_mm;
   double outer_lenght = (((2*3.14*(radius + wheel_base))/360)*angle) / tics_to_mm;
   Serial.println(inner_lenght);
   int outer_sped = -3200;
   int inner_speed = -(outer_sped*inner_lenght)/outer_lenght;
   Serial.println(inner_speed);
   int tics_M1 = 0;
   int tics_M4 = 0;
   Serial.println(outer_lenght);
       while ((inner_lenght > tics_M1) && (outer_lenght > tics_M4 ) ) { ////inner_lenght < (tics_M1*tics_to_mm)
       man.motor(rb::MotorId::M4).speed(outer_sped);
       man.motor(rb::MotorId::M1).speed(inner_speed);
       man.motor(rb::MotorId::M4).requestInfo([&tics_M4](rb::Motor& info) {
            printf("M4: position:%d\n", info.position());
            tics_M4 = info.position();
        });
        man.motor(rb::MotorId::M1).requestInfo([&tics_M1](rb::Motor& info) {
            printf("M1: position:%d\n", info.position());
            tics_M1 = info.position();
        });
        delay(1);
       }
       man.motor(rb::MotorId::M1).speed(0);
       man.motor(rb::MotorId::M4).speed(0);
} 



void setup() {
  // Get the manager instance as a singleton
  auto& man = rb::Manager::get();
  
  // Install the manager
  man.install();
  
  // Set the serial communication baud rate to 115200
  Serial.begin(115200);
  
  // Call the arc_right function with an angle of 180 degrees and a radius of 100 millimeters
  arc_right(180, 100);
  
  // Call the arc_left function with an angle of 180 degrees and a radius of 100 millimeters
  arc_left(180, 100);
}

void loop(){
  //Serial.print("L: ");
}