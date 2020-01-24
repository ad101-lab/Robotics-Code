/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\adick                                            */
/*    Created:      Thu Oct 31 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

vex::brain Brain;
vex::controller Controller;
vex::competition Competition;
vex::motor frontRight(vex::PORT1, false);
vex::motor frontLeft(vex::PORT2, false);
vex::motor Right(vex::PORT4, false);
vex::motor Left(vex::PORT5, false);

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  while(1){
    frontRight.spin(vex::directionType::fwd, (Controller.Axis3.value()-Controller.Axis4.value()-Controller.Axis1.value()), vex::velocityUnits::pct);
    frontLeft.spin(vex::directionType::fwd, (Controller.Axis3.value()+Controller.Axis4.value()+Controller.Axis1.value()), vex::velocityUnits::pct);
    Right.spin(vex::directionType::fwd, (Controller.Axis3.value()+Controller.Axis4.value()-Controller.Axis1.value()), vex::velocityUnits::pct);
    Left.spin(vex::directionType::fwd, (Controller.Axis3.value()-Controller.Axis4.value()+Controller.Axis1.value()), vex::velocityUnits::pct);
    vex::task::sleep(20);
  }
}
