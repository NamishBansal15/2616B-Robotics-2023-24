#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "vex.h"

// Brain should be defined by default
vex::brain Brain;

// START V5 MACROS
#define waitUntil(condition)                                                   \
  do
  {                                                                            \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS

// Robot configuration code.

// Helper to make playing sounds from the V5 in VEXcode easier and
// keeps the code cleaner by making it clear what is happening.
void playVexcodeSound(const char *soundName)
{
  printf("VEXPlaySound:%s\n", soundName);
  wait(5, msec);
}

#pragma endregion VEXcode Generated Robot Configuration

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       {Rohan Bharatia + Namish Bansal}                          */
/*    Created:      {1/30/2024}                                               */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// Include the V5 Library
#include "vex.h"

// Define drive train names
#define FRONT_MOTOR 0
#define BACK_MOTOR 1

// Controller
vex::controller Controller(vex::primary);

// Drive train ports
vex::motor left_drive_train[2] = [vex::motor front_left(PORT1, true), vex::motor back_left(PORT2, true)];
vex::motor right_drive_train[2] = [vex::motor front_right(PORT3), vex::motor back_right(PORT4)];

// Scoring ports
vex::motor intake(PORT5);
vex::motor flywheel(PORT6);

// Pneumatics ports
vex::digital_out pneumatics = vex::digital_out(vex::Brain.ThreeWirePort.A);

// Competition
competition Competition;

void pre_auton(void)
{
  vex::Brain.Screen.clearScreen();
  vex::wait(1, vex::seconds);
}

void auton(void)
{
  vex::Brain.Screen.clearScreen();

  // auton code
}

void control(void)
{
  vex::Brain.Screen.clearScreen();

  while(true)
  {
    vex::wait(20, vex::msec);
  }
}

int main()
{
  vex::Brain.Screen.clearScreen();

  vex::Brain.Screen.setCursor(5,4);
  vex::Brain.Screen.setPenColor(vex::red);
  vex::Brain.Screen.print("Line ∞: Syntax error");
  vex::Brain.Screen.setCursor(6, 5);
  vex::Brain.Screen.setPenColor(vex::green);
  vex::Brain.Screen.print("Powered by Blåhaj.lib  :)");
  Controller.Screen.setPenColor(vex::cyan);
  Controller.Screen.print("Lock in Fred");

  Competition.autonomous(auton);
  Competition.drivercontrol(controls);

  while(true)
  {
    vex::wait(100, vex::msec);
  }
}
