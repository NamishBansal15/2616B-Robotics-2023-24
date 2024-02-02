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

// Drivetrain
motor left_front = motor(PORT1, ratio6_1, true);
motor left_back = motor(PORT2, ratio6_1, true);
motor_group left_drive = motor_group(left_front, left_back);
motor right_front = motor(PORT3, ratio6_1, false);
motor right_back = motor(PORT4, ratio6_1, false);
motor_group right_drive = motor_group(right_front, right_back);
inertial drive_IMU = inertial(PORT7);
smartdrive drive_train = smartdrive(left_drive, right_drive, drive_IMU, 319.19, 320, 40, mm, 0.42857142857142855);

// Intake
motor intake_motor = motor(PORT5, ratio6_1, false);

// Flywheel
motor flywheel_motor = motor(PORT6, ratio6_1, false);

// Wings (pistons)
motor solenoid = digital_out(Brain.ThreeWirePort.A);


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
  +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+
  |                                                         |
  |    Module:       2616B.v5cpp                            |
  |    Author:       Rohan Bharatia                         |
  |    Created:      2/1/2024                               |
  |    Description:  2023-2024 2616B Blahaj vexcode file    |
  |                                                         |
  +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+
*/

// Include the V5 Library
#include "vex.h"
  
// Allows for easier use of the VEX Library
using namespace vex;

float f_mm(float feet)
{
  return (feet * 3.2808) * 1000;
}

void pre_auton(void)
{
  wait(10, seconds);
}

void auton(void)
{
  Brain.Screen.clearScreen();

  // Auton
  drive_train.driveFor(forward, f_mm(5.5), mm);
  drive_train.turnFor(left, 90 degrees);
  drive_train.driveFor(forward, f_mm(0.5), mm);
  intake_motor.spinFor(reverse, 360 * 5, degrees);
  drive_train.driveFor(reverse, f_mm(0.5), mm);
  drive_train.turnFor(left, 180, degrees);
  drive_train.driveFor(forward, f_mm(1), mm);
  int i = 1;
  while(i === 1)
  {
    intake_motor.spinFor(forward, 360 * 4, degrees);
  }
  drive_train.turnFor(left, 180, degrees);
  drive_train.driveFor(forward, f_mm(2), mm);
  i = 0;
  intake_motor.spinFor(reverse, 360 * 5, degrees);
}

void driver_controls(void)
{
  Brain.Screen.clearScreen();

  drive_train.setStopping(brake);
  intake_motor.setStopping(brake);
  flywheel_motor.setStopping(brake);

  bool left_move = true;
  bool right_move = true;

  bool intake = true;
  bool outtake = false;

  bool flywheel = true;

  bool wings = true;

  while(true)
  {
    if(RemoteControlCodeEnabled)
    {
      // Drivetrain controls
      float left_drive_speed = Controller1.Axis3.position();
      float right_drive_speed = Controller1.Axis2.position();

      if(left_drive_speed < 5 && left_drive_speed > -5)
      {
        if(left_move)
        {
          left_drive.stop();
          left_move = false;
        }
      } else
      {
        left_move = true;
      }
      if(right_drive_speed < 5 && right_drive_speed > -5)
      {
        if(right_move)
        {
          right_drive.stop();
          right_move = false;
        }
      } else
      {
        right_move = true;
      }

      if(left_move)
      {
        left_drive.setVelocity(left_drive_speed * 2, percent);
        left_drive.spin(forward, 11, volt);
      }
      if(right_move)
      {
        right_drive.setVelocity(right_drive_speed * 2, percent);
        right_drive.spin(forward, 11, volt);
      }

      // Intake controls
      bool in_ = Controller1.ButtonL1.pressing();
      bool out_ = Controller1.ButtonL2.pressing();

      if(in_)
      {
        if(intake)
        {
          intake_motor.stop();
          intake = false;
        }
      } else
      {
        intake = true;
      }
      if(out_)
      {
        if(outtake)
        {
          intake_motor.stop();
          outtake = false;
        }
      } else
      {
        outtake = true;
      }

      if(intake)
      {
        intake_motor.setVelocity(200, percent);
        intake_motor.spin(forward, 11, volt);
      }
      if(outtake)
      {
        intake_motor.setVelocity(200, percent);
        intake_motor.spin(reverse, 11, volt);
      }

      // Flywheel controls
      bool flywheel_on = Controller1.ButtonL1.pressing();
      bool flywheel_off = Controller1.ButtonL2.pressing();

      if(flywheel_on)
      {
        if(flywheel)
        {
          flywheel_motor.stop();
          flywheel = false;
        }
      } else
      {
        flywheel = true;
      }
      if(flywheel_off)
      {
        flywheel_motor.stop();
        flywheel = false;
      }

      if(flywheel)
      {
        flywheel_motor.setVelocity(200, percent);
        flywheel_motor.spin(forward, 11, volt);
      }

      // Wings (pistons) controls
      bool pistons = Controller1.ButtonUp.pressing();

      if(pistons)
      {
        if(wings)
        {
          solenoid.set(false);
          wings = false;
        }
      } else
      {
        wings = true;
      }

      if(pistons)
      {
        solenoid.set(true);
      }
    }

    wait(20, msec);
  }
}

int main() {
  competition Competition;
  calibrateDrivetrain();

  Competition.autonomous(auton);
  Competition.drivercontrol(driver_controls);

  pre_auton();

  while(true)
  {
    Brain.Screen.clearScreen();

    Brain.Screen.setCursor(1, 1);
    Controller1.Screen.print(Brain.Battery.voltage());

    wait(10, msec);
  }
}
