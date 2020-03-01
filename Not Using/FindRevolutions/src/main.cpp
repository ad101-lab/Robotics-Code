#include "userControl.h"
using namespace vex;

void pre_auton(void) {
}

void autonomous(void) {
}

void usercontrol(void) {//User Control
  while(1){
    printRevs = (rightBack.rotation(rev)+leftBack.rotation(rev))/2;
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.clearScreen();
    Controller1.Screen.print(printRevs);
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