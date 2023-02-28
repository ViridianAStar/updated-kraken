using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern controller Controller1;
extern motor Drive1;
extern motor Drive2;
extern motor Vacuum;
extern motor Launcher;
extern signature Vision__VEXDISK;
extern signature Vision__REDNET;
extern signature Vision__BLUENET;
extern signature Vision__SIG_4;
extern signature Vision__SIG_5;
extern signature Vision__SIG_6;
extern signature Vision__SIG_7;
extern vision Vision;
extern motor flywheelACM;
extern motor Drive3;
extern motor Drive4;
extern limit capacitySwitch;
extern motor Launcher2;
extern digital_out PneumaticsCtrl_B;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );