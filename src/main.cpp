/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

bool userControl = false;

int i_programSettings_A[] = {0, 0, 0, 1, 0, 0, 12};
bool b_breakFactors_TDA[2][4] = {{false, false, false, false}, 
                          {false, false, false, false}};

double d_current_check_D1;
double d_current_check_D2;
double d_drive_1_temp;
double d_drive_2_temp;
double d_magazineatCapacity = 0.0;

int i_RobotReverseVariable = -1;
int i_launchersReverse = 1;
int i_vacuumReverse = 1;
// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/


void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void checkVacuum() {
  Vacuum.spin(forward, 10, rpm);
  if (Vacuum.isSpinning() == false) {
    b_breakFactors_TDA[1][3] = true;
  }
  wait(250, msec);
  Vacuum.spin(reverse, 10, rpm);
  if (Vacuum.isSpinning() == false) {
    b_breakFactors_TDA[1][3] = true;
  }
  wait(250, msec);
  Vacuum.stop(brake);
  if (Vacuum.efficiency() < 100) {
    b_breakFactors_TDA[1][2] = true;
  }
}

void checkDriveTrain() {
  Drive1.spin(forward, 10, rpm);
  Drive2.spin(forward, 10, rpm);
  Drive3.spin(forward, 10, rpm);
  Drive4.spin(forward, 10, rpm);
  if (Drive1.isSpinning() == false) {
    b_breakFactors_TDA[0][0] = true;
  }
  if (Drive2.isSpinning() == false) {
    b_breakFactors_TDA[0][1] = true;
  }
  if (Drive3.isSpinning() == false) {
   b_breakFactors_TDA[0][2] = true;
  }
  if (Drive4.isSpinning() == false) {
   b_breakFactors_TDA[0][3] = true;
  }
  wait(250, msec);
  Drive1.spin(reverse, 10, rpm);
  Drive2.spin(reverse, 10, rpm);
  Drive3.spin(reverse, 10, rpm);
  Drive4.spin(reverse, 10, rpm);
  if (Drive1.isSpinning() == false) {
    b_breakFactors_TDA[0][0] = true;
  }
  if (Drive2.isSpinning() == false) {
    b_breakFactors_TDA[0][1] = true;
  }
  if (Drive3.isSpinning() == false) {
    b_breakFactors_TDA[0][2] = true;
  }
  if (Drive4.isSpinning() == false) {
    b_breakFactors_TDA[0][3] = true;
  }
  wait(250, msec);
  Drive1.stop(brake);
  Drive2.stop(brake);
  Drive3.stop(brake);
  Drive4.stop(brake);
  if(Drive1.efficiency(percent) < 100) {
    b_breakFactors_TDA[0][0] = true;
     b_breakFactors_TDA[1][2] = true;
  }
  if(Drive2.efficiency(percent) < 100) {
    b_breakFactors_TDA[0][1] = true;
     b_breakFactors_TDA[1][2] = true;
  }
  if(Drive3.efficiency(percent) < 100) {
   b_breakFactors_TDA[0][2] = true;
    b_breakFactors_TDA[1][2] = true;
  }
  if(Drive4.efficiency(percent) < 100) {
   b_breakFactors_TDA[0][3] = true;
     b_breakFactors_TDA[1][2] = true;
  }
}

void checkGun() {
  flywheelACM.spinFor(forward, 180, degrees);
  if (flywheelACM.isSpinning() == false){
    b_breakFactors_TDA[1][0] = true;
  }
  
  flywheelACM.spinFor(reverse, 180, degrees);
  if (flywheelACM.isSpinning() == false){
    b_breakFactors_TDA[1][0] = true;
  }
  if(flywheelACM.efficiency(percent) < 100) {
    b_breakFactors_TDA[1][0] = true;
     b_breakFactors_TDA[1][2] = true;
  }

  Launcher.spin(forward, 10, rpm);
  Launcher.spin(reverse, 10, rpm);
  if (Launcher.isSpinning() == false) {
   b_breakFactors_TDA[1][1]  = true;
  }
  wait(250, msec);
  Launcher.spin(reverse, 10, rpm);
  Launcher2.spin(forward, 10, rpm);
  if (Launcher.isSpinning() == false) {
   b_breakFactors_TDA[1][1]  = true;
  }
  wait(250, msec);
  Launcher.stop(brake);
  Launcher2.stop(brake);
  if(Launcher.efficiency(percent) < 100) {
   b_breakFactors_TDA[1][1] = true;
   b_breakFactors_TDA[1][2] = true;
  }
}

void checkMotorworking(){
  checkDriveTrain();
  if (b_breakFactors_TDA[0][0] == true) {
    Brain.Screen.clearScreen(red);
    Brain.Screen.print("Failure on Drive1");
    if (b_breakFactors_TDA[1][2] == true) {
      Brain.Screen.newLine();
      Brain.Screen.print("Efficiency Error");
    }
    while(true) {
      break;
    }
  }
   if (b_breakFactors_TDA[0][1] == true) {
     Brain.Screen.clearScreen(red);
    Brain.Screen.print("Failure on Drive2");
    if (b_breakFactors_TDA[1][2] == true) {
      Brain.Screen.newLine();
      Brain.Screen.print("Efficiency Error");
    }
    while(true) {
      break;
    }
  }
   if (b_breakFactors_TDA[0][2] == true) {
    Brain.Screen.clearScreen(red);
    Brain.Screen.print("Failure on Drive3");
    if (b_breakFactors_TDA[1][2] == true) {
      Brain.Screen.newLine();
      Brain.Screen.print("Efficiency Error");
    }
    while(true) {
      break;
    }
  }
   if (b_breakFactors_TDA[0][3] == true) {
    Brain.Screen.clearScreen(red);
    Brain.Screen.print("Failure on Drive4");
    if (b_breakFactors_TDA[1][2] == true) {
      Brain.Screen.newLine();
      Brain.Screen.print("Efficiency Error");
    }
    while(true) {
      break;
    }
  }
  checkGun();
  if (b_breakFactors_TDA[1][0] == true) {
    Brain.Screen.clearScreen(red);
    Brain.Screen.print("Failure on Flywheel");
    if (b_breakFactors_TDA[1][2] == true) {
      Brain.Screen.newLine();
      Brain.Screen.print("Efficiency Error");
    }
    while(true) {
      break;
    }
  }
  if (b_breakFactors_TDA[1][1] == true) {
    Brain.Screen.clearScreen(red);
    Brain.Screen.print("Failure on Launcher");
    if (b_breakFactors_TDA[1][2] == true) {
      Brain.Screen.newLine();
      Brain.Screen.print("Efficiency Error");
    }
    while(true) {
      break;
    }
  }
  checkVacuum();
  if (b_breakFactors_TDA[1][3] == true) {
    Brain.Screen.clearScreen(red);
    Brain.Screen.print("Failure on Vacuum");
    if (b_breakFactors_TDA[1][2] == true) {
      Brain.Screen.newLine();
      Brain.Screen.print("Efficiency Error");
    }
    while(true) {
      break;
    }
  }
}

void RobotReverse(void) {
  if (i_RobotReverseVariable == 1) {
    i_RobotReverseVariable = -1;
    Brain.Screen.clearLine();
    Brain.Screen.print(i_RobotReverseVariable);
    return;
  }  
  if (i_RobotReverseVariable == -1) {
    i_RobotReverseVariable = 1;
    Brain.Screen.clearLine();
    Brain.Screen.print(i_RobotReverseVariable);
    return;
  }
}

void tempMotor(void) {
  d_drive_1_temp = Drive1.temperature(celsius);
  d_drive_2_temp = Drive2.temperature(celsius);
  Brain.Screen.print(d_drive_2_temp);
  Brain.Screen.newLine();
  Brain.Screen.print(d_drive_2_temp);
  Brain.Screen.newLine();
  wait(5, seconds);
  Brain.Screen.clearScreen();
}


void fireDisks12_7v(){
  Launcher.spin(forward, 30, volt);
  Launcher2.spin(forward,  30, volt); 
}

void fireDisks5_v(){
  Launcher.spin(forward, 7.5, volt);
  Launcher2.spin(forward, 7.5, volt);
}

void capacityDecreased() {
  d_magazineatCapacity = d_magazineatCapacity + 1.0;
}



bool wheelieMode = false;

void wheelieSwitch(void) {
  if (wheelieMode == true) {
   wheelieMode = false;
   return;
  } 
  if(wheelieMode == false) {
    wheelieMode = true;
    return;
  }
}

void pneumaticsSwitch(){
 if( PneumaticsCtrl_B.value() == true){
    PneumaticsCtrl_B.set(false);
 } else {
    PneumaticsCtrl_B.set(true);
 }
}

bool vaconOff = false;
void VacuumonOffswitch(void){
  if (vaconOff == false) {
    vaconOff = true;
    return;
  }
  if (vaconOff == true) {
    vaconOff = false;
    return;
  }
}

void test_drive_Type2() {
  double wheelPositions[2] = {Drive1.position(deg), Drive2.position(deg)};



    if (wheelieMode == true) {
    Drive1.spin(forward, ((Controller1.Axis3.position() * i_RobotReverseVariable) + Controller1.Axis1.position()) /7.87015748, volt);
    Drive2.spin(forward, ((Controller1.Axis3.position() * i_RobotReverseVariable) - Controller1.Axis1.position()) /7.87015748, volt);
    Drive3.spin(forward,  ((Controller1.Axis3.position() * i_RobotReverseVariable) + Controller1.Axis1.position()) /7.87015748, volt);
    Drive4.spin(forward,  ((Controller1.Axis3.position() * i_RobotReverseVariable) - Controller1.Axis1.position()) /7.87015748, volt);
  } else {
    Drive1.spin(forward, ((Controller1.Axis3.position() * i_RobotReverseVariable) + Controller1.Axis1.position()), percent);
    Drive2.spin(forward, ((Controller1.Axis3.position() * i_RobotReverseVariable) - Controller1.Axis1.position()), percent);
    Drive3.spin(forward, ((Controller1.Axis3.position() * i_RobotReverseVariable) + Controller1.Axis1.position()), percent);
    Drive4.spin(forward, ((Controller1.Axis3.position() * i_RobotReverseVariable) - Controller1.Axis1.position()), percent);
  }

  if ((Controller1.Axis1.position() == 0) && (Controller1.Axis3.position() == 0)) {
    Drive1.stop(hold);
    Drive2.stop(hold);
    Drive3.stop(hold);
    Drive4.stop(hold);
     Brain.Screen.print(wheelPositions[0]);
  Brain.Screen.newLine();
  Brain.Screen.print(wheelPositions[1]);
  wait(250, msec);
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(0, 0);
  wheelPositions[0] = Drive1.position(deg);
  wheelPositions[1] = Drive2.position(deg);
  
  }

}

void driveTime() {
  if (wheelieMode == true) {
    Drive1.spin(forward, ((Controller1.Axis3.position() * i_RobotReverseVariable) + Controller1.Axis1.position()) /7.87015748, volt);
    Drive2.spin(forward, ((Controller1.Axis3.position() * i_RobotReverseVariable) - Controller1.Axis1.position()) /7.87015748, volt);
    Drive3.spin(forward,  ((Controller1.Axis3.position() * i_RobotReverseVariable) + Controller1.Axis1.position()) /7.87015748, volt);
    Drive4.spin(forward,  ((Controller1.Axis3.position() * i_RobotReverseVariable) - Controller1.Axis1.position()) /7.87015748, volt);
  } else {
    Drive1.spin(forward, ((Controller1.Axis3.position() * i_RobotReverseVariable) + Controller1.Axis1.position()), percent);
    Drive2.spin(forward, ((Controller1.Axis3.position() * i_RobotReverseVariable) - Controller1.Axis1.position()), percent);
    Drive3.spin(forward, ((Controller1.Axis3.position() * i_RobotReverseVariable) + Controller1.Axis1.position()), percent);
    Drive4.spin(forward, ((Controller1.Axis3.position() * i_RobotReverseVariable) - Controller1.Axis1.position()), percent);
  }

  if ((Controller1.Axis1.position() == 0) && (Controller1.Axis3.position() == 0)) {
    Drive1.stop(brake);
    Drive2.stop(brake);
    Drive3.stop(brake);
    Drive4.stop(brake);
  }

  Controller1.ButtonUp.pressed(pneumaticsSwitch);

  Controller1.ButtonX.pressed(wheelieSwitch);

  Controller1.ButtonA.pressed(RobotReverse);

  Controller1.ButtonR2.pressed(VacuumonOffswitch);

  if (Controller1.ButtonB.pressing() == true){
    Vacuum.spin(reverse, 30, volt);
  } else {
    if(vaconOff == true){
       Vacuum.spin(forward, 30, volt);
    } else {
      Vacuum.stop(coast);
    }
  }
   
  if (Controller1.ButtonL2. pressing() == true) {
    flywheelACM.spin(reverse, 10, volt);
  } else {
    flywheelACM.stop(coast);
  }


  if (Controller1.ButtonR1.pressing() == true && Controller1.ButtonL1.pressing() == true) {
    fireDisks12_7v();
  } else if (Controller1.ButtonR1.pressing() == true) {
    fireDisks5_v();
  } else {
    Launcher.stop(coast);
    Launcher2.stop(coast);
  }

  if (Controller1.ButtonDown.pressing() == true) {
    Launcher.spin(reverse, 30, volt);
    Launcher2.spin(reverse, 30, volt);
  }

  capacitySwitch.pressed(capacityDecreased);

}

void softAIsys(signature TEAM) {
  // TODO: please program this at some point. It would be valuable.
}

void brakeDT() {
  Drive1.stop(brake);
  Drive2.stop(brake);
  Drive3.stop(brake);
  Drive4.stop(brake);
}

void runAutonskills(void) {
  Drive1.spinToPosition(-45, degrees);
  Drive2.spinToPosition(-45, degrees);
  Drive3.spinToPosition(-45, degrees);
  Drive4.spinToPosition(-45, degrees);
   
  Vacuum.setMaxTorque(2000, percent);

  Vacuum.setVelocity(200, rpm);

  Vacuum.spinToPosition(270, degrees);

  Drive1.spinToPosition(765, degrees);
  Drive2.spinToPosition(765, degrees);
  Drive3.spinToPosition(765, degrees);
  Drive4.spinToPosition(765, degrees);

  Vacuum.spinToPosition(-270, degrees);

  Drive1.spinToPosition(90, degrees);
  Drive2.spinToPosition(-90, degrees);
  Drive3.spinToPosition(90, degrees);
  Drive4.spinToPosition(-90, degrees);

  Drive1.spinToPosition(-765, degrees);
  Drive2.spinToPosition(-765, degrees);
  Drive3.spinToPosition(-765, degrees);
  Drive4.spinToPosition(-765, degrees);

  Vacuum.spinToPosition(270, degrees);

  Drive1.spinToPosition(765, degrees);
  Drive2.spinToPosition(765, degrees);
  Drive3.spinToPosition(765, degrees);
  Drive4.spinToPosition(765, degrees);

  Drive1.spinToPosition(-180, degrees);
  Drive2.spinToPosition(180, degrees);
  Drive3.spinToPosition(-180, degrees);
  Drive4.spinToPosition(180, degrees);
}

void notSkillsauton(){
  Drive1.spinToPosition(-45, degrees);
  Drive2.spinToPosition(-45, degrees);
  Drive3.spinToPosition(-45, degrees);
  Drive4.spinToPosition(-45, degrees);
   
  Vacuum.setMaxTorque(2000, percent);

  Vacuum.setVelocity(200, rpm);

  Vacuum.spinToPosition(420, degrees);
}

void skillsAuton(){

  Drive1.spinToPosition(120, degrees);
  Drive2.spinToPosition(-120, degrees);
  Drive3.spinToPosition(120, degrees);
  Drive4.spinToPosition(-120, degrees);

  wait(0.5, seconds);

  pneumaticsSwitch();
}

void autonomous(void) {
  //softAIsys();
  //runAutonskills();
  notSkillsauton();
  //skillsAuton();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
   //driveTime();
   test_drive_Type2();
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
 Competition.autonomous(autonomous);
 Competition.drivercontrol(usercontrol);
 //skillsAuton();
 //autonomous();
 // while(true){
   // driveTime();
  //}
  //while(true) {
    //Controller1.ButtonA.pressed(pneumaticsSwitch);
  //}
}
/*while (true) {
    if (Brain.Screen.pressing() == true) {
      fireDisk();
    } else {
      Launcher.stop(coast);
      Launcher2.stop(coast);
    }
  }*/