/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\dickha.alexan27                                  */
/*    Created:      Thu Nov 07 2019                                           */ 
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// cubeRamp             motor         2               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;
vex::brain Brain;
vex::gyro TurnGyroSmart = gyro(Brain.ThreeWirePort.D);
vex::motor leftFWD           = vex::motor( vex::PORT11, true);
vex::motor leftBack          = vex::motor( vex::PORT20 );
vex::motor rightFWD          = vex::motor( vex::PORT1 );
vex::motor rightBack         = vex::motor( vex::PORT10, true );
vex::motor CubeRamp          = vex::motor( vex::PORT2);
vex::motor intakeRight       = vex::motor( vex::PORT3);
vex::motor intakeLeft        = vex::motor( vex::PORT4);
vex::controller controller1  = vex::controller();

void moveForward(int cm){
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

void TurnRight(int rotations){
  TurnGyroSmart.setHeading(0,degrees);
  while (TurnGyroSmart.heading() < 90 ){
    leftFWD.spinFor(-10, degrees, false);
    rightFWD.spinFor(10, degrees, false);
    leftBack.spinFor(-10, degrees, false);
    rightBack.spinFor(10, degrees, false);
  }
}

void TurnLeft(int rotations){
  TurnGyroSmart.setHeading(0,degrees);
  while (TurnGyroSmart.heading() < 90 ){
    leftFWD.spinFor(10, degrees, false);
    rightFWD.spinFor(-10, degrees, false);
    leftBack.spinFor(10, degrees, false);
    rightBack.spinFor(-10, degrees, false);
  }
}

void cubeRampUp (){
  CubeRamp.spinFor(2400, degrees, false);
}

void cubeRampDown (){
  CubeRamp.spinFor(2000, degrees, false);
}

void intake (bool onOff){
  if( onOff == true){
    intakeRight.spin(forward);
    intakeLeft.spin(forward);
  }else if( onOff == false){
    intakeRight.spin(reverse);
    intakeLeft.spin(reverse);
  } else {
    intakeRight.spin(forward);
    intakeLeft.spin(forward);
  }
}

void motorWait(){
  waitUntil(intakeRight.isDone());
  waitUntil(intakeLeft.isDone());
  waitUntil(CubeRamp.isDone());
  waitUntil(leftFWD.isDone());
  waitUntil(rightFWD.isDone());
  waitUntil(leftBack.isDone());
  waitUntil(rightBack.isDone());
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  moveForward(100);
  intake(true);
  moveForward(200);
  intake(false)
  +
}
