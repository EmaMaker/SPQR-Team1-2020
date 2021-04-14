#pragma once

#include <Arduino.h>

#include "behaviour_control/ds_ctrl.h"
#include "systems/systems.h"

#include "vars.h" 

#define S1I A7
#define S1O A6
#define S2I A2
#define S2O A3
#define S3I A1
#define S3O A0
#define S4I A9
#define S4O A8

#define LINE_THRESH_CAM 300
#define EXIT_TIME 250
#define LINES_EXIT_SPD 350

class LineSysCamera : public LineSystem{

    public:
        LineSysCamera();
        LineSysCamera(vector<DataSource*> in_, vector<DataSource*> out);

        void update() override;
        void test() override;
        void outOfBounds();
        void checkLineSensors();
        
    private:
        vector<DataSource*> in, out;
        DataSource* ds;
        bool fboundsX, fboundsY, fboundsOX, fboundsOY, slow;
        int inV, outV, linesensOldX, linesensOldY, value, linetriggerI[4], linetriggerO[4], linepins[4], i;
        unsigned long exitTimer;
        int outDir, outVel;
        byte linesens;
};