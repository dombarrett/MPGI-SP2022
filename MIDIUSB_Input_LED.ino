/*
 * Modification of MIDIUSB_test.ino
 * Modified by Dominic Barrett Spring 2022
 *
 * Original Created: 4/6/2015 10:47:08 AM
 * Author: gurbrinder grewal
 * Modified by Arduino LLC (2015)
 * 
 */ 

#include "MIDIUSB.h"


//For the LED circuit:
// Short leg of your LED (-,cathode) to ground 
// 220 ohm resistor on the long leg of your LED (+,anode)
// Resistor goes to led pin (right now is 9)


// constants won't change. Used here to set a pin number:
const int ledPin =  9; // the number of the LED pin
int ledValue = 0; //How bright the LED will be

void setup() {
  Serial.begin(115200);
}

void loop() {

  /*
   
  What kind of MIDI message is our Arduino recieving?
  On the lower level of hardware, we are looking at the raw MIDI "Events"
  These are the serial messages that follow a specific convention

  Lots is written about the MIDI message specification
  It can be very complicated!
  A brief summary is here:
  https://www.songstuff.com/recording/article/midi_message_format/


  However, if you just want to listen to Note On, Note Off, and CC messages:
  Just use the code below and don't worry about understanding the messages!

  */
  
  midiEventPacket_t rx;
  do {
    rx = MidiUSB.read();
    if (rx.header != 0) {
      //Many of the resources you see online for decoding these serial MIDI messages involve hexidecimal numbers
      //In this example, we can set our Serial prints to decode in "HEX" mode for this purpose
      //Serial.print("Received: ");
      //Serial.print(rx.header, HEX);
      //Serial.print("-");
      //Serial.print(rx.byte1, HEX);
      //Serial.print("-");
      //Serial.print(rx.byte2, HEX);
      //Serial.print("-");
      //Serial.println(rx.byte3,HEX);

      //What to do if the Arduino sees a Note On:
      if(rx.header==9){
        //a 9 midi serial message header is a "Note On" event
        //Serial.print("Note ON");
        //While hexidecimal is the usual way of thinking of these messages in serial
        //We don't have to view them this way- traditional numbers may work better for our purposes
        //So we leave out the ",HEX" addition to our print lines
        //Serial.print(rx.byte2);
        //Serial.print(", velocity of:");
        //Serial.println(rx.byte3);
      }

      //What to do if the Arduino sees a Note Off:
      if(rx.header==8){
        //a 8 midi serial message header is a "Note Off" event
        //Serial.print("Note OFF from note");
        //Serial.print(rx.byte2);
        //Serial.print(", velocity of:");
        //Serial.println(rx.byte3);
      }

      //What to do if the Arduino sees a Control Change
      if(rx.header==11){
        //an 11, or hexidemical "B", midi serial message header is a "Control Change" or "Continuous Change" event
        //Serial.print("CC Message from CC number:");
        //Serial.print(rx.byte2);
        //Serial.print(", value of:");
        //Serial.println(rx.byte3);

        //Choose a specific CC number to listen to:
        if(rx.byte2==1){
          //If we get a new value from CC 1, use that to fade the LED
          //analogWrite(ledPin, rx.byte3);
          ledValue=rx.byte3;
        }
      }
      
    }

  } while (rx.header != 0);


    //This is will fade our LED
    //However, this may be delayed and choppy
    //That is because of the "Serial.print" commands
    //If you comment them out, the LED will be much smoother and more responsive
    analogWrite(ledPin, ledValue);

  
}



/*
 * 
 * Sending MIDI from the Arduino
 * Not used in this sketch, but leaving the functions here
 * in the case you wish to use them later
 * 
 * This also shows that, yes, you can send and receive MIDI at the same time
 * 
 */


// First parameter is the event type (0x09 = note on, 0x08 = note off).
// Second parameter is note-on/note-off, combined with the channel.
// Channel can be anything between 0-15. Typically reported to the user as 1-16.
// Third parameter is the note number (48 = middle C).
// Fourth parameter is the velocity (64 = normal, 127 = fastest).

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

// First parameter is the event type (0x0B = control change).
// Second parameter is the event type, combined with the channel.
// Third parameter is the control number number (0-119).
// Fourth parameter is the control value (0-127).

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}
