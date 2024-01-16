#include<Arduino.h>
#include"RBCX.h"
auto& man = rb::Manager::get(); //needs to be there to work man.sometning
//r motor 3
// l motor 2
double mm_to_ticks = 0.104;
int wheel_base = 170;
int last_ticks_M4 = 0;
int last_ticks_M1 = 0;


struct klepeto
{
  int id = 4;
  void move(){
    //tady je kod co pohnek klepetem
  }
  int position(){
    //returns position of klepeto
    int position = 0;
    return position;
  }
};


void arc_right(int angle, int radius){
   man.motor(rb::MotorId::M1).setCurrentPosition(0);
   man.motor(rb::MotorId::M4).setCurrentPosition(0);
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
       man.motor(rb::MotorId::M1).speed(-outer_sped);
       man.motor(rb::MotorId::M4).speed(-inner_speed);
       man.motor(rb::MotorId::M1).requestInfo([&tics_M1](rb::Motor& info) {
            //printf("M1: position:%d\n", info.position());
            tics_M1 = info.position();
        });
        man.motor(rb::MotorId::M4).requestInfo([&tics_M4](rb::Motor& info) {
            //printf("M4: position:%d\n", info.position());
            tics_M4 = info.position();
        });
        delay(10);
       }
       man.motor(rb::MotorId::M1).speed(0);
       man.motor(rb::MotorId::M4).speed(0);
}
void Straight(int speed, int distance){
  auto& man = rb::Manager::get(); 
  man.motor(rb::MotorId::M1).setCurrentPosition(0);
  man.motor(rb::MotorId::M4).setCurrentPosition(0);
   int ticks_M1 = 0;
   int ticks_M4 = 0;
   distance = distance / mm_to_ticks;
  while((-ticks_M1 < distance) && (-ticks_M4 < distance)){
    man.motor(rb::MotorId::M1).speed(speed);
    man.motor(rb::MotorId::M4).speed(-speed);
    man.motor(rb::MotorId::M4).requestInfo([&ticks_M4](rb::Motor& info) {
            printf("M4: position:%d\n", info.position());
            ticks_M4 =  info.position();
        });
        man.motor(rb::MotorId::M1).requestInfo([&ticks_M1](rb::Motor& info) {
            printf("M1: position:%d\n", info.position());
            ticks_M1 =  info.position();
        });
    delay(1);
  }
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
    man.motor(rb::MotorId::M1).setCurrentPosition(0);
  man.motor(rb::MotorId::M4).setCurrentPosition(0);
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
       man.motor(rb::MotorId::M4).speed(-outer_sped);
       man.motor(rb::MotorId::M1).speed(-inner_speed);
       man.motor(rb::MotorId::M4).requestInfo([&tics_M4](rb::Motor& info) {
            //printf("M4: position:%d\n", info.position());
            tics_M4 = info.position();
        });
        man.motor(rb::MotorId::M1).requestInfo([&tics_M1](rb::Motor& info) {
            //printf("M1: position:%d\n", info.position());
            tics_M1 = info.position();
        });
        delay(10);
       }
       man.motor(rb::MotorId::M4).speed(0);
       man.motor(rb::MotorId::M1).speed(0);
      
} 
//test????
void Acceleration(int speed_from, int speed_to, int distance_mm){
     double distance_ticks = distance_mm / mm_to_ticks;
     double acc_const = speed_to/distance_ticks;
     int ticks_M1 = 0;
     int ticks_M4 = 0;
     while((ticks_M1 < distance_ticks) && (ticks_M4 < distance_ticks)){
        man.motor(rb::MotorId::M4).requestInfo([&ticks_M4](rb::Motor& info) {
            //printf("M4: position:%d\n", info.position());
            ticks_M4 = info.position();
        });
        man.motor(rb::MotorId::M1).requestInfo([&ticks_M1](rb::Motor& info) {
            //printf("M1: position:%d\n", info.position());
            ticks_M1 = info.position();
        });
       man.motor(rb::MotorId::M4).speed(-acc_const*ticks_M4+speed_from);
       man.motor(rb::MotorId::M1).speed(-acc_const*ticks_M1+speed_from);
      delay(10);
     }
}
void test(){
int M1 =0;
int M2 =0;
int M3 =0;
int M4 =0;
  while ((M1 < 5000 || M1 > -5000) & (M2 < 5000 || M2 > -5000) & (M3 < 5000 || M3 > -5000) & (M4 < 5000 || M4 > -5000) )
  { 
      man.motor(rb::MotorId::M1).speed(10000);
      man.motor(rb::MotorId::M2).speed(10000);
      man.motor(rb::MotorId::M3).speed(10000);
      man.motor(rb::MotorId::M4).speed(10000);
      man.motor(rb::MotorId::M1).requestInfo([&M1](rb::Motor& info) {
            printf("M1: position:%d\n", info.position());
            M1 = info.position();
        });
        man.motor(rb::MotorId::M1).requestInfo([&M2](rb::Motor& info) {
          printf("M2: position:%d\n", info.position());
            M2 = info.position();
        });
    man.motor(rb::MotorId::M4).requestInfo([&M3](rb::Motor& info) {
            printf("M3: position:%d\n", info.position());
          M3 = info.position();
        });
        man.motor(rb::MotorId::M1).requestInfo([&M4](rb::Motor& info) {
            //printf("M1: position:%d\n", info.position());
          M4 = info.position();
        });
  }
  

}
void setup() {
  // Get the manager instance as a singleton
  auto& man = rb::Manager::get();
  // Install the manager
  man.install();
  struct klepeto Klepeto_L, Klepeto_R;
  // Set the serial communication baud rate to 115200
  Serial.begin(115200);
  Straight(10000, 500);
  //man.stupidServo(0).setPosition(1);
  //arc_right(170, 150);
  //Straight(3200, 150);
  //arc_left(150, 150);
  //Straight(3200, 1000);
//Acceleration(100,3200,200);
//Straight(3200,300);
//Acceleration(3200,100,200);
// while (true) {
//         if(man.buttons().left()){
//           man.motor(rb::MotorId::M4).speed(20000);
//         }
//         else if(man.buttons().right()){
//           man.motor(rb::MotorId::M1).speed(20000);
//         }
//         if(man.buttons().down()) {
//             man.stupidServo(0).setPosition(2.0); // on button down, set servo to min range
//         } 
//         else if(man.buttons().up()) {
//             man.stupidServo(0).setPosition(-2.0); // on button up, set servo to max range
//         }
//         else {
//             man.stupidServo(0).setPosition(0); // default center position
//             //man.motor(rb::MotorId::M4).speed(0);
//             //man.motor(rb::MotorId::M1).speed(0);
//         }
//     }
}






void loop(){
  //Serial.print("L: ");
}