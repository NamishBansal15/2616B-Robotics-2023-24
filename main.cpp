#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;


// START V5 MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS


// Robot configuration code.
// Controller
controller Controller1 = controller(primary);

// Drive train
// Left drive motors
motor left_front = motor(PORT1, ratio6_1, false);
motor left_back = motor(PORT2, ratio6_1, false);
motor_group left_drive = motor_group(left_front, left_back);
// Right drive motors
motor right_front = motor(PORT3, ratio6_1, true);
motor right_back = motor(PORT4, ratio6_1, true);
motor_group right_drive = motor_group(right_front, right_back);
// IMU
inertial drive_IMU = inertial(PORT7);
// Putting it all together
smartdrive drive_train = smartdrive(left_drive, right_drive, drive_IMU, 398.98, 320, 40, mm, 0.5714285714285714);

// Intake motor
motor intake = motor(PORT5, ratio6_1, false);

// Flywheel motor
motor flywheel = motor(PORT6, ratio6_1, false);

// Piston solenoid
digital_out solenoid = digital_out(Brain.ThreeWirePort.A);

void calibrateDrivetrain() {
  wait(200, msec);
  Brain.Screen.print("Calibrating");
  Brain.Screen.newLine();
  Brain.Screen.print("Inertial");
  drive_IMU.calibrate();
  while (drive_IMU.isCalibrating()) {
    wait(25, msec);
  }

  // Clears the screen and returns the cursor to row 1, column 1.
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
}

// Helper to make playing sounds from the V5 in VEXcode easier and
// keeps the code cleaner by making it clear what is happening.
void playVexcodeSound(const char *soundName) {
  printf("VEXPlaySound:%s\n", soundName);
  wait(5, msec);
}



// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

#pragma endregion VEXcode Generated Robot Configuration

/*
  +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+
  |                                                                                |
  |    Module:       main.cpp                                                      |
  |    Author:       Rohan Bharatia                                                |
  |    Created:      1/31/2024                                                     |
  |    Description:  2023-2024 2616B Blåhaj Code                                   |
  |                                                                                |
  +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+
*/

// Include the V5 Library
#include "vex.h"
  
// Allows for easier use of the VEX Library
using namespace vex;

// Define if you have an auton
bool AUTON = false;

void pre_auton(void)
{
  Brain.Screen.clearScreen();

  wait(1, seconds);
}

void auton(void)
{
  Brain.Screen.clearScreen();

  if(AUTON)
  {
    // Auton cose
  }
}

void user_controls(void)
{
  Brain.Screen.clearScreen();

  while(true)
  {
    // Drive train movement
    while(Controller1.Axis3.position() > 0 && Controller1.Axis2.position() > 0)
    {
      drive_train.drive(forward);
    }
    while(Controller1.Axis3.position() < 0 && Controller1.Axis2.position() < 0)
    {
      drive_train.drive(reverse);
    }

    // Drive train rotatation
    while(Controller1.Axis3.position() < 0 && Controller1.Axis2.position() > 0)
    {
      drive_train.turn(left);
    }
    while(Controller1.Axis3.position() > 0 && Controller1.Axis2.position() < 0)
    {
      drive_train.turn(right);
    }

    // Intake rotation
    while(Controller1.ButtonR2.pressing())
    {
      intake.spin(forward);
    }
    while(Controller1.ButtonR1.pressing())
    {
      intake.spin(reverse);
    }

    // Flywheel rotation
    bool flywheel_state = false;

    if(Controller1.ButtonL2.pressing())
    {
      flywheel_state = true;
    }
    if(Controller1.ButtonL1.pressing())
    {
      flywheel_state = false;
    }

    if(flywheel_state)
    {
      flywheel.spin(forward);
    }

    // Wing extenders
    bool piston_state = false;

    if(Controller1.ButtonUp.pressing())
    {
      piston_state = true;
    } else
    {
      piston_state = false;
    }

    solenoid.set(piston_state);

    // Hard-stopping all motors
    drive_train.setStopping(brake);
    intake.setStopping(brake);
    flywheel.setStopping(brake);

    wait(20, msec);
  }
}

int main() {
  competition Competition;

  calibrateDrivetrain();

  Competition.autonomous(auton);
  Competition.drivercontrol(user_controls);

  pre_auton();

  while(true)
  {
    wait(100, msec);
  }
}

