#include "api.h"
#include "pros/rotation.hpp"

extern pros::Motor Cata;


extern pros::ADIDigitalOut LWing;
extern pros::ADIDigitalOut RWing;
extern pros::ADIDigitalOut ClimbPTO;
extern pros::ADIDigitalOut Gripper;
extern pros::ADIDigitalOut ClimbRelease;
extern pros::ADIDigitalOut Flicker;


extern pros::Motor L1;
extern pros::Motor L2;
extern pros::Motor L3;
extern pros::Motor PTOL;
extern pros::Motor R1;
extern pros::Motor R2;
extern pros::Motor R3;
extern pros::Motor PTOR;

void FWD(double distance);
void Turn(double angle);
void SwingL(double angle);
void SwingR(double angle);
