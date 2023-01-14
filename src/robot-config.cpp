#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor Drive1 = motor(PORT20, ratio18_1, false);
motor Drive2 = motor(PORT11, ratio18_1, true);
motor Vacuum = motor(PORT7, ratio18_1, false);
motor Launcher = motor(PORT10, ratio6_1, true);
/*vex-vision-config:begin*/
signature Vision__VEXDISK = signature (1, -47, 47, 0, -2907, -2403, -2655, 4.4, 0);
signature Vision__REDNET = signature (2, 6337, 9125, 7731, -927, 421, -253, 3.9, 0);
signature Vision__BLUENET = signature (3, -2817, 1, -1408, 4369, 11299, 7834, 1.7, 0);
vision Vision = vision (PORT1, 26, Vision__VEXDISK, Vision__REDNET, Vision__BLUENET);
/*vex-vision-config:end*/
motor flywheelACM = motor(PORT15, ratio18_1, true);
motor Drive3 = motor(PORT19, ratio18_1, false);
motor Drive4 = motor(PORT12, ratio18_1, true);
limit capacitySwitch = limit(Brain.ThreeWirePort.A);
motor Launcher2 = motor(PORT9, ratio6_1, true);

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