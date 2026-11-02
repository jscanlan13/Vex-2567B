#include "main.h"
#include "lemlib/api.hpp"
#include "lemlib/logger/stdout.hpp"
#include "pros/misc.h"

// controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// drive motors
pros::Motor lF(-18, pros::E_MOTOR_GEARSET_06);
pros::Motor lM(19, pros::E_MOTOR_GEARSET_06);
pros::Motor lB(20, pros::E_MOTOR_GEARSET_06);
pros::Motor rF(5, pros::E_MOTOR_GEARSET_06);
pros::Motor rM(-4, pros::E_MOTOR_GEARSET_06);
pros::Motor rB(-16, pros::E_MOTOR_GEARSET_06);

// motor groups
pros::MotorGroup leftMotors({lF, lM, lB}); // left motor group
pros::MotorGroup rightMotors({rF, rM, rB}); // right motor group

// Inertial Sensor on port 14
pros::Imu imu(15);

pros::Motor IntakeL(17, pros::E_MOTOR_GEARSET_06);
pros::Motor IntakeR(-14, pros::E_MOTOR_GEARSET_06);
pros::MotorGroup Intake({IntakeL, IntakeR});

pros::Motor Cata(8, pros::E_MOTOR_GEARSET_06);

pros::ADIDigitalOut ClimbPTO ('B');
pros::ADIDigitalOut FWings ('C');
pros::ADIDigitalOut IntakePTO ('F');
pros::ADIDigitalOut Lift ('G');
pros::ADIDigitalOut BLWings ('H');
pros::ADIDigitalOut BRWings ('A');

pros::Rotation CataRotation(2);

// drivetrain settings
lemlib::Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              11.25, // 10 inch track width
                              lemlib::Omniwheel::NEW_275, // using new 2.75" omnis
                              600, // drivetrain rpm is 360
                              2 // chase power is 2. If we had traction wheels, it would have been 8
);

// lateral motion controller
lemlib::ControllerSettings linearController(17, // proportional gain (kP)
                                            0, // integral(kI)
                                            30, // derivative gain (kD)
                                            0, //windup range
                                            1, // small error range, in inches
                                            100, // small error range timeout, in milliseconds
                                            3, // large error range, in inches
                                            500, // large error range timeout, in milliseconds
                                            10 // maximum acceleration (slew)
);


// angular motion controller
lemlib::ControllerSettings angularController(2, // proportional gain (kP)
                                            0, //integral (kI)
                                             10, // derivative gain (kD)
                                             0, //windup range
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             3, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             20 // maximum acceleration (slew)
);

// sensors for odometry
// note that in this example we use internal motor encoders, so we don't pass vertical tracking wheels
lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1, set to nullptr as we don't have one
                            nullptr, // vertical tracking wheel 2, set to nullptr as we don't have one
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// create the chassis
lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors);

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors

    // the default rate is 50. however, if you need to change the rate, you
    // can do the following.
    // lemlib::bufferedStdout().setRate(...);
    // If you use bluetooth or a wired connection, you will want to have a rate of 10ms

    // for more information on how the formatting for the loggers
    // works, refer to the fmtlib docs

    // thread to for brain screen and position logging
    pros::Task screenTask([&]() {
        lemlib::Pose pose(0, 0, 0);
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            pros::lcd::print(3, "Rotation: %f", CataRotation.get_angle());
            // log position telemetry
            lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
            // delay to save resources
            pros::delay(50);
        }
    });
}

/**
 * Runs while the robot is disabled
 */
void disabled() {}

/**
 * runs after initialize if the robot is connected to field control
 */
void competition_initialize() {}

// get a path used for pure pursuit
// this needs to be put outside a function
ASSET(example_txt); // '.' replaced with "_" to make c++ happy
ASSET(path1_txt);
ASSET(path2_txt);
ASSET(path3_txt);
ASSET(path4_txt);
ASSET(path5_txt);
ASSET(pathA_txt);
ASSET(pathPush_txt);
ASSET(path6_txt);
ASSET(path7_txt);
/**
 * Runs during auto
 *
 * This is an example autonomous routine which demonstrates a lot of the features LemLib has to offer
 */
void autonomous() {

chassis.setPose(45.153, 58, 135);
    //chassis.moveToPoint(10, 10, 7000);
    //chassis.moveToPose(10, 10, 0, 7000);
    // example movement: Move to x: 20 and y:15, and face heading 90. Timeout set to 4000 ms
//chassis.moveTo(20, 15, 90, 4000);
    // example movement: Turn to face the point x:45, y:-45. Timeout set to 1000
    // dont turn faster than 60 (out of a maximum of 127)
// chassis.turnTo(45, -45, 1000, true, 60);
    // example movement: Follow the path in path.txt. Lookahead at 15, Timeout set to 4000
    // following the path with the back of the robot (forwards = false)
    // see line 116 to see how to define a path

Intake = -127;
chassis.follow(path1_txt, 10, 2000, true);
Intake = 0;
Lift.set_value(1);
Cata = 127;
FWings.set_value(1);
pros::delay(2000);
while(true){
    if(CataRotation.get_angle()>300 && CataRotation.get_angle() < 320){
        break;
    }
    pros::delay(20);
}
Cata = 0;
Lift.set_value(0);
FWings.set_value(0);
chassis.turnTo(60.265, 30.931, 500);
chassis.follow(pathA_txt, 8, 1000);
chassis.moveToPoint(59.102, 46, 1000, false);
chassis.turnTo(37.616, 43.303, 1000);
chassis.follow(path2_txt, 21, 5000, true);
chassis.waitUntil(39);
FWings.set_value(1);
chassis.waitUntil(104);
FWings.set_value(0);
chassis.moveToPoint(26.142, -23.000, 1000, false, 127, true);
chassis.turnTo(52.682, -39.212, 800, true);
chassis.follow(path3_txt, 14, 5500);
chassis.moveToPoint(-62.461, -40.000, 1000, false, 127, true);
chassis.follow(pathPush_txt, 10, 1000, true);
chassis.moveToPoint(-62.461, -40.000, 1000, false, 127, true);
chassis.turnTo(0.499, -25.543, 1000);
chassis.follow(path4_txt, 14, 4000, true);
chassis.waitUntil(40);
FWings.set_value(1);
chassis.waitUntil(77);
FWings.set_value(0);
chassis.moveToPoint(-24, -9.248, 1300, false);
chassis.turnTo(-22, 5, 500, true);
chassis.follow(path5_txt, 14, 3000, true);
chassis.waitUntil(9);
FWings.set_value(1);
chassis.waitUntil(36);
FWings.set_value(0);
chassis.moveToPoint(-36.618, 6.286, 1300, false);
chassis.turnTo(-41.219, 44.899, 500);
chassis.follow(path6_txt, 10, 8000, true);
chassis.moveToPoint(-62.361, 36, 1300, false);
chassis.turnTo(-43.204, 67.848, 500);
chassis.follow(path7_txt, 14, 4000);
    // wait until the chassis has travelled 10 inches. Otherwise the code directly after
    // the movement will run immediately
    // Unless its another movement, in which case it will wait
//chassis.waitUntil(10);
//pros::lcd::print(4, "Travelled 10 inches during pure pursuit!");
    // wait until the movement is done
//chassis.waitUntilDone();
//pros::lcd::print(4, "pure pursuit finished!");
}

/**
 * Runs in driver control
 */
void opcontrol() {
    // controller
    // loop to continuously update motors
    while (true) {
        // get joystick positions
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

        chassis.tank(leftY, rightY);
        // delay to save resources
        pros::delay(10);
    }
}