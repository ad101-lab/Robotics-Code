#include "robot-config.h"
#include "vex.h"
using namespace vex;

void pre_auton(void) {
  motorHold(true);
}

void autonomous(void) {
  intake(100);
  oneBarUp(45, 100, true);
  oneBarUp(-45, 100, true);
  //moveForward(, int speed)
}

void usercontrol(void) {//User Control
  while (1) {
    rightFWD.spin(forward, (Controller1.Axis2.position()/ turnValue)/baseRPM , vex::velocityUnits::pct);//Tank Drive controls
    leftFWD.spin(forward, (Controller1.Axis3.position()/ turnValue)/baseRPM , vex::velocityUnits::pct);
    rightBack.spin(forward, (Controller1.Axis2.position()/ turnValue)/baseRPM , vex::velocityUnits::pct);
    leftBack.spin(forward, (Controller1.Axis3.position()/ turnValue)/baseRPM , vex::velocityUnits::pct);
    if (Controller2.ButtonL1.pressing() and !(cubeRamp.rotation(rev)>3.7)){//if button is pressing it will
      cubeRampValue = 85;//sets cube ramp to 85 RPM
    } else if (Controller2.ButtonL2.pressing() and !(cubeRamp.rotation(rev)<0)) {//if button is pressing it will
      cubeRampValue = -100;//sets cube ramp to -100 RPM
    } else {//if no others are true
      cubeRampValue = 0;//Stops cube ramp
    }
    cubeRamp.spin(forward, cubeRampValue , vex::velocityUnits::rpm);//applies the changes
    if (Controller1.ButtonR1.pressing()){//if button is pressing it will
      intakeValue = 100;//sets cube ramp to 100 RPM
    } else if (Controller1.ButtonR2.pressing()) {//if button is pressing it will
      intakeValue = -200;//sets cube ramp to -200 RPM
    } else if (Controller1.ButtonA.pressing()){//if button is pressing it will
      intakeValue = -50;//sets cube ramp to -50 RPM
    }else if(Controller1.ButtonB.pressing()){//if button is pressing it will
      intakeValue = 45;//sets cube ramp to 45 RPM
    } else if(Controller2.ButtonX.pressing()){//if button is pressing it will
      stack();//Stacks
    } else {//If no other conditions are true
      intakeValue = 0;//sets cube ramp to -100 RPM
    }
    if(Controller2.ButtonUp.pressing() and !(oneBar.rotation(rev)>1.7)){
      oneBarValue = 200;
    }else if (Controller2.ButtonDown.pressing()and !(oneBar.rotation(rev)<0)) {
      oneBarValue = -200;
    } else {
      oneBarValue = 0;
    }
    if (Controller2.ButtonR1.pressing()){
      baseRPM = 6;
    } else if (Controller2.ButtonR2.pressing()){
      baseRPM = 2;
    }else {
      baseRPM = 1;
    }
    if (((Controller1.Axis3.value() > 60) and (Controller1.Axis2.value() < -60)) or ((Controller1.Axis3.value() < -60) and (Controller1.Axis2.value() > 60))){
      turnValue = 3;
    } else{
      turnValue = 1;
    }
    oneBar.spin(forward, oneBarValue, pct);
    intakeLeft.spin(forward, intakeValue , vex::velocityUnits::rpm);//applies the changes
    intakeRight.spin(forward, intakeValue , vex::velocityUnits::rpm);
    wait(20, msec); // Sleep the task for a short amount of time to
    Brain.Screen.print(oneBar.rotation(rev));
  }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();
  while (true) {
    wait(100, msec);
  }
}