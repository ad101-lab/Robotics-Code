/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;


#include "vex.h"


using namespace vex;


//vex::brain Brain;
vex::gyro TurnGyroSmart       = vex::gyro(Brain.ThreeWirePort.D);
vex::bumper rampBumper        = vex::bumper(Brain.ThreeWirePort.C);
vex::bumper rampBumperForward = vex::bumper(Brain.ThreeWirePort.B);
vex::motor leftFWD            = vex::motor( vex::PORT11, ratio18_1, true);
vex::motor leftBack           = vex::motor( vex::PORT20, ratio18_1, false );
vex::motor rightFWD           = vex::motor( vex::PORT1, ratio18_1, false );
vex::motor rightBack          = vex::motor( vex::PORT10, ratio18_1, true );
vex::motor cubeRamp           = vex::motor( vex::PORT2, ratio36_1, false);
vex::motor intakeRight        = vex::motor( vex::PORT3, ratio6_1, false);
vex::motor intakeLeft         = vex::motor( vex::PORT4, ratio6_1, false);
vex::controller controller1   = vex::controller();



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
  leftFWD.spin(forward);
  leftBack.spin(forward);
  rightBack.spin(reverse);
  rightFWD.spin(reverse);
  waitUntil(TurnGyroSmart.heading() > rotations);

}

void turnLeft(int rotations){
  TurnGyroSmart.setHeading(0,degrees);
  leftFWD.spin(reverse);
  leftBack.spin(reverse);
  rightBack.spin(forward);
  rightFWD.spin(forward);
  waitUntil(TurnGyroSmart.heading() < rotations);

}

void cubeRampVertical (bool degree){
  if(degree == true){
    cubeRamp.spin(forward);
    waitUntil(rampBumper.pressing() == true);
    cubeRamp.setStopping(brake);
  }else if (degree == false) {
    cubeRamp.spin(forward);
    waitUntil(rampBumperForward.pressing() == true);
    cubeRamp.setStopping(brake);
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
    intakeRight.setStopping(hold);
    intakeLeft.setStopping(hold);
  }
  intakeRight.setVelocity(100, percent);
  intakeLeft.setVelocity(100, percent); 

}

void motorWait(){
  waitUntil(intakeRight.isDone());
  waitUntil(intakeLeft.isDone());
  waitUntil(cubeRamp.isDone());
  waitUntil(leftFWD.isDone());
  waitUntil(rightFWD.isDone());
  waitUntil(leftBack.isDone());
  waitUntil(rightBack.isDone());

}

void motorHold(){
  intakeRight.setStopping(hold);
  intakeLeft.setStopping(hold);
  cubeRamp.setStopping(hold);
  leftFWD.setStopping(hold);
  rightFWD.setStopping(hold);
  leftBack.setStopping(hold);
  rightBack.setStopping(hold);
}

void pre_auton(void) {
  cubeRamp.setVelocity(50, percent);
  vexcodeInit();
  motorHold();
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
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

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    leftFWD.spin(vex::directionType::fwd, controller1.Axis3.value(), vex::velocityUnits::pct);
    rightFWD.spin(vex::directionType::fwd, controller1.Axis2.value(), vex::velocityUnits::pct);
    leftBack.spin(vex::directionType::fwd, controller1.Axis3.value(), vex::velocityUnits::pct);
    rightBack.spin(vex::directionType::fwd, controller1.Axis2.value(), vex::velocityUnits::pct);
    if((controller1.ButtonR1.pressing()) & (cubeRamp.position(degrees) < 1170)){
      cubeRamp.spin(forward);
    }else if((controller1.ButtonR2.pressing()) & (cubeRamp.position(degrees) > 0)){
      cubeRamp.spin(reverse);
    }else {
      cubeRamp.setStopping(hold);
    }
    if(controller1.ButtonL1.pressing()){
      intake(1, 100);
    } else if(controller1.ButtonL2.pressing()){
      intake(2, 100);
    }else {
      intake(0, 100);
    }
    wait(20, msec); // Sleep the task for a short amount of time to
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
