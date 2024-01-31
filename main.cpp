/*
~~~ DO NOT touch anything from '#pragma region VEXcode Generated Robot Configuration' to '#pragma endregion VEXcode Generated Robot Configuration' ~~~
*/
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




// Helper to make playing sounds from the V5 in VEXcode easier and
// keeps the code cleaner by making it clear what is happening.
void playVexcodeSound(const char *soundName) {
  printf("VEXPlaySound:%s\n", soundName);
  wait(5, msec);
}

#pragma endregion VEXcode Generated Robot Configuration

// ~~~ All code below this line (46+) was written by me ~~~
/*
+--------------------------------------------------------------------------+
|                                                                          |
|   Module:       Blåhaj.lib                                               |
|   Author:       Rohan Bharatia                                           |
|   Created:      1/30/2024                                                |
|   Description:  V5 project                                               |
|                                                                          |
+--------------------------------------------------------------------------+
*/

// Include the V5 Library
#include "vex.h"

// Allows for easier use of the VEX Library
using namespace vex;

// Define (preset) brain button layout
#define X 0 // Used for: left_joystick + right_joystick + action_button
#define Y 1 // Used for: left_joystick + right_joystick + action_button
#define A 2 // Used for: action_button
#define B 3 // Used for: action_button
#define L1 0 // Used for: back_left
#define L2 1 // Used for: back_left
#define R1 0 // Used for: back_right
#define R2 1 // Used for: back_right
#define UP 0 // Used for: arrow
#define DOWN 1 // Used for: arrow
#define LEFT 2 // Used for: arrow
#define RIGHT 3 // Used for: arrow

// Define analog ports
#define a 0 // Used for: solenoid
#define b 0 // Used for: solenoid
#define c 0 // Used for: solenoid
#define d 0 // Used for: solenoid
#define e 0 // Used for: solenoid
#define f 0 // Used for: solenoid
#define g 0 // Used for: solenoid
#define h 0 // Used for: solenoid

// Define drive train motor types
#define FRONT_MOTOR 0 // Used for: left_drive_train + right_drive_train
#define MIDDLE_MOTOR 1 // Used for: left_drive_train + right_drive_train
#define BACK_MOTOR 2 // Used for: left_drive_train + right_drive_train

// Define tracking wheels
#define UP_DOWN 0 // Used for: tracking_wheel
#define LEFT_RIGHT 1 // Used for: tracking_wheel

// Define if you have an auton
#define AUTON false

// Controller
controller Controller1(primary);

// Competition
competition Competition;

// Drive train
motor left_drive_train[3] = [motor(PORT2, true),                                                                                                \
                             null /* put null if there is no middle drive motor or motor(PORT#, true) if there is */, motor(PORT1, true)];
motor right_drive_train[3] = [motor(PORT4),                                                                                          \
                              null /* put null if there is no middle drive motor or motor(PORT#) if there is */, motor(PORT3)];
// Putting true after the port reverses the motor
// *** Do not put false after the port, that will freeze the motor ***

// Pneumatics
digital_out solenoid[8] = [Brain.ThreeWirePort.A, Brain.ThreeWirePort.B, Brain.ThreeWirePort.C, Brain.ThreeWirePort.D,\
                           Brain.ThreeWirePort.E, Brain.ThreeWirePort.F, Brain.ThreeWirePort.G, Brain.ThreeWirePort.H];

// Autons
// Tracking wheels
rotation tracking_wheel[2] = [rotation(PORT11, false), rotation(PORT12, false)];
// IMU
inertial IMU(PORT13);

// Scoring
motor intake_motor(PORT5);

// Match loading
//motor catapult_motor(PORT6); // Uncomment if you have a catapult
motor flywheel_motor(PORT6); // Uncomment if you have a flywheel
//motor puncher_motor(PORT6); // Uncomment if you have a puncher / slapper

// Controller inputs
// Joysticks
double left_joystick[2] = [Controller1.Axis4.position(), Controller1.Axis3.position()];
double right_joystick[2] = [Controller1.Axis1.position(), Controller1.Axis2.position()];
// Back buttons
bool back_left[2] = [Controller1.ButtonL1.pressing(), Controller1.ButtonL2.pressing()];
bool back_right[2] = [Controller1.ButtonR1.pressing(), Controller1.ButtonR2.pressing()];
// Arrow buttons
bool arrow[4] = [Controller1.ButtonUp.pressing(), Controller1.ButtonDown.pressing(),          \
                 Controller1.ButtonLeft.pressing(), Controller1.ButtonRight.pressing()];
// Action buttons
bool action[4] = [Controller1.ButtonX.pressing(), Controller1.ButtonY.pressing(),      \
                  Controller1.ButtonA.pressing(), Controller1.ButtonB.pressing()];

void pre_auton(void)
{
  Brain.Screen.clearScreen();

  print_msg();
  
  wait(1, seconds);
}
void auton(void)
{
  Brain.Screen.clearScreen();

  if(AUTON)
  {
    // Auton code
  }
}

void user_controls(void)
{
  Brain.Screen.clearScreen();

  while(true)
  {
    // Drive train controls
    left_drive_train[FRONT_MOTOR].spin(forward, left_joystick[Y], velocityUnits::pct);
    left_drive_train[BACK_MOTOR].spin(forward, left_joystick[Y], velocityUnits::pct);
    right_drive_train[FRONT_MOTOR].spin(forward, right_joystick[Y], velocityUnits::pct);
    right_drive_train[BACK_MOTOR].spin(forward, right_joystick[Y], velocityUnits::pct);

    // Intake controls
    if(back_right[L1])
    {
      intake_motor.spin(forward, 1200, velocityUnits::pct);
    } else if(back_right[L2])
    {
      intake_motor.spin(forward, -1200, velocityUnits::pct);
    } else
    {
      intake_motor.spin(forward, 0, velocityUnits::pct);
    }

    // Flywheel controls
    if(back_left[L1])
    {
      flywheel_motor.spin(forward, 1800, velocityUnits::pct);
    } else if(back_left[L2])
    {
      flywheel_motor.spin(forward, 0, velocityUnits::pct);
    } else
    {
      flywheel_motor.spin(forward, 0, velocityUnits::pct);
    }

    wait(1, msec);
  }
}

// Prints inspirational messages to the brain + controller
void print_msg(void)
{
  Brain.Screen.setCursor(6, 5);
  Brain.Screen.setPenColor(blue);
  Brain.Screen.print("Powered by Blåhaj.lib  :)");

  Controller1.Screen.setPenColor(black);
  Controller1.Screen.print("Lock in Fred :)");
}

int main() {
  Brain.Screen.clearScreen();

  // Reseting motors
  left_drive_train[FRONT_MOTOR].spin(forward, 0, velocityUnits::pct);
  left_drive_train[BACK_MOTOR].spin(forward, 0, velocityUnits::pct);
  right_drive_train[FRONT_MOTOR].spin(forward, 0, velocityUnits::pct);
  right_drive_train[BACK_MOTOR].spin(forward, 0, velocityUnits::pct);
  intake_motor.spin(forward, 0, velocityUnits::pct);
  flywheel_motor.spin(forward, 0, velocityUnits::pct);

  Competition.autonomous(auton);
  Competition.drivercontrol(user_controls);

  pre_auton();

  while(true)
  {
    wait(1, msec);
  }
}
