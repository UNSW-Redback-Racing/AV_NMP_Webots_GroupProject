// File:          NMP_Manual_Controller.cpp
// Date:          06/09/2021
// Description:   Controller to Manual move the robot
// Author:        Stephanie Liaw
// Modifications:


#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/InertialUnit.hpp>
#include <webots/Lidar.hpp>
#include <webots/Keyboard.hpp>
#include <webots/Camera.hpp>

#include <iostream>
#include <array>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>

using namespace webots;

#define TIME_STEP 32
#define INPUT_SPEED 6.4

void Move(const int key, webots::Motor *front_left_motor, webots::Motor *back_left_motor, webots::Motor *front_right_motor, webots::Motor *back_right_motor);
void moveForward(webots::Motor *front_left_motor, webots::Motor *back_left_motor, webots::Motor *front_right_motor, webots::Motor *back_right_motor);
void moveBackward(webots::Motor *front_left_motor, webots::Motor *back_left_motor, webots::Motor *front_right_motor, webots::Motor *back_right_motor);
void turnRight(webots::Motor *front_left_motor, webots::Motor *back_left_motor, webots::Motor *front_right_motor, webots::Motor *back_right_motor);
void turnLeft(webots::Motor *front_left_motor, webots::Motor *back_left_motor, webots::Motor *front_right_motor, webots::Motor *back_right_motor);
void stop(webots::Motor *front_left_motor, webots::Motor *back_left_motor, webots::Motor *front_right_motor, webots::Motor *back_right_motor);

int main(int argc, char **argv) {
  // create the Robot instance.
  Robot *robot = new Robot();

  // get the time step of the current world.
  int timeStep = (int)robot->getBasicTimeStep();

  // Get the motors and keyboard instances
  Motor *front_left_motor = robot->getMotor("front left wheel");
  Motor *back_left_motor = robot->getMotor("back left wheel");
  Motor *front_right_motor = robot->getMotor("front right wheel");
  Motor *back_right_motor = robot->getMotor("back right wheel");
  Keyboard *keyboard = robot->getKeyboard();
  keyboard->enable(timeStep);


  // Initialise the position and velocity of the motors
  front_left_motor->setPosition(std::numeric_limits<double>::infinity());
  back_left_motor->setPosition(std::numeric_limits<double>::infinity());
  front_right_motor->setPosition(std::numeric_limits<double>::infinity());
  back_right_motor->setPosition(std::numeric_limits<double>::infinity());
  front_left_motor->setVelocity(0);
  back_left_motor->setVelocity(0);
  front_right_motor->setVelocity(0);
  back_right_motor->setVelocity(0);

  // Initialise value of the key pressed
  int key {-1};

  // Main loop:
  // - perform simulation steps until Webots is stopping the controller
  while (robot->step(timeStep) != -1) {
      const int prevKey = key;
      key = keyboard->getKey();
      if(key != prevKey){
          front_left_motor->setVelocity(0);
          back_left_motor->setVelocity(0);
          front_right_motor->setVelocity(0);
          back_right_motor->setVelocity(0);
          Move(key, front_left_motor, back_left_motor, front_right_motor, back_right_motor);
        }  
  };

  delete robot;
  return 0;
}
//Settng keys to move the robot manually
void Move(const int key, webots::Motor *front_left_motor, webots::Motor *back_left_motor, webots::Motor *front_right_motor, webots::Motor *back_right_motor){
    switch(key){
        case Keyboard::UP:
            moveForward(front_left_motor, back_left_motor, front_right_motor, back_right_motor);
            break;
        case Keyboard::DOWN:
            moveBackward(front_left_motor, back_left_motor, front_right_motor, back_right_motor);
            break;
        case Keyboard::LEFT:
            turnLeft(front_left_motor, back_left_motor, front_right_motor, back_right_motor);
            break;
        case Keyboard::RIGHT:
            turnRight(front_left_motor, back_left_motor, front_right_motor, back_right_motor);
            break;
        case ' ':
            stop(front_left_motor, back_left_motor, front_right_motor, back_right_motor);
            break;

    }
}

void moveForward(webots::Motor *front_left_motor, webots::Motor *back_left_motor, webots::Motor *front_right_motor, webots::Motor *back_right_motor){
  front_left_motor->setVelocity(INPUT_SPEED);
  back_left_motor->setVelocity(INPUT_SPEED);
  front_right_motor->setVelocity(INPUT_SPEED);
  back_right_motor->setVelocity(INPUT_SPEED);

}

void moveBackward(webots::Motor *front_left_motor, webots::Motor *back_left_motor, webots::Motor *front_right_motor, webots::Motor *back_right_motor){
  front_left_motor->setVelocity(-1*INPUT_SPEED);
  back_left_motor->setVelocity(-1*INPUT_SPEED);
  front_right_motor->setVelocity(-1*INPUT_SPEED);
  back_right_motor->setVelocity(-1*INPUT_SPEED);
}

void turnRight(webots::Motor *front_left_motor, webots::Motor *back_left_motor, webots::Motor *front_right_motor, webots::Motor *back_right_motor){
  front_left_motor->setVelocity(INPUT_SPEED);
  back_left_motor->setVelocity(INPUT_SPEED);
  front_right_motor->setVelocity(0.5*INPUT_SPEED);
  back_right_motor->setVelocity(0.5*INPUT_SPEED); 
}

void turnLeft(webots::Motor *front_left_motor, webots::Motor *back_left_motor, webots::Motor *front_right_motor, webots::Motor *back_right_motor){
  front_left_motor->setVelocity(0.5*INPUT_SPEED);
  back_left_motor->setVelocity(0.5*INPUT_SPEED);
  front_right_motor->setVelocity(INPUT_SPEED);
  back_right_motor->setVelocity(INPUT_SPEED);
}
void stop(webots::Motor *front_left_motor, webots::Motor *back_left_motor, webots::Motor *front_right_motor, webots::Motor *back_right_motor){
  front_left_motor->setVelocity(0.0);
  back_left_motor->setVelocity(0.0);
  front_right_motor->setVelocity(0.0);
  back_right_motor->setVelocity(0.0);
}