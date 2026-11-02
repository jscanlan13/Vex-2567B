#include "globals.h"
#include "pros/motors.hpp"
#include "pros/adi.hpp"
#include "pros/rotation.hpp"
#include "main.h"

#define LEFT_INTAKE 3
#define RIGHT_INTAKE 3

int pullback =22;
int buffer = 3;
bool toggle;

pros::Motor Cata(8);

pros::Rotation cata_Rotation(2);

pros::ADIDigitalOut ClimbPTO ('A');
pros::ADIDigitalOut Gripper ('B');
pros::ADIDigitalOut ClimbRelease ('C');
pros::ADIDigitalOut Flicker ('F');
pros::ADIDigitalOut LWing ('H');
pros::ADIDigitalOut RWing ('G');

pros::Motor L1(-18);
pros::Motor L2(19);
pros::Motor L3(20);
pros::Motor PTOL(17);
pros::Motor R1(5);
pros::Motor R2(-4);
pros::Motor R3(-16);
pros::Motor PTOR(-14);

pros::Motor Intake(-2);
