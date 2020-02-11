#include "vex.h"

using namespace vex;

competition Competition;

brain Brain;
bumper rampBumper        = bumper(Brain.ThreeWirePort.H);//Sets up the Globals of The limit bumpers
bumper rampBumperForward = bumper(Brain.ThreeWirePort.G);
motor rightFWD = motor(PORT20, ratio6_1, true);//Sets up the drivetrain motors(rightFWD)
motor leftFWD = motor(PORT9, ratio6_1, false);//Left FWD
motor rightBack = motor(PORT11, ratio6_1, true);//Right Back
motor leftBack = motor(PORT1, ratio6_1, false);//Letf Back
motor cubeRamp = motor(PORT6, ratio36_1, false);//Cube ramp motor global
motor intakeRight = motor(PORT5, ratio36_1, true);//Right intake global
motor intakeLeft = motor(PORT7, ratio36_1, false);//Left intake
motor oneBar = motor(PORT1, ratio36_1, true);
controller Controller1        = controller(primary);//Sets up controllers
controller Controller2        = controller(primary);

int cubeRampValue;//Sets up integers to be used later
int intakeValue;
double cms;
double tright;
double tleft;
double oneBarValue;
double turnValue;
double baseRPM;
double degree;

void moveForward(double cm, double speed, bool stopping){
  degree = (cm/32) * 375;//Transfer to the degrees
  leftFWD.spinFor(forward, degree, degrees, speed, velocityUnits::pct, false);
  rightFWD.spinFor(forward, degree, degrees, speed, velocityUnits::pct, false);
  leftBack.spinFor(forward, degree, degrees, speed, velocityUnits::pct, false);
  rightBack.spinFor(forward, degree, degrees, speed, velocityUnits::pct, stopping);
} 

void moveBackwards(double cm, double speed, bool stopping){
  degree = (cm/32) * 375;//Transfer to the degrees
  leftFWD.spinFor(forward, degree, degrees, speed, velocityUnits::pct, false);
  rightFWD.spinFor(forward, degree, degrees, speed, velocityUnits::pct, false);
  leftBack.spinFor(forward, degree, degrees, speed, velocityUnits::pct, false);
  rightBack.spinFor(forward, degree, degrees, speed, velocityUnits::pct, stopping);
}

void turnRight(double degree){
  tright = degree * (335/90) * -1;//Sets the transvertion factors
  tleft  = degree * (335/90);
  leftFWD.setVelocity(100, rpm);
  leftBack.setVelocity(100, rpm);
  rightFWD.setVelocity(100, rpm);
  rightBack.setVelocity(100, rpm);
  leftFWD.spinFor(tleft, vex::rotationUnits::deg, false);//Spins the motor
  leftBack.spinFor(tleft, vex::rotationUnits::deg, false);
  rightFWD.spinFor(tright, vex::rotationUnits::deg, false);
  rightBack.spinFor(tright, vex::rotationUnits::deg, false);
  leftFWD.setVelocity(200, rpm);
  leftBack.setVelocity(200, rpm);
  rightFWD.setVelocity(200, rpm);
  rightBack.setVelocity(200, rpm);
}

void turnLeft(double degree){
  tright = degree * (335/90);//Sets the transvertion factors
  tleft  = degree * (335/90) * -1;
  leftFWD.setVelocity(100, rpm);
  leftBack.setVelocity(100, rpm);
  rightFWD.setVelocity(100, rpm);
  rightBack.setVelocity(100, rpm);
  leftFWD.spinFor(tleft, vex::rotationUnits::deg, false);//spins the motor
  leftBack.spinFor(tleft, vex::rotationUnits::deg, false);
  rightFWD.spinFor(tright, vex::rotationUnits::deg, false);
  rightBack.spinFor(tright, vex::rotationUnits::deg, false);
  leftFWD.setVelocity(200, rpm);
  leftBack.setVelocity(200, rpm);
  rightFWD.setVelocity(200, rpm);
  rightBack.setVelocity(200, rpm);
}

void cubeRampVertical (bool degree, double speed){
  cubeRamp.setVelocity(speed, rpm);//sets the velocity to the specified 
  if(degree == true){
    cubeRamp.spin(forward);//Spins motor Forward
    waitUntil(rampBumperForward.pressing() == true);//Waits until the bumper is pressed
    cubeRamp.stop();//Stops the mmotor
  }else if (degree == false) {
    cubeRamp.spin(reverse);//moves the motor backwards
    waitUntil(rampBumper.pressing() == true);//Waits until the bumper is pressed
    cubeRamp.stop();//Stops the mmotor
  }
  cubeRamp.setVelocity(100, percent);//Resets the velocity

}

void intake (double speed){
  intakeValue = speed*-1; //Conversion factor
  intakeLeft.spin(forward, intakeValue, rpm);//spins both intakes
  intakeRight.spin(forward, intakeValue, rpm);

}

void stack(){
  cubeRampVertical(true, 70);//Move the cube ramp up
  intake(-100);//Prepares to move away
  wait(0.3, seconds);//waits
  moveBackwards(40, 30, false);//Back away
  cubeRampVertical(false, 100);//Puts the cube ramp down
  intake(0);//Stops the intake
}

void motorWait(){
  waitUntil(cubeRamp.isDone());//Waits Until the motors are done
  waitUntil(leftFWD.isDone());
  waitUntil(rightFWD.isDone());
  waitUntil(leftBack.isDone());
  waitUntil(rightBack.isDone());

}

void motorHold(bool holding){
  if(holding == true){
  intakeRight.setStopping(hold);//Holds if the code says to
  intakeLeft.setStopping(hold);
  cubeRamp.setStopping(hold);
  leftFWD.setStopping(hold);
  rightFWD.setStopping(hold);
  leftBack.setStopping(hold);
  rightBack.setStopping(hold);
 }else{
  intakeRight.setStopping(coast);//Lets the motors coast if not
  intakeLeft.setStopping(coast);
  cubeRamp.setStopping(coast);
  leftFWD.setStopping(coast);
  rightFWD.setStopping(coast);
  leftBack.setStopping(coast);
  rightBack.setStopping(coast);
 }
}

int oneBarUp(int distance, int speeds, bool stopping){
  if(oneBar.rotation(rev) < 5 and distance > 0){
    oneBar.spinFor(forward, distance/15, degrees, speeds, velocityUnits::rpm, stopping);//1:15 gear ratio
  }else if (oneBar.rotation(rev) > 0 and distance < 0) {
    oneBar.spinFor(forward, distance/15, degrees, speeds, velocityUnits::rpm, stopping);//1:15 gear ratio
  }else {
    oneBar.stop();
    return false;
  }
  return true;
}

void oneBarStop(){
  while(1){
    if(oneBar.rotation(rev) > 5 or oneBar.rotation(rev) < 0){
      oneBar.stop();
    }
  }
}


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
    if (Controller2.ButtonR1.pressing()){//if button is pressing it will
      intakeValue = 100;//sets cube ramp to 100 RPM
    } else if (Controller2.ButtonR2.pressing()) {//if button is pressing it will
      intakeValue = -200;//sets cube ramp to -200 RPM
    } else if (Controller2.ButtonA.pressing()){//if button is pressing it will
      intakeValue = -50;//sets cube ramp to -50 RPM
    }else if(Controller2.ButtonB.pressing()){//if button is pressing it will
      intakeValue = 45;//sets cube ramp to 45 RPM
    } else if(Controller2.ButtonX.pressing()){//if button is pressing it will
      stack();//Stacks
    } else {//If no other conditions are true
      intakeValue = 0;//sets cube ramp to -100 RPM
    }
    if(Controller1.ButtonUp.pressing() and !(oneBar.rotation(rev)>1.7)){
      oneBarValue = 200;
    }else if (Controller1.ButtonDown.pressing()and !(oneBar.rotation(rev)<0)) {
      oneBarValue = -200;
    } else {
      oneBarValue = 0;
    }
    if (Controller1.ButtonY.pressing()){
      baseRPM = 6;
    } else{
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