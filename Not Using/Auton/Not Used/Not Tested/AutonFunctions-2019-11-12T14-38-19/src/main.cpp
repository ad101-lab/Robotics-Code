/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\adick                                            */
/*    Created:      Thu Nov 07 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// TurnGyroSmart        gyro          D               
// leftFWD              motor         1               
// rightFWD             motor         2               
// leftBack             motor         3               
// rightBack            motor         4               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;
vex::gyro TurnGyroSmart = gyro(Brain.ThreeWirePort.D);
void MoveForward(int cm){
  leftFWD.spinFor(cm/32*360, degrees, false);
  rightFWD.spinFor(cm/32*360, degrees, false);
  leftBack.spinFor(cm/32*360, degrees, false);
  rightBack.spinFor(cm/32*360, degrees, false);
} 

void MoveBackwards(int cm){
  leftFWD.spinFor(cm/32*-360, degrees, false);
  rightFWD.spinFor(cm/32*-360, degrees, false);
  leftBack.spinFor(cm/32*-360, degrees, false);
  rightBack.spinFor(cm/32*-360, degrees, false);
}

void TurnRight(int degrees){
  TurnGyroSmart.setHeading(0,degrees);
  while (TurnGyroSmart.heading() < 90 ){
    leftFWD.spinFor(-10, vex::rotationUnits::degrees, false);
    rightFWD.spinFor(10, degrees, false);
    leftBack.spinFor(-10, degrees, false);
    rightBack.spinFor(10, degrees, false);
  }
}

void TurnLeft(int degrees){
  leftFWD.spinFor(cm/32*-360, degrees, false);
  rightFWD.spinFor(cm/32*-360, degrees, false);
  leftBack.spinFor(cm/32*-360, degrees, false);
  rightBack.spinFor(cm/32*-360, degrees, false);
}

void intakeUp (int degrees){

}

void intakeDown (int degrees){

}

void cubeRampUp (int degrees){

}

void cubeRampDown (int degrees){

}

void intake (int onOff){

}


int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
}
