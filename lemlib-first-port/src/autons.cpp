#include "autons.h"
#include "main.h"
#include "lemlib/api.hpp"

void PIDTest(){
    chassis.moveTo(0,10, 1000);
    chassis.turnTo(10,10, 1000);
    chassis.moveTo(10,10, 1000);
    chassis.moveTo(0,0, 1000);

}