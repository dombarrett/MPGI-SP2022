#include <CapacitiveSensor.h>
#include <Keyboard.h>

/* A variation of the CapacitiveSensor Library Demo Sketch by Paul Badger 2008
 *  by Dominic Barrett
 *  
 *  To be used with the CapacitiveSensor libarary,
 *  which can be found in the Arduino Library Manager name "CapacitiveSensor"
 *  You can read more about the library here:
 *  https://playground.arduino.cc/Main/CapacitiveSensor/
 *  
 *  
 *  Capacitive sensing will allow you to detect a person's touch-
 *  without having to complete a circuit.
 *  This library allows wo digital pins to measure the capaciticance between them
 *  
 *  I used a smaller resistor value of 910k, which corresponds more to direct touch,
 *  But with larger resistors you get readings without directly touching your sensor
 *  However, those readings will be slower. Try different resistors to see what works for you!
 *  
 *  
 *  From Original sketch:
 *  Uses a high value resistor e.g. 10M between send pin and receive pin
 *  Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 *  Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 * 
 * 
 * 
 */


CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);
// Resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired

CapacitiveSensor   cs_4_6 = CapacitiveSensor(4,6);
// The first argument is the "send" pin (here, 4) and the second argument is the "receive" sensor pin (here, 6)

CapacitiveSensor   cs_4_8 = CapacitiveSensor(4,8);
// This can be continued on with digital pins, with the 4 pin being similar to a "ground rail" of sorts



void setup()                    
{
   //cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   Serial.begin(9600);


   pinMode(10, INPUT_PULLUP); //Using digital pin 10 for a internal pullup pushbutton
   Keyboard.begin();
}

void loop()                    
{
    long start = millis();
    long total1 =  cs_4_2.capacitiveSensor(30);
    //long total2 =  cs_4_6.capacitiveSensor(10);
    //long total3 =  cs_4_8.capacitiveSensor(10);

    //I've commented out the 2nd and 3rd out,
    // because if you set up the capacitive sensing without the circuitry,
    // there will be a long delay in your serial reads.
    //If you see a big delay, make sure all your circuits are properly connected
    // -then your readings should be faster
    

    Serial.print(millis() - start);        // check on performance in milliseconds- how fast are we reading
    Serial.print("\t");                    // tab character for debug windown spacing

    Serial.print(total1);                  // print sensor output 1
    Serial.println("\t");
    
    delay(10);                             // arbitrary delay to limit data to serial port


    //Next, we will want to see what values we get that are useable
    //With capacitive sensing, there are many factors that can change your readings
    //Your resistor values, conductive materials, if those are coated or covered, even the ambient humidity
    //But you can get a reading, see what are usable to you, and plan accordingly

    //Right now with just a jumper wire, I get a non-touch reading of 0 to 50
    //When I touch with a small amount of my skin, I get a reading of around 800-1200
    //When I grab the end of the wire with two fingers I get 3500
    //When I grab and squeeze, for maximum surface area, I get a maximum of around 4100


    //I could use multiple capacitive touch sensors to trigger different keyboard keys
    //But I could also use their analog stlye readings to modify other digital events
    //What about a high value being a "caps lock" or "shift" type functionality?

    if (digitalRead(10) == LOW) { //if the button is being pressed
      //And we're grabbing normally, small 'a'
        if(total1>2000 && total1<4000){
          Keyboard.write('a');
        }
         
      //But if we're grabbing tight, capital 'A'
        if(total1>4000){
          Keyboard.write('A');
        }
         
    }

    //To note- these values did change when I was working with the circuit
    //So I would tweak them as needed
    //If we wanted to work with our own capacitive touch sensors in more finished projects
    //We might want to build in a way to calibrate our values without having to open the arduino IDE

}



/* Code comment area to test my keyboard presses
 * 
 * 
 *
 *
 *
 * 
 */
