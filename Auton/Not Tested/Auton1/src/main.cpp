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
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;



vex::brain Brain;
vex::gyro TurnGyroSmart = gyro(Brain.ThreeWirePort.D);
vex::motor leftFWD           = vex::motor( vex::PORT11, ratio18_1, true);
vex::motor leftBack          = vex::motor( vex::PORT20, ratio18_1, false );
vex::motor rightFWD          = vex::motor( vex::PORT1, ratio18_1, false );
vex::motor rightBack         = vex::motor( vex::PORT10, ratio18_1, true );
vex::motor CubeRamp          = vex::motor( vex::PORT2, ratio18_1, false);
vex::motor intakeRight       = vex::motor( vex::PORT3, ratio36_1, false);
vex::motor intakeLeft        = vex::motor( vex::PORT4, ratio36_1, false);
vex::motor cubeRamp          = vex::motor(PORT2, ratio6_1, false);
vex::controller controller1  = vex::controller();



void moveForward(int cm, int speed){
  leftFWD.setVelocity(speed, percent);
  rightFWD.setVelocity(speed, percent);
  leftBack.setVelocity(speed, percent);
  rightBack.setVelocity(speed, percent);
  leftFWD.spinFor(cm/32*360, degrees, false);
  rightFWD.spinFor(cm/32*360, degrees, false);
  leftBack.spinFor(cm/32*360, degrees, false);
  rightBack.spinFor(cm/32*360, degrees, false);
  leftFWD.setVelocity(100, percent);
  rightFWD.setVelocity(100, percent);
  leftBack.setVelocity(100, percent);
  rightBack.setVelocity(100, percent);

} 

void moveBackwards(int cm, int speed){
  leftFWD.setVelocity(speed, percent);
  rightFWD.setVelocity(speed, percent);
  leftBack.setVelocity(speed, percent);
  rightBack.setVelocity(speed, percent);
  leftFWD.spinFor(cm/32*-360, degrees, false);
  rightFWD.spinFor(cm/32*-360, degrees, false);
  leftBack.spinFor(cm/32*-360, degrees, false);
  rightBack.spinFor(cm/32*-360, degrees, false);
  leftFWD.setVelocity(100, percent);
  rightFWD.setVelocity(100, percent);
  leftBack.setVelocity(100, percent);
  rightBack.setVelocity(100, percent);

}

void turnRight(int rotations){
  TurnGyroSmart.setHeading(0,degrees);
  while (TurnGyroSmart.heading() < 90 ){
    leftFWD.spinFor(-10, degrees, false);
    rightFWD.spinFor(10, degrees, false);
    leftBack.spinFor(-10, degrees, false);
    rightBack.spinFor(10, degrees, false);
  }

}

void turnLeft(int rotations){
  TurnGyroSmart.setHeading(0,degrees);
  while (TurnGyroSmart.heading() < 90 ){
    leftFWD.spinFor(10, degrees, false);
    rightFWD.spinFor(-10, degrees, false);
    leftBack.spinFor(10, degrees, false);
    rightBack.spinFor(-10, degrees, false);
  }

}

void cubeRampVertical (bool degree){
  if(degree == true){
    CubeRamp.spinFor(2400, degrees, true);
  }else if (degree == false) {
  CubeRamp.spinFor(2000, degrees, false);
  }

}

void intake (int onOff, int speed){
  intakeRight.setVelocity(speed, percent);
  intakeLeft.setVelocity(speed, percent); 
  if( onOff == 1){
    intakeRight.spin(forward);
    intakeLeft.spin(forward);
  }else if( onOff == 2){
    intakeRight.spin(reverse);
    intakeLeft.spin(reverse);
  } else if( onOff == 0 ) {
    intakeRight.setStopping(brake);
    intakeLeft.setStopping(brake);
  }
  intakeRight.setVelocity(100, percent);
  intakeLeft.setVelocity(100, percent); 

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
  moveForward(140, 100);
  intake(1, 100);
  motorWait();
  intake(0, 100);
  moveBackwards(140, 100);
  motorWait();
  turnRight(90);
  motorWait();
  moveForward(127, 100);
  motorWait();
  cubeRampVertical(true);
  intake(2, 20);
  moveBackwards(67, 20);
  cubeRampVertical(false);
  turnLeft(90);
  intake(1, 100);
  moveForward(140, 100);
  intake(0, 100);
}
