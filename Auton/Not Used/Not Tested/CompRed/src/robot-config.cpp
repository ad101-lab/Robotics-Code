#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;
/*vex::gyro TurnGyroSmart = gyro(Brain.ThreeWirePort.D);
vex::motor leftFWD           = vex::motor( vex::PORT11, ratio18_1, true);
vex::motor leftBack          = vex::motor( vex::PORT20, ratio18_1, false );
vex::motor rightFWD          = vex::motor( vex::PORT1, ratio18_1, false );
vex::motor rightBack         = vex::motor( vex::PORT10, ratio18_1, true );
vex::motor CubeRamp          = vex::motor( vex::PORT2, ratio36_1, false);
vex::motor intakeRight       = vex::motor( vex::PORT3, ratio6_1, false);
vex::motor intakeLeft        = vex::motor( vex::PORT4, ratio6_1, false);
vex::controller controller1  = vex::controller();
*
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  TurnGyroSmart.calibrate(1);
  Brain.Screen.print("Gyro Is Calibrating"); 
  while (TurnGyroSmart.isCalibrating()) {
    wait(25, msec);
  }
  Brain.Screen.print("Done Calibrating");
  // Nothing to initialize
}