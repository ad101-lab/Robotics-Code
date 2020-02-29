#include "userControl.h"
using namespace vex;

void pre_auton(void) {
  //task pickAutonmous(pickAuton);
}

void autonomous(void) {
  //runAuton();
}
void usercontrol(void) {//User Control
  double hi;
  while(1){
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.clearScreen();
    hi = cubeRamp.rotation(rev);
    Controller1.Screen.print(hi);
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
