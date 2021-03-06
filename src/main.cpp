#include <Arduino.h>

#define VARS

#include "behaviour_control/status_vector.h"
#include "sensors/sensors.h"
#include "strategy_roles/games.h"
#include "vars.h"
#include "test_menu.h"
#include "motors_movement/roller.h"

void updateRoller();

TestMenu* testmenu;

bool striker_condition = false;
bool keeper_condition = false;

void setup() {
  pinMode(BUZZER, OUTPUT);
  
  tone(BUZZER, 220, 250);
  delay(1500);
  DEBUG.begin(115200);
    
  for(int i = 0; i < 360; i++){
      sins[i] = (float) sin((i*3.14/180));
      cosins[i] =  (float) cos((i*3.14/180));
  }

  testmenu = new TestMenu();
  tone(BUZZER, 240, 250);
  initStatusVector();
  delay(250);

  tone(BUZZER, 260, 250);
  initSensors();
  delay(500);
  
  tone(BUZZER, 320, 250);
  initGames();
  delay(250);

  //Startup sound
  tone(BUZZER, 350.00, 250);

  drive->prepareDrive(0,0,0);
}

void loop() {
  updateSensors();
  drive->resetDrive();
  
  striker_condition = role == HIGH;
  striker->play(1);

  // if(role) precision_shooter->play(1);
  // else pass_and_shoot->play(1);

  // keeper_condition = role == LOW;
  // keeper->play(keeper_condition);
  // testmenu->testMenu();

  // // Last thing to do: movement and update status vector
  drive->drivePrepared();  
  updateStatusVector();
}