#include<Arduino.h>
#include "SmartServoBus.hpp"
#include"RBCX.h"



static lx16a::SmartServoBus servoBus;
auto& man = rb::Manager::get(); //needs to be there to work man.sometning
//r motor 3
// l motor 2
double mm_to_ticks = 0.215;
int wheel_base = 150;
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
struct arm
{
  void Drivemode(){
    //puts the arm in drive mode
    //stupid servos position is from<-2;2>
    man.stupidServo(0).setPosition(0);
    man.stupidServo(1).setPosition(2); //or -2 needs to be tested
    man.stupidServo(2).setPosition(2); //or -2 needs to be tested
  }
  void GrabBaterry(){
    man.stupidServo(0).setPosition(2);
    man.stupidServo(1).setPosition(0.5); //just random needs to be tested
    man.stupidServo(2).setPosition(0);
  }
  void ReleaseBattery() {
    man.stupidServo(0).setPosition(-2);
    man.stupidServo(1).setPosition(1); //just random needs to be tested
    man.stupidServo(2).setPosition(2);//or -2 needs to be tested
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
       //man.motor(rb::MotorId::M1).speed(0);
       //man.motor(rb::MotorId::M4).speed(0);
}
void Straight(int speed, int distance){
  auto& man = rb::Manager::get(); 
man.motor(rb::MotorId::M1).setCurrentPosition(0);
man.motor(rb::MotorId::M4).setCurrentPosition(0);
   int ticks_M1 = 0;
   int ticks_M4 = 0;
   distance = distance/mm_to_ticks;
   Serial.println(distance);
  while(ticks_M1 < distance){//(ticks_M1 < distance)&& (ticks_M4 < distance)
    man.motor(rb::MotorId::M1).speed(-speed);
    man.motor(rb::MotorId::M4).speed(speed);
    man.motor(rb::MotorId::M4).requestInfo([&ticks_M4](rb::Motor& info) {
            //Serial.println( info.position());
            ticks_M4 =  info.position();
        });
        man.motor(rb::MotorId::M1).requestInfo([&ticks_M1](rb::Motor& info) {
            //Serial.println( -info.position());
            ticks_M1 =   -info.position();
        });

    delay(10);
  }
  //man.motor(rb::MotorId::M1).speed(0);
  //man.motor(rb::MotorId::M4).speed(0);
  printf("niga");

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
       //man.motor(rb::MotorId::M4).speed(0);
       //man.motor(rb::MotorId::M1).speed(0);
      
} 
//test????
//needs to start from at least 100 speed_from!!!!!
void Acceleration(int speed_from, int speed_to, int distance_mm){
  man.motor(rb::MotorId::M1).setCurrentPosition(0);
man.motor(rb::MotorId::M4).setCurrentPosition(0);
     double distance_ticks = distance_mm / mm_to_ticks;
     double acc_const = speed_to/distance_ticks;
     int ticks_M1 = 0;
     int ticks_M4 = 0;
     int error = 0;
     while((ticks_M1 < distance_ticks) && (ticks_M4 < distance_ticks)){
      error = 10*(ticks_M1 - ticks_M4);
      man.motor(rb::MotorId::M1).speed(-(acc_const*ticks_M1+speed_from-error));
        man.motor(rb::MotorId::M4).speed(acc_const*ticks_M4+speed_from+error); 
        man.motor(rb::MotorId::M4).requestInfo([&ticks_M4](rb::Motor& info) {
            //printf("M4: position:%d\n", info.position());
            ticks_M4 = info.position();
        });
        man.motor(rb::MotorId::M1).requestInfo([&ticks_M1](rb::Motor& info) {
            //printf("M1: position:%d\n", info.position());
            ticks_M1 = -info.position();
        });

      delay(10);
     }
}
void measuring(){
  int ticks_M4 = 0;
  while (true)
  {
     man.motor(rb::MotorId::M4).requestInfo([&ticks_M4](rb::Motor& info) {
            Serial.println( info.position());
            ticks_M4 = info.position();
        });
        delay(100);
  }
  
}
void Turn (int angle){
    man.motor(rb::MotorId::M1).setCurrentPosition(0);
man.motor(rb::MotorId::M4).setCurrentPosition(0);
  int ticks_M1 =0;
  int ticks_M4=0;
  int distance = ((PI*wheel_base)/360)*angle/mm_to_ticks;
  while (distance > ticks_M4)
  {
        man.motor(rb::MotorId::M1).speed(1000);
        man.motor(rb::MotorId::M4).speed(1000); 
        man.motor(rb::MotorId::M4).requestInfo([&ticks_M4](rb::Motor& info) {
            //printf("M4: position:%d\n", info.position());
            ticks_M4 = info.position();
        });
        man.motor(rb::MotorId::M1).requestInfo([&ticks_M1](rb::Motor& info) {
            //printf("M1: position:%d\n", info.position());
            ticks_M1 = -info.position();
        });

      delay(10);
  }
  man.motor(rb::MotorId::M4).speed(0);
  man.motor(rb::MotorId::M1).speed(0);

  
}
void setup() {
  // Get the manager instance as a singleton
  auto& man = rb::Manager::get();
  // Install the manager
  man.install();
  struct klepeto Klepeto_L, Klepeto_R;
  struct arm arm;
  
  // Set the serial communication baud rate to 115200
  Serial.begin(115200);
  Serial.println(man.battery().voltageMv());
  ///////////////////////////////////////////////
  servoBus.begin(1, UART_NUM_1, GPIO_NUM_27);
  servoBus.setId(0);
    while (true) {
        printf("GetId: %d\n", servoBus.getId());
        delay(1000);
    }






//////////////////////////////
  //starting button
  while (true)
  {
    if (man.buttons().up()==1)
    {
      break;
    }
    
    delay(10);
  }
  delay(500);

//functions in testing
arm.Drivemode();
delay(500);
//////////////////////////////////////////
// int distance;
// while (true)
// {
//   distance = man.ultrasound(0).measure();
//   Serial.println(distance);
//   if (man.buttons().up()==1)
//     {
//       break;
//     }
//   delay(100);
// }


//   while (true)
//   {
//     if (man.buttons().up()==1)
//     {
//       break;
//     }
    
//     delay(10);
//   }
//   delay(500);









////////////////////////////////////////
//Straight(3200, 1000);
  //esko == pos1
  Acceleration(300,32000,400); //default 500
  arc_right(180, 180);
  //Straight(32000, 100);
  arc_left(165, 200);
  Straight(32000, 300);
  Acceleration(32000,0,100);
  man.motor(rb::MotorId::M4).speed(0);
  man.motor(rb::MotorId::M1).speed(0);
  //go to pos2
  delay(2000);
  ////////////////
  Turn(180);
  Acceleration(1000,32000,100);
  Straight(32000, 300);
  arc_right(165, 200);
  Straight(32000, 300);
  arc_left(180, 180);
  Straight(32000, 300);
  


  /////////////////////////////////////////
//   Acceleration(500,32000,400);
//   Acceleration(32000,500,400);
//   man.motor(rb::MotorId::M4).speed(0);
//   man.motor(rb::MotorId::M1).speed(0);
//   delay(100);
//   Turn(165);
//   delay(1000);
//   int i = 0;
// while (i<300)
// {
//   i=i+1;
//   man.motor(rb::MotorId::M4).speed(-500);
//   man.motor(rb::MotorId::M1).speed(500);
//    delay(10);
// }
//   man.motor(rb::MotorId::M4).speed(0);
//   man.motor(rb::MotorId::M1).speed(0);



  /////////////////////////////////////////////////////////////////////////////////////
  //measuring();
  //test();
  //delay(10000);
  //Straight(1000, 2000);
  //man.stupidServo(0).setPosition(1);
  //
 // Serial.println("hovno");
  //
  //
  //

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