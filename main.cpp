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

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       {author}                                                  */
/*    Created:      {date}                                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// Include the V5 Library
#include "vex.h"

// Allows for easier use of the VEX Library
using namespace vex;

// define motor types
#define FRONT_MOTOR 0
#define BACK_MOTOR 1

// Controller
controller Controler(primary);

// Drive train
motor left_drive_train[2] = [motor front_left(PORT2), motor back_left(PORT1)]; //left drive
motor right_drive_train[2] = [motor right_left(PORT2), motor right_left(PORT1)]; //right drive

// Scoring
motor intake(PORT5);
motor flywheel(PORT6);

// Pneumatics
digital_out pneumatics = digital_out(Brain.ThreeWirePort.A);

void pre_auton(void)
{
  Brain.Screen.clearScreen();
  wait(1, seconds);
}
void auton(void)
{
  Brain.Screen.clearScreen();
}

void user_controls(void)
{
  Brain.Screen.clearScreen();

  while(true)
  {
    wait(20, msec);
  }
}

// Prints inspirational messages
void print_msg()
{
  Brain.Screen.setCursor(5,4);
  Brain.Screen.setPenColor(red);
  Brain.Screen.print("Line ∞: Syntax error");
  Brain.Screen.setCursor(6, 5);
  Brain.Screen.setPenColor(green);
  Brain.Screen.print("Powered by Blåhaj.lib  :)");
  Controller.Screen.setPenColor(black);
  Controller.Screen.print("Lock in Fred :)");
}

int main() {
  Brain.Screen.clearScreen();

  competition Competition;

  Competition.autonomous(auton);
  Competition.drivercontrol(user_controls);

  pre_auton();

  while(true)
  {
    wait(100, seconds);
  }
}
