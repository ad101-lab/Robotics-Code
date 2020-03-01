#include "vex.h"

using namespace vex;

competition Competition;

brain Brain;
bumper rampBumper        = bumper(Brain.ThreeWirePort.H);//Sets up the Globals of The limit bumpers
bumper rampBumperForward = bumper(Brain.ThreeWirePort.G);
inertial Inertial           = inertial(PORT15);
motor rightFWD = motor(PORT20, ratio18_1, true);//Sets up the drivetrain motors(rightFWD)
motor leftFWD = motor(PORT9, ratio18_1, false);//Left FWD
motor rightBack = motor(PORT11, ratio18_1, true);//Right Back
motor leftBack = motor(PORT1, ratio18_1, false);//Letf Back
motor cubeRamp = motor(PORT6, ratio18_1, false);//Cube ramp motor global
motor intakeRight = motor(PORT5, ratio18_1, true);//Right intake global
motor intakeLeft = motor(PORT7, ratio18_1, false);//Left intake
controller Controller1        = controller(primary);//Sets up controllers
controller Controller2        = controller(primary);

int cubeRampValue;//Sets up integers to be used later
int intakeValue;
int degree;
int tright;
int tleft;
int baseSpeed;
bool driveEnabledPID = true;

//Settings
double kP = 0.0;
double kI = 0.0;
double kD = 0.0;
int desiredValue = 100;

int error;
int prevError = 0;
int derivative;
int totalError = 0;

void drivePID(){
  while(driveEnabledPID){

    int leftFWDMotorPosition = leftFWD.position(degrees);
    int rightFWDMotorPosition = rightFWD.position(degrees);
    int leftBackMotorPosition = leftBack.position(degrees);
    int rightBackMotorPosition = rightBack.position(degrees);
    int adveragePosition = (rightBackMotorPosition + leftBackMotorPosition + rightFWDMotorPosition + leftFWDMotorPosition)/ 4;

    error = adveragePosition - desiredValue;

    derivative = error - prevError;

    totalError += error;

    double motorPower = (error * kP + derivative * kD + totalError * kI) / 12.0;

    prevError = error;
    task::sleep(20);
  }
}

void moveForward(int cm, int speed, bool stopping){
  degree = (cm/32) * 375;//Transfer to the degrees
  leftFWD.spinFor(forward, degree, degrees, speed, velocityUnits::pct, false);
  rightFWD.spinFor(forward, degree, degrees, speed, velocityUnits::pct, false);
  leftBack.spinFor(forward, degree, degrees, speed, velocityUnits::pct, false);
  rightBack.spinFor(forward, degree, degrees, speed, velocityUnits::pct, stopping);
} 

void moveBackwards(int cm, int speed, bool stopping){
  degree = (cm/32) * 375;//Transfer to the degrees
  leftFWD.spinFor(forward, degree, degrees, speed, velocityUnits::pct, false);
  rightFWD.spinFor(forward, degree, degrees, speed, velocityUnits::pct, false);
  leftBack.spinFor(forward, degree, degrees, speed, velocityUnits::pct, false);
  rightBack.spinFor(forward, degree, degrees, speed, velocityUnits::pct, stopping);
}

void turnRight(int degree, int speed){
  Inertial.calibrate();
  waitUntil(Inertial.isCalibrating() == false);
  leftFWD.spin(forward, speed, percent);
  rightFWD.spin(reverse, speed, percent);
  leftBack.spin(forward, speed, percent);
  rightBack.spin(reverse, speed, percent);
  waitUntil((Inertial.rotation(degrees) >= degree));
  leftFWD.stop();
  rightFWD.stop();
  leftBack.stop();
  rightBack.stop();
}

void turnLeft(int degree, int speed){
  Inertial.calibrate();
  waitUntil(Inertial.isCalibrating() == false);
  leftFWD.spin(forward, speed, percent);
  rightFWD.spin(reverse, speed, percent);
  leftBack.spin(forward, speed, percent);
  rightBack.spin(reverse, speed, percent);
  waitUntil((Inertial.rotation(degrees) <= degree));
  leftFWD.stop();
  rightFWD.stop();
  leftBack.stop();
  rightBack.stop();
}

void cubeRampVertical (bool degree, int speed){
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

void intake (int speed){
  intakeValue = speed*-1; //Conversion factor
  intakeLeft.spin(forward, intakeValue, rpm);//spins both intakes
  intakeRight.spin(forward, intakeValue, rpm);

}

void stack(){
  wait(0.3 ,seconds);
  moveForward(1, 0, false);
  cubeRampVertical(true, 70);//Move the cube ramp up
  intake(-100);//Prepares to move away
  wait(0.3, seconds);//waits
  moveBackwards(40, 30, false);//Back away
  cubeRampVertical(false, 100);//Puts the cube ramp down
  intake(0);//Stops the intake
}

int driveStack(){
  while(Controller1.ButtonX.pressing()){
    stack();
    task::sleep(20);
  }
  return 1;
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

void motorSpeed(int velocity){
  intakeRight.setVelocity(velocity, percent);
  intakeLeft.setVelocity(velocity, percent);
  cubeRamp.setVelocity(velocity, percent);
  leftFWD.setVelocity(velocity, percent);
  rightFWD.setVelocity(velocity, percent);
  leftBack.setVelocity(velocity, percent);
  rightBack.setVelocity(velocity,percent);
  
}
void pre_auton(void) {
  motorHold(true);
  Inertial.calibrate();
  waitUntil(Inertial.isCalibrating() == false);
}

void autonomous(void) {
  intake(250);//Sets the intake to flip out cube ramp
  wait(1, seconds);//waits for that to happen
  moveForward(115, 20, true);//picks up the cubes
  //wait(7, seconds);//waits until it is done
  intake(10);//slows the intake
  turnLeft(180, 50);
  intake(100);
  wait(1, seconds);
  intake(25);
  moveBackwards(48, 50, true);
  //wait(1, seconds);
  turnRight(135, 50);
  wait(1,seconds);
  moveForward(65, 30, true);
  //wait(2, seconds);
  intake(0);
  stack();
  moveBackwards(50, 100, true);
  //wait(3, seconds);
  turnRight(135, 70);
  moveForward(100, 30, true);
  turnLeft(45, 50);
  moveForward(30, 50, true);
  stack();
  turnRight(45, 50);
  moveForward(50, 50, true);
  turnRight(90, 50);
  intake(250);
  moveForward(100, 30, true);
  intake(10);
  moveBackwards(100, 100, true);
  turnRight(90, 100);
  moveForward(200, 100, true);
  turnRight(45, 100);
  moveForward(20, 50, true);
  stack();
}

void usercontrol(void) {//User Control
  task stacking(driveStack);
  while (1) {
    motorHold(true);//Puts the motors into hold mode
    rightFWD.spin(forward, Controller1.Axis2.position() , vex::velocityUnits::pct);//Tank Drive controls
    leftFWD.spin(forward, Controller1.Axis3.position() , vex::velocityUnits::pct);
    rightBack.spin(forward, Controller1.Axis2.position() , vex::velocityUnits::pct);
    leftBack.spin(forward, Controller1.Axis3.position() , vex::velocityUnits::pct);
    if (Controller2.ButtonL1.pressing() and !(rampBumperForward.pressing())){//if button is pressing it will
      cubeRampValue = 85;//sets cube ramp to 85 RPM
    } else if (Controller2.ButtonL2.pressing() and !(rampBumper.pressing())) {//if button is pressing it will
      cubeRampValue = -100;//sets cube ramp to -100 RPM
    } else if (Controller2.ButtonUp.pressing()) {//if button is pressing it will
      cubeRampVertical(true, 80);//moves cube ramp up
    } else if (Controller2.ButtonDown.pressing()){//if button is pressing it will
      cubeRampVertical(false, 80);//moves cube ramp down
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
    } /*else if(Controller2.ButtonX.pressing()){//if button is pressing it will
      stack();//Stacks
    }*/ else if (Controller2.ButtonR1.pressing() and Controller2.ButtonR2.pressing()){
      baseSpeed = 100;
    } else {//If no other conditions are true
      intakeValue = 0;//sets cube ramp to -100 RPM
    } 
    if(((Controller1.Axis3.value() > 60) and (Controller1.Axis2.value() < -60)) or ((Controller1.Axis3.value() < -60) and (Controller1.Axis2.value() > 60))) {
      baseSpeed = 70;
    } else {
      baseSpeed = 250;
    } 

    intakeLeft.spin(forward, intakeValue , vex::velocityUnits::rpm);//applies the changes
    intakeRight.spin(forward, intakeValue , vex::velocityUnits::rpm);
    Controller1.Screen.clearScreen();
    Controller1.Screen.print("R", (rightFWD.velocity(rpm)+rightBack.velocity(rpm)/2));
    Controller1.Screen.newLine(); 
    Controller1.Screen.print("L", (leftFWD.velocity(rpm)+leftBack.velocity(rpm)/2));
    Controller1.Screen.newLine(); 
    Controller1.Screen.print("INTAKES", leftFWD.velocity(rpm));
    wait(20, msec); // Sleep the task for a short amount of time to
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
