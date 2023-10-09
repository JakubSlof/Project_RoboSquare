#include <Arduino.h>
#include "SmartServoBus.hpp"
#include <robotka.h>


#define DEAFULT_WHEEL_DIAMETER 62 //deafult wheel diameter
#define DEAFULT_WHEEL_BASE 120 //deafult wheel base
 


class RoboSquare
{
  public:
const int wheel_diameter = DEAFULT_WHEEL_DIAMETER; //wheel diameter of robot 
const int wheel_base = DEAFULT_WHEEL_BASE; //wheel base of robot

//checks battery percent and turn on leds
void check_battery();
/**
 * \brief Turns robot on place in given degrees. 
 *
 * \param degrees degrees you want robot to turn
 * \param speed speed of turn 
 */
void turn(int degrees, int speed);
}; 


