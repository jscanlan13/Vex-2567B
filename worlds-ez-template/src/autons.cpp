#include "autons.hpp"
#include "EZ-Template/drive/drive.hpp"
#include "EZ-Template/util.hpp"
#include "main.h"
#include "globals.h"
#include "pros/rtos.hpp"


/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////

const int DRIVE_SPEED = 122; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;



///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void plowingConstants() {
  chassis.set_slew_min_power(127, 127);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 1, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 1, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 7, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 13, 0, 45, 0);
}

void exit_condition_defaults() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 300, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 300, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 150, 150, 100, 500);
}

void modified_exit_condition() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 0, 3, 0, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

// . . .
// Make your own autonomous functions here!
// . . .

void FWD(double distance){
  chassis.set_drive_pid(distance, DRIVE_SPEED);
  chassis.wait_drive();
}
void FWDMax(double distance){
  chassis.set_drive_pid(distance, 127);
  chassis.wait_drive();
}
void Turn(double angle){
  chassis.set_turn_pid(angle, TURN_SPEED);
  chassis.wait_drive();
}

void SwingL(double angle){
  chassis.set_swing_pid(ez::LEFT_SWING, angle, 70);
  chassis.wait_drive();
}
void SwingR(double angle){
  chassis.set_swing_pid(ez::RIGHT_SWING, angle, 70);
  chassis.wait_drive();
}

void WP(){
  FWD(-5);
  Flicker.set_value(1);
  FWD(4);
  Turn(-40);
  Gripper.set_value(1);
  FWD(34);
  Turn(-44);
  Flicker.set_value(0);
  FWD(-25);
  Turn(-121);
  FWD(42);
  LWing.set_value(1);
  Turn(-40);
  FWD(20);
  LWing.set_value(0);
  FWD(-5);
  Turn(45);
  FWD(25);
  FWD(-2);
  Turn(-35);
  Flicker.set_value(1);
  FWD(9);
}

void FarSide(){
  RWing.set_value(1);
  FWD(41);
  RWing.set_value(0);
  Gripper.set_value(1);
  Turn(95);
  FWD(16);
  Gripper.set_value(0);
  FWD(-6);
  Turn(285);
  FWD(24);
  Gripper.set_value(1);
  Turn(95);
  FWD(26);
  Gripper.set_value(0);
  FWD(-6);
  Turn(237);
  FWD(28);
  Gripper.set_value(1);
  Turn(135);
  FWD(44);
  Turn(70);
  Flicker.set_value(1);
  FWD(10);
  Turn(-10);
  Turn(17);
  Flicker.set_value(0);
  Gripper.set_value(0);
  FWD(18);
  FWD(-8);
}

void FarWP(){
  FWD(29);
  FWD(-16);
  Turn(-92);
  FWD(36);
  Gripper.set_value(1);
}