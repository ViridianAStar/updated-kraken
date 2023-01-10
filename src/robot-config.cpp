#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor Drive1 = motor(PORT11, ratio18_1, false);
motor Drive2 = motor(PORT20, ratio18_1, true);
motor Vacuum = motor(PORT5, ratio18_1, false);
motor Launcher = motor(PORT4, ratio18_1, false);
/*vex-vision-config:begin*/
signature Vision__VEXDISK = signature (1, -1, 49, 24, -4097, -3487, -3792, 9.3, 0);
signature Vision__REDNET = signature (2, 6337, 9125, 7731, -927, 421, -253, 1.4, 0);
signature Vision__BLUENET = signature (3, -2785, -1345, -2065, 5691, 10117, 7904, 1.7, 0);
vision Vision = vision (PORT19, 50, Vision__VEXDISK, Vision__REDNET, Vision__BLUENET);
/*vex-vision-config:end*/
motor flywheelACM = motor(PORT17, ratio18_1, false);
motor Drive3 = motor(PORT15, ratio18_1, false);
motor Drive4 = motor(PORT18, ratio18_1, false);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}