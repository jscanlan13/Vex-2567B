#include "api.h"
#include "lemlib/api.hpp"

extern pros::Motor L1;
extern pros::Motor L2;
extern pros::Motor L3;
extern pros::Motor L4;
extern pros::Motor R1;
extern pros::Motor R2;
extern pros::Motor R3;
extern pros::Motor R4;

extern pros::MotorGroup leftSide;
extern pros::MotorGroup rightSide;

extern pros::Imu inertial_sensor;

extern lemlib::Drivetrain_t drivetrain;
extern lemlib::OdomSensors_t sensors;
extern lemlib::ChassisController_t lateralController;
extern lemlib::ChassisController_t angularController;
extern lemlib::Chassis chassis;