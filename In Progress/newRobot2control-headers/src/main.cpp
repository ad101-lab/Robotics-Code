#include "userControl.h"
using namespace vex;

void pre_auton(void) {
  task userControls(userControl);
  motorHold(true);
  task pickAutonmous(pickAuton);
}

void autonomous(void) {
  userControlEnabled=false;
  //flipOut();
  runAuton();
  //moveForward(, int speed)
}

void usercontrol(void) {//User Control
  userControlEnabled = true;
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();
  while (true) {
    wait(100, msec);
  }
}