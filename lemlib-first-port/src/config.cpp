#include "main.h"
#include "config.h"
#include "lemlib/api.hpp"

/////////////////Motors and Sensors/////////////

pros::Motor L1(11, pros::E_MOTOR_GEARSET_06, false);
pros::Motor L2(12, pros::E_MOTOR_GEARSET_06, false);
pros::Motor L3(13, pros::E_MOTOR_GEARSET_06, true);
pros::Motor L4(14, pros::E_MOTOR_GEARSET_18, false);
pros::Motor R1(20, pros::E_MOTOR_GEARSET_06, true);
pros::Motor R2(19, pros::E_MOTOR_GEARSET_06, true);
pros::Motor R3(18, pros::E_MOTOR_GEARSET_06, false);
pros::Motor R4(17, pros::E_MOTOR_GEARSET_06, true);

pros::MotorGroup leftSide({L1, L2, L3, L4});
pros::MotorGroup rightSide({R1, R2, R3, R4});

pros::Imu inertial_sensor(10);



///////////////////lemlib setup//////////////////////



lemlib::Drivetrain_t drivetrain {
	&leftSide, // left motors
	&rightSide, // right motors
	10, // track width
	2.75, // wheel diameter
	600 // wheel rpm
};

lemlib::OdomSensors_t sensors {
    nullptr, // vertical tracking wheel 1
    nullptr, // vertical tracking wheel 2
    nullptr, // horizontal tracking wheel 1
    nullptr, // horizontal tracking wheel 2
    &inertial_sensor // inertial sensor
};

//forward/backward PID
lemlib::ChassisController_t lateralController {
    10, // kP
    40, // kD
    1, // smallErrorRange
    100, //smallErrorTimeout
    3, //largeErrorRange
    500, // largeErrorTimeout
    7 // slew rate
};

// turning PID
lemlib::ChassisController_t angularController {
    4, // kP
    40, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    40 // slew rate
};

//create the chassis
lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);