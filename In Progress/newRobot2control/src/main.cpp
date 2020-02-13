#include "v5.h"
#include "v5_vcs.h"
#include "include.h"

void pre_auton(void) {
  wait(1, seconds);
  motorHold(true);
  if(oneBar.installed() == false or  rightFWD.installed() == false or rightBack.installed() == false or leftFWD.installed() == false or leftBack.installed() == false and cubeRamp.installed() == false){while(1){wait(1,seconds);}}
}

void autonomous(void) {
  intake(200);
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
      vex::task hi(stack);//Stacks
    } else {//If no other conditions are true
      intakeValue = 0;//sets cube ramp to -100 RPM
    }
    if(Controller2.ButtonUp.pressing() and !(oneBar.rotation(rev)>1.7)){
      oneBarValue = 200;
    }else if (Controller2.ButtonDown.pressing() and !(oneBar.rotation(rev)<0)) {
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
    if (Controller2.ButtonA.pressing()){
      oneBarTower("low", false, 100);
    } else if(Controller2.ButtonB.pressing()){
      oneBarTower("mid", false, 100);
    } else if (Controller2.ButtonY.pressing()) {
      oneBarTower("null", false, 100);
    }
    Controller2.Screen.clearScreen();
    Controller2.Screen.setCursor(1, 1);
    Controller2.Screen.print("Chassis Temp: %d", (rightFWD.temperature()+leftFWD.temperature()+rightBack.temperature()+leftBack.temperature())/4);
    Controller2.Screen.newLine();
    Controller2.Screen.print("Intake Temp: %d", (intakeRight.temperature()+intakeLeft.temperature())/2);
    Controller2.Screen.newLine();
    Controller2.Screen.print("One Bar: %d", oneBar.temperature());
    Controller2.Screen.newLine();
    Controller2.Screen.print("Cube Ramp: %d", cubeRamp.temperature());
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Chassis Temp: %d", (rightFWD.temperature()+leftFWD.temperature()+rightBack.temperature()+leftBack.temperature())/4);
    Controller1.Screen.newLine();
    Controller1.Screen.print("Intake Temp: %d", (intakeRight.temperature()+intakeLeft.temperature())/2);
    Controller1.Screen.newLine();
    Controller1.Screen.print("One Bar: %d", oneBar.temperature());
    Controller1.Screen.newLine();
    Controller1.Screen.print("Cube Ramp: %d", cubeRamp.temperature());
    oneBar.spin(forward, oneBarValue, pct);
    intakeLeft.spin(forward, intakeValue , vex::velocityUnits::rpm);//applies the changes
    intakeRight.spin(forward, intakeValue , vex::velocityUnits::rpm);
    wait(20, msec);
    Brain.Screen.print(oneBar.temperature());
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