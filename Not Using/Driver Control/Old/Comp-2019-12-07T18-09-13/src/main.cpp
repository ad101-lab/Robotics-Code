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
vex::brain Brain;
vex::bumper rampBumper        = vex::bumper(Brain.ThreeWirePort.G);
vex::bumper rampBumperForward = vex::bumper(Brain.ThreeWirePort.H);
motor rightFWD = motor(PORT20, ratio18_1, true);
motor leftFWD = motor(PORT10, ratio18_1, false);
motor rightBack = motor(PORT11, ratio18_1, true);
motor leftBack = motor(PORT1, ratio18_1, false);
motor cubeRamp = motor(PORT6, ratio18_1, false);
motor intakeRight = motor(PORT5, ratio6_1, true);
motor intakeLeft = motor(PORT7, ratio6_1, false);
controller Controller1        = vex::controller(primary);
int cubeRampValue;
int intakeValue;
int cms;

void moveForward(int cm, int speed){
  leftFWD.setVelocity(speed, percent);
  rightFWD.setVelocity(speed, percent);
  leftBack.setVelocity(speed, percent);
  rightBack.setVelocity(speed, percent);
  cms = (cm/32) * 360;
  leftFWD.spinFor(cms, degrees, false);
  rightFWD.spinFor(cms, degrees, false);
  leftBack.spinFor(cms, degrees, false);
  rightBack.spinFor(cms, degrees, false);
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
  cms = (cm/32) * -360;
  leftFWD.spinFor(cms, degrees, false);
  rightFWD.spinFor(cms, degrees, false);
  leftBack.spinFor(cms, degrees, false);
  rightBack.spinFor(cms, degrees, false);
  leftFWD.setVelocity(100, percent);
  rightFWD.setVelocity(100, percent);
  leftBack.setVelocity(100, percent);
  rightBack.setVelocity(100, percent);

}

void cubeRampVertical (bool degree){
  if(degree == true){
    cubeRamp.spin(forward);
    waitUntil(rampBumper.pressing() == true);
  }else if (degree == false) {
    cubeRamp.spinFor(1170, degrees, false);
    waitUntil(rampBumperForward.pressing() == true);
  }

}

void intake (int onOff, int speed){
  intakeRight.setVelocity(speed, percent);
  intakeLeft.setVelocity(speed, percent); 
  if( onOff == 1){
    intakeRight.spin(reverse);
    intakeLeft.spin(reverse);
  }else if( onOff == 2){
    intakeRight.spin(forward);
    intakeLeft.spin(forward);
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

void motorHold(bool holding){
  if(holding == true){
  intakeRight.setStopping(hold);
  intakeLeft.setStopping(hold);
  cubeRamp.setStopping(hold);
  leftFWD.setStopping(hold);
  rightFWD.setStopping(hold);
  leftBack.setStopping(hold);
  rightBack.setStopping(hold);
 }else{
  intakeRight.setStopping(coast);
  intakeLeft.setStopping(coast);
  cubeRamp.setStopping(coast);
  leftFWD.setStopping(coast);
  rightFWD.setStopping(coast);
  leftBack.setStopping(coast);
  rightBack.setStopping(coast);
 }

}

void pre_auton(void) {
   
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*-----------------------------------------------------------alex is a nerd----------------*/
/*                                                            alex is a nerd               */
/*                              Autonomous Task                 alex is a nerd             */
/*                                                                alex is a nerd           */
/*  This task is used to control your robot during the autonomous palex is a nerdhase of   */
/*  a VEX Competition.                                              alex is a nerd          */
/*                                                                   alex is a nerd        */
/*  You must modify the code to add your own robot specific commands halex is a nerdere.   */
/*---------------------------------------------------------------------alex is a nerd------*/

void autonomous(void) {
  motorHold(true);
  intakeValue = -200;
  intakeLeft.spin(forward, intakeValue , vex::velocityUnits::rpm);
  intakeRight.spin(forward, intakeValue, vex::velocityUnits::rpm);
  wait(3, seconds);
  intakeLeft.stop();
  intakeRight.stop();//thanks
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
    cubeRamp.setStopping(hold);
    intakeLeft.setStopping(hold);
    intakeRight.setStopping(hold);
    rightFWD.spin(forward, Controller1.Axis2.position() , vex::velocityUnits::pct);
    leftFWD.spin(forward, Controller1.Axis3.position() , vex::velocityUnits::pct);
    rightBack.spin(forward, Controller1.Axis2.position() , vex::velocityUnits::pct);
    leftBack.spin(forward, Controller1.Axis3.position() , vex::velocityUnits::pct);
    if (Controller1.ButtonL1.pressing() and !(rampBumper.pressing())){
      cubeRampValue = 200;
    } else if (Controller1.ButtonL2.pressing() and !(rampBumperForward.pressing())) {
      cubeRampValue = -200;
    } else {
      cubeRampValue = 0;
    }
    cubeRamp.spin(forward, cubeRampValue , vex::velocityUnits::rpm);
    if (Controller1.ButtonR1.pressing()){
      intakeValue = 100;
    } else if (Controller1.ButtonR2.pressing()) {
      intakeValue = -300;
    } else {
      intakeValue = 0;
    }
    intakeLeft.spin(forward, intakeValue , vex::velocityUnits::rpm);
    intakeRight.spin(forward, intakeValue , vex::velocityUnits::rpm);
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
