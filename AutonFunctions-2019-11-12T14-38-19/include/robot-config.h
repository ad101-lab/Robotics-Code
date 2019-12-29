using namespace vex;

extern brain Brain;

// VEXcode devices
extern gyro TurnGyroSmart;
extern motor leftFWD;
extern motor rightFWD;
extern motor leftBack;
extern motor rightBack;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );