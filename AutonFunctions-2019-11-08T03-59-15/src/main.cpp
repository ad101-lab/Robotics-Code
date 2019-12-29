/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\adick                                            */
/*    Created:      Thu Nov 07 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;
gyro TurnGyroSmart = gyro(Brain.ThreeWirePort.D);
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
  leftFWD.spinFor(cm/32*-360, degrees, true);
  rightFWD.spinFor(cm/32*-360, degrees, true);
  leftBack.spinFor(cm/32*-360, degrees, true);
  rightBack.spinFor(cm/32*-360, degrees, true);
  
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
