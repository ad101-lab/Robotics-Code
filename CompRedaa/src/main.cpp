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

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/
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
vex::gyro TurnGyroSmart      = vex::gyro(Brain.ThreeWirePort.D);
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
    CubeRamp.spinFor(1170, degrees, true);
  }else if (degree == false) {
  CubeRamp.spinFor(1170, degrees, false);
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

void pre_auton(void) {
  cubeRamp.setVelocity(50, percent);
  vexcodeInit();
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
    }
    if(controller1.ButtonL1.pressing()){
      intakeLeft.spin(forward);
      intakeRight.spin(forward);
    } else if(controller1.ButtonL2.pressing()){
      intakeLeft.spin(reverse);
      intakeRight.spin(reverse);
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
