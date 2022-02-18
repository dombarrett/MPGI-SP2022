/*
  Keyboard Control using internal pullups
  A slight modification of Tom Igoe's Keyboard an Mouse example here:
  http://www.arduino.cc/en/Tutorial/KeyboardAndMouseControl

  "Controls the mouse from five pushbuttons on an Arduino Leonardo, Micro or Due.

  Hardware:
  - five pushbuttons attached to D2, D3, D4, D5, D6"
  
  Which pin is which number? We can look at our pinouts by searching online
  But I've included the Nano 33 IoT pinout diagram here:
  https://docs.arduino.cc/static/d77fe4114922e80804b6ebfd2e586316/ABX00027-pinout.png

 */

#include "Keyboard.h"

// set pin numbers for the five buttons:
const int oneButton = 2;
const int twoButton = 3;
const int threeButton = 4;
const int fourButton = 5;
const int fiveButton = 6;

const int otherButton = 7;

void setup() {
  // initialize the buttons' inputs
  // instead of "INPUT", we're using "INPUT_PULLUP"
  // this uses internal pull up resistors for the inputs
  
  pinMode(oneButton, INPUT_PULLUP);
  pinMode(twoButton, INPUT_PULLUP);
  pinMode(threeButton, INPUT_PULLUP);
  pinMode(fourButton, INPUT_PULLUP);
  pinMode(fiveButton, INPUT_PULLUP);

  pinMode(otherButton, INPUT_PULLUP);

  Keyboard.begin();
}

void loop() {
  // use the pushbuttons to control the keyboard
  // note how we are checking for LOW instead of the usual HIGH
  // this is how we check to see if a button is pressed when using INPUT_PULLUP mode
  
  if (digitalRead(oneButton) == LOW) {
    Keyboard.write('w');
  }
  if (digitalRead(twoButton) == LOW) {
    Keyboard.write('a');
  }
  if (digitalRead(threeButton) == LOW) {
    Keyboard.write('s');
  }
  if (digitalRead(fourButton) == LOW) {
    Keyboard.write('d');
  }
  if (digitalRead(fiveButton) == LOW) {
    Keyboard.write(' ');
  }


  // with the Keyboard.write() approach, you will see LOTS of characters typed out
  // thats because the arduino taps the key for each time it runs the loop()
  // (which is *many* times per second)


  // however, maybe we don't want that functionality
  // perhaps we want a "press and hold" type functionality
  // in that case, we would use Keyboard.press() and Keyboard.release()
  
  if (digitalRead(otherButton) == LOW) {
    Keyboard.press('q');
  } else {
    Keyboard.release('q');   
  }
  
  // also note there is a Keyboard.releaseAll() function
  // to see more about what the Keyboard functionality can do, check out the reference page here:
  // https://www.arduino.cc/reference/en/language/functions/usb/keyboard/

  // what about keyboard keys like delete, shift, tab, etc?
  // use the ASCII key code. How do I find that?
  // https://keycode.info/
  // for example, Backspace is 8
  // so that would look like: Keyboard.write(8);
  
}


/* Using the keyboard? WATCH OUT
 * Maybe put your cursor down here in the comments before testing
 * That way you won't mess up your program
 * 
 * 
 * 
 * 
 * 
 * 
 */
