#pragma once

#include "data_source.h"
#include "data_source_ball.h"
#include "motor.h"
#include "drivecontroller.h"
#include "sensors.h"
#include "vars.h"
#include "data_source_bno055.h"
#include "goalie.h"
#include "keeper.h"

class Game{
    public:
        Game();
        //void keeper();
        //void goalie();
        //void ballBack();
        bool role, attackGoal; //1->goalie 0->keeper, 1->yellow 0->blue
        //~Game();
};