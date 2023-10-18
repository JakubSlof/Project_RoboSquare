#ifndef ROBOSQUARE
#include <Arduino.h>
#include "SmartServoBus.hpp"
#include <robotka.h>

#define MOTORS_GEAR_RATIO 3.64 //gear ratio of used motors (for accurate distance measuring)
#define DEAFULT_WHEEL_DIAMETER 70 //deafult wheel diameter
#define DEAFULT_WHEEL_BASE 170 //deafult wheel base
#define AC 3.64 //constant to gear ratio 


class RoboSquare
{
  public:
const int wheel_diameter = DEAFULT_WHEEL_DIAMETER; //wheel diameter of robot 
const int wheel_base = DEAFULT_WHEEL_BASE; //wheel base of robot
const float gears_ratio = MOTORS_GEAR_RATIO; //gears ratio for precise distance measurement

//checks battery percent and turn on leds
void check_battery();
/**
 * \brief Turns robot on place in given degrees. 
 *
 * \param angle degrees you want robot to turn
 * \param speed speed of turn 
 */
void turn(double angle, int speed);

/**
 * \brief Turns robot in arc.
 *
 * \param angle degrees you want robot to turn
 * \param speed speed of turn 
 * \param radius radius of the arc (outer wheel)
 * \param side "right" or "left" 
 * \warning radius must be bigger than robot wheel base 
 */
void arc(double angle, double radius, int speed,std::string side);

/**
 * \brief Moves robot forward.
 *
 * \param speed speed of robot
 * \param lenght how far should robot go in mm
 */
void forward(double lenght, int speed);

/**
 * \brief Reads data from raspberry pi.
 *
 * 
 */
void receve_data();

  private:
double degrees;
int speed;
double angle;
double radius;
std::string side;
}; 
#endif

