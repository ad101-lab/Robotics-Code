#include "vex.h"

using namespace vex;

competition Competition;

brain Brain;
bumper rampBumper        = bumper(Brain.ThreeWirePort.H);//Sets up the Globals of The limit bumpers (THREEWIREPORT H)
bumper rampBumperForward = bumper(Brain.ThreeWirePort.G);//(THREEWIREPORT G)
motor rightFWD = motor(PORT20, ratio18_1, true);//Sets up the drivetrain motors(rightFWD) (PORT 20)
motor leftFWD = motor(PORT9, ratio18_1, false);//Left FWD (PORT9)
motor rightBack = motor(PORT11, ratio18_1, true);//Right Back (PORT 11)
motor leftBack = motor(PORT1, ratio18_1, false);//Letf Back (PORT1)
motor cubeRamp = motor(PORT6, ratio18_1, false);//Cube ramp motor global (PORT 6)
motor intakeRight = motor(PORT5, ratio18_1, true);//Right intake global (PORT 5)
motor intakeLeft = motor(PORT7, ratio18_1, false);//Left intake (PORT 7)
controller Controller1        = controller(primary);//Sets up controllers
controller Controller2        = controller(primary);

int cubeRampValue;//Sets up integers to be used later
int intakeValue;
int cms;
int tright;
int tleft;
int baseSpeed;
bool changedSpeed;

void moveForward(int cm, int speed){
  leftFWD.setVelocity(speed, percent);//Sets up the velocity of the motors
  rightFWD.setVelocity(speed, percent);
  leftBack.setVelocity(speed, percent);
  rightBack.setVelocity(speed, percent);
  cms = (cm/32) * 375;//Transfer to the degrees
  leftFWD.spinFor(cms, degrees, false);//Spins the Motors
  rightFWD.spinFor(cms, degrees, false);
  leftBack.spinFor(cms, degrees, false);
  rightBack.spinFor(cms, degrees, false);
  leftFWD.setVelocity(100, percent);//Resets the Velocity
  rightFWD.setVelocity(100, percent);
  leftBack.setVelocity(100, percent);
  rightBack.setVelocity(100, percent);

} 

void moveBackwards(int cm, int speed){
  leftFWD.setVelocity(speed, percent);//Sets up the velocity of the motors
  rightFWD.setVelocity(speed, percent);
  leftBack.setVelocity(speed, percent);
  rightBack.setVelocity(speed, percent);
  cms = (cm/32) * -375;//Transfer to the degrees
  leftFWD.spinFor(cms, degrees, false);//Spins the Motors
  rightFWD.spinFor(cms, degrees, false);
  leftBack.spinFor(cms, degrees, false);
  rightBack.spinFor(cms, degrees, false);
  leftFWD.setVelocity(100, percent);//Resets the Velocity
  rightFWD.setVelocity(100, percent);
  leftBack.setVelocity(100, percent);
  rightBack.setVelocity(100, percent);

}

void turnRight(int degree){
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

void turnLeft(int degree){
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
  moveForward(1, 0);
  cubeRampVertical(true, 70);//Move the cube ramp up
  intake(-100);//Prepares to move away
  wait(0.3, seconds);//waits
  moveBackwards(40, 30);//Back away
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
}

void autonomous(void) {
  cubeRampVertical(true, 100);
  intake(250);
  cubeRampVertical(false, 90);

}

void usercontrol(void) {//User Control
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
    } else if(Controller2.ButtonX.pressing()){//if button is pressing it will
      stack();//Stacks
    } else {//If no other conditions are true
      intakeValue = 0;//sets cube ramp to -100 RPM
    } 

    if(((Controller1.Axis3.value() > 60) and (Controller1.Axis2.value() < -60)) or ((Controller1.Axis3.value() < -60) and (Controller1.Axis2.value() > 60))) {
      motorSpeed(100);
      changedSpeed = true;
    } else {
      if (changedSpeed == true){
        motorSpeed(250);
        changedSpeed = false;
      } 
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
