#ifndef ROBOSQUARE
#include <Arduino.h>
#include "SmartServoBus.hpp"
#include <robotka.h>


#define DEAFULT_WHEEL_DIAMETER 70 //deafult wheel diameter
#define DEAFULT_WHEEL_BASE 170 //deafult wheel base
#define AC 3.64 //constant to gear ratio 


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
void turn(double degrees, int speed);

/**
 * \brief Turns robot in arc.
 *
 * \param degrees degrees you want robot to turn
 * \param speed speed of turn 
 * \param radius radius of the arc (outer wheel)
 */
void arc(double angle, int radius, int speed,std::string side);

/**
 * \brief Moves robot forward.
 *
 * \param speed speed of robot
 * \param lenght lenght how far should robot go 
 */
void forward(int lenght, int speed);

  private:
int degrees;
int speed;
int angle;
int radius;
std::string side;
}; 
#endif

