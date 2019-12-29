/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\dickha.alexan27                                  */
/*    Created:      Wed Nov 20 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// rightFWD             motor         20              
// leftFWD              motor         10              
// rightBack            motor         11              
// leftBack             motor         1               
// cubeRamp             motor         6               
// intakeRight          motor         5               
// intakeLeft           motor         7               
// BumperH              bumper        H               
// BumperG              bumper        G               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include <vex.h>

using namespace vex;
brain Brain;
controller Controller1 = vex::controller();
motor rightFWD = motor(PORT20, ratio18_1, true);
motor leftFWD = motor(PORT10, ratio18_1, false);
motor rightBack = motor(PORT11, ratio18_1, true);
motor leftBack = motor(PORT1, ratio18_1, false);
motor cubeRamp = motor(PORT6, ratio18_1, false);
motor intakeRight = motor(PORT5, ratio6_1, true);
motor intakeLeft = motor(PORT7, ratio6_1, false);
bumper BumperH = bumper(Brain.ThreeWirePort.H);
bumper BumperG = bumper(Brain.ThreeWirePort.G);
int cubeRampValue;
int intakeValue;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  while(1){
    cubeRamp.setStopping(hold);
    intakeLeft.setStopping(hold);
    intakeRight.setStopping(hold);
    rightFWD.spin(forward, Controller1.Axis2.position() , vex::velocityUnits::pct);
    leftFWD.spin(forward, Controller1.Axis3.position() , vex::velocityUnits::pct);
    rightBack.spin(forward, Controller1.Axis2.position() , vex::velocityUnits::pct);
    leftBack.spin(forward, Controller1.Axis3.position() , vex::velocityUnits::pct);
    if (Controller1.ButtonL1.pressing() and !(BumperG.pressing())){
      cubeRampValue = 200;
    } else if (Controller1.ButtonL2.pressing() and !(BumperH.pressing())) {
      cubeRampValue = -200;
    } else {
      cubeRampValue = 0;
    }
    cubeRamp.spin(forward, cubeRampValue , vex::velocityUnits::rpm);
    if (Controller1.ButtonR1.pressing()){
      intakeValue = 100;
    } else if (Controller1.ButtonR2.pressing()) {
      intakeValue = -200;
    } else {
      intakeValue = 0;
    }
    intakeLeft.spin(forward, intakeValue , vex::velocityUnits::rpm);
    intakeRight.spin(forward, intakeValue , vex::velocityUnits::rpm);

  }
}
