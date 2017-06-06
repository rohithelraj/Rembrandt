/*
 * Move 
 *Ostacle detection and avoidance
 */

// --- Includes ---

#include <Wire.h> 
#include <Zumo32U4.h>

// --- Robot Components ---

Zumo32U4LCD lcd;
Zumo32U4ProximitySensors proxSensors;
Zumo32U4Motors motors;


// --- Constants ---

const uint16_t motorSpeed = 100;
int delay_set = 5;
bool Obstacle_state = false;
int LeftSensor = 0;
int RightSensor = 0;


// --- Support Functions ---

// Turn left
void turnLeft() {
  motors.setSpeeds(-motorSpeed, motorSpeed);
}

// Turn right
void turnRight() {
  motors.setSpeeds(motorSpeed, -motorSpeed); 
}

// Stop
void stop() {
  motors.setSpeeds(0, 0);
  delay_set = 5;
}

// Go forward
void forward() {
  motors.setSpeeds(motorSpeed, motorSpeed);
}

// --- Setup ---
void setup() {

  // Proximity sensors
  proxSensors.initThreeSensors();
}

// --- Main Loop ---
void loop() {
  if(Obstacle_state==false)
  {
    sense();
  }
  else
  {
    obstacle_Avoidance();
  }

  delay(delay_set);
}

void sense()
{
  forward();
  delay_set=5;
  // Proximity sensors
  proxSensors.read();
  //read sensor values
  LeftSensor = proxSensors.countsLeftWithLeftLeds();
  RightSensor = proxSensors.countsRightWithRightLeds();
  if (LeftSensor >= 6 && RightSensor >= 6)
  {
    stop();
    Obstacle_state=true;
    lcd.gotoXY(0, 0);
    lcd.print("obstacle Detected!");
  }  
  lcd.gotoXY(0, 1);
  lcd.print(" ");
  lcd.print(LeftSensor);
  lcd.print(" ");
  lcd.print(RightSensor);
}
//--- desired obstacle path
void obstacle_Avoidance()
{
    
    turnLeft();
    delay(1200);
    forward();
    delay(1700);
    turnRight();
    delay(1200);
    forward();
    delay(3200);
    turnRight();
    delay(1200);
    forward();
    delay(1700);
    turnLeft();
    delay(1200);
    stop();
    delay_set= 10000;
}
 



