/*
 * A combination of JoystickMouseControl
 *  Using Internal Pullup Resistors
 *  http://www.arduino.cc/en/Tutorial/JoystickMouseControl
 *  
 * And using the Arduino Nano 33 IoT's internal accelerometer
 * https://docs.arduino.cc/tutorials/nano-33-iot/imu_accelerometer
 * 
 * To get the accelerometer you will need to install LSM6DS3 library from the Library Manager
 * 
*/

// adding USB mouse ability
#include "Mouse.h"
// adding accelerometer library
// if you haven't already, get the LSM6DS3 library from the Library Manager
#include <Arduino_LSM6DS3.h>

// set pin numbers for switch, joystick axes, and LED:
const int switchPin = 2;      // switch to turn on and off mouse control
const int mouseButton = 3;    // input pin for the mouse pushButton
const int ledPin = 9;         // Mouse control LED

int responseDelay = 5;        // response delay of the mouse, in ms

bool mouseIsActive = false;    // whether or not to control the mouse
int lastSwitchState = LOW;        // previous switch state

void setup() {
  pinMode(switchPin, INPUT_PULLUP);       // the switch pin
  pinMode(mouseButton, INPUT_PULLUP);     // mouse left click input pin
  
  // take control of the mouse:
  Mouse.begin();

  //Accelerometer Setup:
  Serial.begin(9600);
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");

    while (1);
  }
}

void loop() {
  // read the switch for turning the mouse functionality on and off:
  int switchState = digitalRead(switchPin);
  // if it's changed and it's high, toggle the mouse state:
  if (switchState != lastSwitchState) {
    if (switchState == LOW) {
      mouseIsActive = !mouseIsActive;
      // turn on LED to indicate mouse state:
      digitalWrite(ledPin, mouseIsActive);
    }
  }
  // save switch state for next comparison:
  lastSwitchState = switchState;

  // read X, Y and Z accelerometer information
  // is given to us on a range from -1.0 to 1.0

  float accelX, accelY, accelZ;
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(accelX, accelY, accelZ);

    //    Serial.print(accelX);
    //    Serial.print('\t');
    //    Serial.print(accelY);
    //    Serial.print('\t');
    //    Serial.println(accelZ);
  }

  // take those numbers and adjust as necessary
  // here we multiply by 10, but could do more to make it faster
  // also, we may find that we aren't tilting the right way-
  //    may want to multiply by -1 to flip orientation
  
  int adjustedX = (int)floor((accelX*10)*-1);
  int adjustedY = (int)floor((accelY*10));

  
  Serial.print(adjustedX);
  Serial.print('\t');
  Serial.println(adjustedY);
  

  // if the mouse control state is active, move the mouse:
  if (mouseIsActive) {
    Mouse.move(adjustedX, adjustedY, 0);
  }

  // read the mouse button and click or not click:
  // if the mouse button is pressed:
  if (digitalRead(mouseButton) == LOW) {
    // if the mouse is not pressed, press it:
    if (!Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.press(MOUSE_LEFT);
    }
  }
  // else the mouse button is not pressed:
  else {
    // if the mouse is pressed, release it:
    if (Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.release(MOUSE_LEFT);
    }
  }

  delay(responseDelay);
}
