#pragma once

#include <Arduino.h>

#include "behaviour_control/complementary_filter.h"
#include "motors_movement/motor.h"

#include "PID_v2.h"


//BEST NUMBERS YET
//USE MOVING AVERAGE AND ANGLE WRAP
#define KP 0.8
#define KI 0.0
#define KD 0.025

#define KSPD 0.3

#define UNLOCK_THRESH 800

#define MAX_VEL 150
#define MAX_VEL_EIGTH 120
#define MAX_VEL_HALF 75
#define MAX_VEL_3QUARTERS 112
#define MAX_VEL_QUARTER 38

class DriveController{

    public:

        DriveController(Motor* m1_, Motor* m2_, Motor* m3_, Motor* m4_);
        
        void drive(int dir=0, int speed=0, int tilt=0);
        void prepareDrive(int dir, int speed, int tilt=0);
        void drivePrepared();
        float updatePid();
        float torad(float f);

        int vxp, vyp, vxn, vyn;
        bool canUnlock;
        unsigned long unlockTime;
        Motor* m1;
        Motor* m2;
        Motor* m3;
        Motor* m4;

    private:
        PID* pid;
        ComplementaryFilter* speedFilter;
        ComplementaryFilter* dirFilter;
        int pDir, pSpeed, pTilt, oldSpeed;
        float x, y, vx, vy, speed1, speed2, speed3, speed4, pidfactor, delta;

        double input, output, setpoint;
        
};