/*
  Debounce Modification
  Original code taken from Arudino site
  http://www.arduino.cc/en/Tutorial/Debounce

  This is an example of "Debouncing", or ignoring false positive button presses
  I've modified the example to use the internal pullup resistor mode
  And the button press will not only turn on the LED on your arduino (pin 13)
  But it will also press a keyboard key
  (Additional logic changes make this a momentary push button instead of a latching one)

  ///////////////
   Why debounce?
  ///////////////

  Sometimes a single button press in the real world can read as a few button presses on the Arduino
  There are many potential reasons- the mechanical connection of your buttons, electrical noise, etc
  To deal with these 'false' presses, we dedice to ignore repeated presses within a timeframe
  
  For example, if we have three button presses 1 millisecond apart
  we might think that press two and three might be false positives
  So we set up rules:
  if I get a repeated button press within a certain amount of time- ignore them
  This is the debounceDelay variable in this sketch: 50 is the amount of time we're using
  You can play with this number to see the difference in functionality.

  Note, debounce just ignores repeats within a timeframe-
  it doesn't "know" if they're intended or not
  If the user really *did* press the button twice within 50ms,
  the second legitimate press would be ignored
  So adjust as much as you need for your particular uses

  This example is for *one* button. Do to this with multiple buttons, each would need their own
*/


#include "Keyboard.h"

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;    // the number of the pushbutton pin
const int ledPin = 13;      // the number of the LED pin

// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = HIGH;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the input detected a change
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers or you get false positive keypresses

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  // set initial LED state
  digitalWrite(ledPin, ledState);

  //Activate our keyboard simulating ability
  Keyboard.begin();
}

void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from HIGH to LOW on an internal pullup), and you've waited long enough
  // since the last press to ignore any noise:

  // If the input pin changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:
    
    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == LOW) {
        ledState = HIGH;
        Keyboard.write('w');
      } else {
        ledState = LOW;
      }
    }
  }

  // set the LED:
  digitalWrite(ledPin, ledState);

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}



/* Comment section for testing our USB keyboard key presses 
 * 
 * 
 *
 * wwwwwwwwww
 *
 * 
 */
