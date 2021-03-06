#pragma once

#ifdef GAMES_CPP
#define g_extr 
#else
#define g_extr extern
#endif

#include <Arduino.h>
#include "strategy_roles/game.h"
#include "strategy_roles/striker.h"
#include "strategy_roles/precision_shooter.h"
#include "strategy_roles/pass_and_shoot.h"
// #include "strategy_roles/keeper.h"

void initGames();

g_extr Game* striker;
g_extr Game* precision_shooter;
g_extr Game* pass_and_shoot;
// g_extr Game* keeper;