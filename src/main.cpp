#include<Arduino.h>
#include"RBCX.h"
auto& man = rb::Manager::get(); //needs to be there to work man.sometning

double mm_to_ticks = 0.104;
int wheel_base = 170;
int last_ticks_M4 = 0;
int last_ticks_M1 = 0;
/**
 * 
 * Updates last ticks
 * 
 * @return None
 */
void UpdateLastTicks(){
  int ticks_M1 = 0;
  int ticks_M4 = 0;
        ticks_M4 = man.motor(rb::MotorId::M4).position();
        ticks_M1 = man.motor(rb::MotorId::M1).position();
  //update global variables
  last_ticks_M1 = ticks_M1;
  last_ticks_M4 = ticks_M4;
  //////////////////////////////
  Serial.print("lastticksM1:");
  Serial.println(last_ticks_M1);
  Serial.print("lastticksM4:");
  Serial.println(last_ticks_M4);
}
void arc_right(int angle, int radius){
   auto& man = rb::Manager::get(); 
   double inner_lenght = (((2*PI*radius)/360)*angle)/mm_to_ticks;
   double outer_lenght = (((2*3.14*(radius + wheel_base))/360)*angle) / mm_to_ticks;
   Serial.println(inner_lenght);
   int outer_sped = 3200;
   int inner_speed = -(outer_sped*inner_lenght)/outer_lenght;
   Serial.println(inner_speed);
   int tics_M1 = 0;
   int tics_M4 = 0;
   Serial.println(outer_lenght);
       while ((inner_lenght > tics_M4) && (outer_lenght > tics_M1 ) ) { ////inner_lenght < (tics_M1*mm_to_ticks)
       man.motor(rb::MotorId::M1).speed(outer_sped);
       man.motor(rb::MotorId::M4).speed(inner_speed);
       man.motor(rb::MotorId::M1).requestInfo([&tics_M1](rb::Motor& info) {
            //printf("M1: position:%d\n", info.position());
            tics_M1 = info.position()-last_ticks_M1;
        });
        man.motor(rb::MotorId::M4).requestInfo([&tics_M4](rb::Motor& info) {
            //printf("M4: position:%d\n", info.position());
            tics_M4 = info.position()-last_ticks_M4;
        });
        delay(10);
       }
       man.motor(rb::MotorId::M1).speed(0);
       man.motor(rb::MotorId::M4).speed(0);
       UpdateLastTicks();
}
void Straight(int speed, int distance,bool deceleration_enabled){
  double acceleration = 0.8;
  double deceleration = 1;
  auto& man = rb::Manager::get(); 
   int ticks_M1 = 0;
   int ticks_M4 = 0;
   distance = distance / mm_to_ticks;
   int deceleration_distance = 100/mm_to_ticks;
   
   
  while((ticks_M1 < distance) && (ticks_M4 < distance)){
    if(acceleration<1){
    acceleration = acceleration + 0.02;}
    if(deceleration_enabled == true && (ticks_M1 > (distance-deceleration_distance)) && (ticks_M4 > (distance-deceleration_distance))&&deceleration<1){
      deceleration = deceleration - 0.05;
    
   }
    man.motor(rb::MotorId::M1).speed(speed*acceleration*deceleration);
    man.motor(rb::MotorId::M4).speed(-speed*acceleration*deceleration);

    man.motor(rb::MotorId::M4).requestInfo([&ticks_M4](rb::Motor& info) {
            printf("M4: position:%d\n", info.position());
            ticks_M4 = info.position()-last_ticks_M4;
        });
        man.motor(rb::MotorId::M1).requestInfo([&ticks_M1](rb::Motor& info) {
            printf("M1: position:%d\n", info.position());
            ticks_M1 = info.position()-last_ticks_M1;
        });
    delay(10);
  }

  man.motor(rb::MotorId::M1).speed(0);
  man.motor(rb::MotorId::M4).speed(0);
  UpdateLastTicks();
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
   double inner_lenght = (((2*PI*radius)/360)*angle)/mm_to_ticks;
   double outer_lenght = (((2*3.14*(radius + wheel_base))/360)*angle) / mm_to_ticks;
   Serial.println(inner_lenght);
   int outer_sped = -3200;
   int inner_speed = -(outer_sped*inner_lenght)/outer_lenght;
   Serial.println(inner_speed);
   int tics_M1 = 0;
   int tics_M4 = 0;
   Serial.println(outer_lenght);
       while ((inner_lenght > tics_M1) && (outer_lenght > tics_M4 ) ) { ////inner_lenght < (tics_M1*mm_to_ticks)
       man.motor(rb::MotorId::M4).speed(outer_sped);
       man.motor(rb::MotorId::M1).speed(inner_speed);
       man.motor(rb::MotorId::M4).requestInfo([&tics_M4](rb::Motor& info) {
            //printf("M4: position:%d\n", info.position());
            tics_M4 = info.position()-last_ticks_M4;
        });
        man.motor(rb::MotorId::M1).requestInfo([&tics_M1](rb::Motor& info) {
            //printf("M1: position:%d\n", info.position());
            tics_M1 = info.position()-last_ticks_M1;
        });
        delay(10);
       }
       man.motor(rb::MotorId::M1).speed(0);
       man.motor(rb::MotorId::M4).speed(0);
       UpdateLastTicks();
} 



void setup() {
  // Get the manager instance as a singleton
  auto& man = rb::Manager::get();
  // Install the manager
  man.install();
  
  // Set the serial communication baud rate to 115200
  Serial.begin(115200);
  Straight(3200, 500,true);
  arc_right(170, 150);
  Straight(3200, 150,true);
  arc_left(150, 150);
  Straight(3200, 1000,true);
  // arc_left(180,200);
  // delay(100);
  // UpdateLastTicks();
  
  //Serial.println("done 2");

}

void loop(){
  //Serial.print("L: ");
}