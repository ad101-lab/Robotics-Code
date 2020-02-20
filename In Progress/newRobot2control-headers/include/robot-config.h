#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "v5.h"
#include "v5_vcs.h"

#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
using namespace vex;

extern brain Brain;
extern motor leftFWD;
extern motor leftBack;
extern motor rightFWD;
extern motor rightBack;
extern motor CubeRamp;
extern motor intakeRight;
extern motor intakeLeft;
extern controller Controller1;
extern controller Controller2;
extern bumper rampBumper;
extern bumper rampBumperForward;
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
controller Controller2        = controller(partner);

int cubeRampValue;//Sets up integers to be used later
int intakeValue;
double cms;
double tright;
double tleft;
double oneBarValue;
double turnValue;
double baseRPM;
double degree;
double oneBarRotation;
bool autonSide = false;
std::string tower;
std::string auton= "Red";

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

void oneBarChecker(){
  while(1){
    oneBarRotation = oneBar.rotation(rev);
    task::sleep(100);
  }
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
  oneBar.setStopping(hold);
 }else{
  intakeRight.setStopping(coast);//Lets the motors coast if not
  intakeLeft.setStopping(coast);
  cubeRamp.setStopping(coast);
  leftFWD.setStopping(coast);
  rightFWD.setStopping(coast);
  leftBack.setStopping(coast);
  rightBack.setStopping(coast);
  oneBar.setStopping(coast);
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

void oneBarTower(std::string tower){
  double goal;
  if(tower == "High" or tower =="high"){
    goal = 1.7;
  } else if (tower == "Mid" or tower == "Middle" or tower == "mid" or tower == "middle") {
    goal = 1.2;
  }else if (tower == "Low" or tower == "low" or tower == "alliance" or tower == "Alliance") {
    goal = 0.7;
  } else {
    //the lack of something makes this space aquard
  };
  if(goal < oneBarRotation){
    oneBar.spin(forward, 100, pct);
  } else if(goal > oneBarRotation){
    oneBar.spin(reverse, 100, pct);
  }
}


int redAuton(){
  intake(100);
  oneBarUp(45, 100, true);
  oneBarUp(-45, 100, true);
  moveForward(110, 10, true);
  intake(0);
  moveBackwards(54, 50, true);
  turnRight(180);
  moveForward(63.5, 10, true);
  intake(0);
  stack();
  return 1;
}

int blueAuton(){
  intake(100);
  oneBarUp(45, 100, true);
  oneBarUp(-45, 100, true);
  moveForward(110, 10, true);
  intake(0);
  moveBackwards(54, 50, true);
  turnLeft(180);
  moveForward(63.5, 10, true);
  intake(0);
  stack();
  return 1;
}

void pickAuton (){
  task::sleep(100);
  while(!Controller1.ButtonA.pressing()){
    Brain.Screen.print(auton);
    if(Controller1.ButtonRight.pressing() or Controller1.ButtonLeft.pressing()){
      if(autonSide == true){
        auton = "RED";
      }else{
        auton = "BLUE";
      }
      Controller1.Screen.setCursor(1, 1);
      Controller1.Screen.clearScreen();
      Controller1.Screen.print(auton);
      task::sleep(50);
    }
  }
  if(auton == "RED"){
    task redAutonomous(redAuton);
  } else{
    task blueAutonomous(blueAuton);
  }
}

