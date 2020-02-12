#include <Arduino.h>

#include "sensors.h"
#include "games.h"
#include "status_vector.h"

void setup() {
  delay(1500);

  DEBUG.begin(9600);
  initStatusVector();
  initSensors();
  initGames();
  
  delay(1500);
}


void loop() {
  updateSensors();

  goalie->play(role==1);
  keeper->play(role==0);  

  Serial.println(CURRENT_DATA_READ.IMUAngle);

  // Last thing to do: movement and update status vector
  drive->drivePrepared();  
  updateStatusVector();
} 
