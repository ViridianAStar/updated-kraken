/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\24_nyocum                                        */
/*    Created:      Thu Jan 05 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drive1               motor         11              
// Drive2               motor         20              
// Vacuum               motor         5               
// Launcher             motor         4               
// Vision               vision        19              
// flywheelACM          motor         17              
// Drive3               motor         15              
// Drive4               motor         18              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;



int programSettings[] = {0, 0, 0, 1, 0, 0, 12};
bool breakFactors[2][4] = {{false, false, false, false}, 
                          {false, false, false, false}};

double current_check_D1;
double current_check_D2;
double drive_1_temp;
double drive_2_temp;

int RobotReverseVariable = -1;

void checkDriveTrain() {
  Drive1.spin(forward, 10, rpm);
  Drive2.spin(forward, 10, rpm);
  Drive3.spin(forward, 10, rpm);
  Drive4.spin(forward, 10, rpm);
  if (Drive1.isSpinning() == false) {
    breakFactors[0][0] = true;
  }
  if (Drive2.isSpinning() == false) {
    breakFactors[0][1] = true;
  }
  if (Drive3.isSpinning() == false) {
    breakFactors[0][2] = true;
  }
  if (Drive4.isSpinning() == false) {
    breakFactors[0][3] = true;
  }
  wait(250, msec);
  Drive1.spin(reverse, 10, rpm);
  Drive2.spin(reverse, 10, rpm);
  Drive3.spin(reverse, 10, rpm);
  Drive4.spin(reverse, 10, rpm);
  if (Drive1.isSpinning() == false) {
    breakFactors[0][0] = true;
  }
  if (Drive2.isSpinning() == false) {
    breakFactors[0][1] = true;
  }
  if (Drive3.isSpinning() == false) {
    breakFactors[0][2] = true;
  }
  if (Drive4.isSpinning() == false) {
    breakFactors[0][3] = true;
  }
  wait(250, msec);
  Drive1.stop(brake);
  Drive2.stop(brake);
  Drive3.stop(brake);
  Drive4.stop(brake);
}

void checkGun() {
  flywheelACM.spinFor(forward, 180, degrees);
  if (flywheelACM.isSpinning() == false){
    breakFactors[1][0] = true;
  }
  
  flywheelACM.spinFor(reverse, 180, degrees);
  if (flywheelACM.isSpinning() == false){
    breakFactors[1][0] = true;
  }

  Launcher.spin(forward, 10, rpm);
  if (Launcher.isSpinning() == false) {
    breakFactors[1][1]  = true;
  }
  wait(250, msec);
  Launcher.spin(reverse, 10, rpm);
  if (Launcher.isSpinning() == false) {
    breakFactors[1][1]  = true;
  }
  wait(250, msec);
  Launcher.stop(brake);
}

void checkMotorworking(){
  checkDriveTrain();
  if (breakFactors[0][0] == true) {
    Brain.Screen.print("Failure on Drive1");
    while(true) {
      break;
    }
  }
   if (breakFactors[0][1] == true) {
    Brain.Screen.print("Failure on Drive2");
    while(true) {
      break;
    }
  }
  checkGun();
  if (breakFactors[1][0] == true) {
    Brain.Screen.print("Failure on Flywheel");
    while(true) {
      break;
    }
  }
  if (breakFactors[1][1] == true) {
    Brain.Screen.print("Failure on Launcher");
    while(true) {
      break;
    }
  }
}

void RobotReverse(void) {
  if (RobotReverseVariable == 1) {
    RobotReverseVariable = -1;
    Brain.Screen.clearLine();
    Brain.Screen.print(RobotReverseVariable);
    return;
  }  
  if (RobotReverseVariable == -1) {
    RobotReverseVariable = 1;
    Brain.Screen.clearLine();
    Brain.Screen.print(RobotReverseVariable);
    return;
  }
}

void tempMotor(void) {
  drive_1_temp = Drive1.temperature(celsius);
  drive_2_temp = Drive2.temperature(celsius);
  Brain.Screen.print(drive_2_temp);
  Brain.Screen.newLine();
  Brain.Screen.print(drive_2_temp);
  Brain.Screen.newLine();
  wait(5, seconds);
  Brain.Screen.clearScreen();
}


void fireDisk(void){
  while (Controller1.ButtonL2.pressing() == true) {
    Launcher.spin(forward, 3200, rpm);
  }
}

void driveTime() {
  Drive1.spin(forward, (Controller1.Axis3.position() * RobotReverseVariable) + Controller1.Axis1.position(), volt);
  Drive2.spin(forward, (Controller1.Axis3.position() * RobotReverseVariable) - Controller1.Axis1.position(), volt);
  Drive3.spin(forward, (Controller1.Axis3.position() * RobotReverseVariable) + Controller1.Axis1.position(), volt);
  Drive4.spin(forward, (Controller1.Axis3.position() * RobotReverseVariable) - Controller1.Axis1.position(), volt);
  if (Controller1.ButtonR2.pressing() == true) {
    tempMotor();
  }
  if (Controller1.ButtonY.pressing() == true) {
    Drive1.stop(brake);
    Drive2.stop(brake);
    Drive3.stop(brake);
    Drive4.stop(brake);
  }
  if (Controller1.ButtonA.pressing() == true){
    RobotReverse();
  }
  if (Controller1.ButtonR2.pressing() == true) {
    fireDisk();
  }
}

// only for testing purposed initially
void testCommandpipeline(void) {
  // code to enter into testing settings
  if (Controller1.ButtonLeft.pressing() == true) {
    if (Controller1.ButtonRight.pressing() == true) {
      Brain.Screen.print("System entering test mode please wait...");
      Drive1.stop(brake);
      Drive2.stop(brake);
      Vacuum.stop(brake);
      Launcher.stop(brake);
      Brain.Screen.clearScreen();
      for (int i = 0; i < 10; i++) {
        Brain.Screen.drawCircle(0, 0, i);
      }
      wait(2, seconds);
      Brain.Screen.clearScreen(blue);
      Brain.Screen.print("System succesfully entered test mode!");
      programSettings[0] = 1;
    }
  }
  // code to select groups used
  while (programSettings[0] == 1) {
  if (Controller1.ButtonL1.pressing() == true) {
    if (Controller1.ButtonR1.pressing() == true) {
      programSettings[1] = 1;
      Brain.Screen.clearScreen(blue);
      Brain.Screen.print("Left and Up arrows for drive train only Down and Right arrows for vacuum only");
      Brain.Screen.newLine();
      Brain.Screen.print("X and A buttons for launcher only B and Down for all exit if Y and Left pressed");
      Brain.Screen.newLine();
    }
  }
  while(programSettings[1] == 1) {
    if (Controller1.ButtonLeft.pressing() == true && Controller1.ButtonUp.pressing() == true) {
        programSettings[3] = 1;
        Brain.Screen.print("1");
    }
    if (Controller1.ButtonDown.pressing() == true && Controller1.ButtonRight.pressing() == true) {
        programSettings[3] = 2;
        Brain.Screen.print("2");
    }
    if (Controller1.ButtonX.pressing()  == true && Controller1.ButtonA.pressing() == true) {
        programSettings[3] = 3;
        Brain.Screen.print("3");
    }
    if (Controller1.ButtonB.pressing() == true && Controller1.ButtonDown.pressing() == true) {
        programSettings[3] = 4;
        Brain.Screen.print("4");
    }
    if (Controller1.ButtonY.pressing() == true && Controller1.ButtonLeft.pressing() == true) {
        Brain.Screen.clearScreen(blue);
      }
    }
  }
    while(programSettings[3] == 1) {
      Drive1.spin(forward, (((Controller1.Axis3.position() * RobotReverseVariable) + Controller1.Axis1.position()) * 4) * programSettings[6], rpm);
      Drive2.spin(forward, (((Controller1.Axis3.position() * RobotReverseVariable) - Controller1.Axis1.position()) * 4) * programSettings[6], rpm);
      if (Controller1.ButtonY.pressing() == true) {
         Drive1.stop(brake);
         Drive2.stop(brake);
      }
      if (Controller1.ButtonA.pressing() == true){
       RobotReverse();
      }
    }

  while(programSettings[3] == 2) {
    if(Controller1.Axis1.position() == 100){
      Vacuum.spin(forward, 400 *programSettings[6], rpm);
    }
  }
  while(programSettings[3] == 3) {
    if(Controller1.Axis1.position() == 100){
      Launcher.spin(forward, 400 *programSettings[6], rpm);
    }
  }
  while(programSettings[3] == 4) {
    Drive1.spin(forward, (((Controller1.Axis3.position() * RobotReverseVariable) + Controller1.Axis1.position()) * 4) * programSettings[6], rpm);
    Drive2.spin(forward, (((Controller1.Axis3.position() * RobotReverseVariable) - Controller1.Axis1.position()) * 4) * programSettings[6], rpm);
    if (Controller1.ButtonY.pressing() == true) {
        Drive1.stop(brake);
        Drive2.stop(brake);
    }
    if (Controller1.ButtonA.pressing() == true){
      RobotReverse();
    }
    while (Controller1.ButtonL2.pressing() == true) {
       Launcher.spin(forward, 400 *programSettings[6], rpm);
    }
  }
}

void competition_Drive() {
   Drive1.spin(forward, (((Controller1.Axis3.position() * RobotReverseVariable) + Controller1.Axis1.position()) * 4) * programSettings[6], rpm);
    Drive2.spin(forward, (((Controller1.Axis3.position() * RobotReverseVariable) - Controller1.Axis1.position()) * 4) * programSettings[6], rpm);
    if (Controller1.ButtonY.pressing() == true) {
        Drive1.stop(brake);
        Drive2.stop(brake);
    }
    if (Controller1.ButtonA.pressing() == true){
      RobotReverse();
    }
    while (Controller1.ButtonL2.pressing() == true) {
       Launcher.spin(forward, 400 *programSettings[6], rpm);
    }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  // always needs to be called at the beginning of anything
  checkMotorworking();
}
