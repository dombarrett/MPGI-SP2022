
/*
Example code for OSC communication and internal pullup resistors
Based off of the OscWifi example code for the ArduinoOSC library

In order to run this code you will need to:
  install WiFiNINA from the arduino library manager,
  install ArduinoOSC from the arduino library manager,
  (also assuming you have the SAMD Board definitions required for the Arduino Nano IoT 33)

You will also need to be on a WiFi network with a device that can recieve OSC messages
This means you'll need:
  the network name and password
  the local ip address of the device you want to send to
  the network port that ip address will receive OSC messages on
*/

#include <ArduinoOSC.h>

// WiFi stuff
const char* ssid = "TripMateNano-571E"; //YOUR WifiSSD name
const char* pwd = "11111111"; //YOUR PASSWORD WATCH OUT
const IPAddress ip(192, 168, 1, 201); //The local ip of the Arduino is whatever you say it is
const IPAddress gateway(192, 168, 1, 1);
const IPAddress subnet(255, 255, 255, 0);


const char* host = "10.10.10.1";
/*
What ip are you sending the messages to? Your computer?
Commonly, it will be something starting with 192.168.x.x
But right now, mine is 10.10.10.1 Yours may be different.

Find your IP address... if you are connected to the internet
https://www.avg.com/en/signal/find-ip-address

If you aren't on the internet,
On Windows:
Select Start > Settings > Network & Internet > Wi-Fi
then select the Wi-Fi network you are connected to

On MacOS:
Select Apple Menu > System Preferences > Network
Select Wi-Fi on the left side menu and look at the network information on the right
*/


const int publish_port = 54445;  //the port we will use to receive on the computer
// send / receive varibales


//The variables we will send
int button1State, button2State, button3State, button4State, button5State;

// We can send float and string variables with this library, as well


void setup()
{
    Serial.begin(115200);
    delay(2000);

    //Setting up our buttons
    //More direct than the previous MIDI example sketch- we have 5 inputs, so activate all 5 as INPUT_PULLUP
    pinMode(2, INPUT_PULLUP);
    pinMode(3, INPUT_PULLUP);
    pinMode(4, INPUT_PULLUP);
    pinMode(5, INPUT_PULLUP);
    pinMode(6, INPUT_PULLUP);
    

    // WiFi stuff (no timeout setting for WiFi)
    #ifdef ESP_PLATFORM
        WiFi.disconnect(true, true); // disable wifi, erase ap info
        delay(1000);
        WiFi.mode(WIFI_STA);
    #endif
        WiFi.begin(ssid, pwd);
        WiFi.config(ip, gateway, subnet);
        while (WiFi.status() != WL_CONNECTED) { Serial.print("."); delay(500); }
        Serial.print("WiFi connected, IP = "); Serial.println(WiFi.localIP());


    //OscWiFi.publish(host, publish_port, "/publish/func", &millis, &micros)
    //    ->setIntervalMsec(500.f);

    //OscWiFi.publish(host, publish_port, "/publish/func", button2State)
    //    ->setFrameRate(60.f);

    OscWiFi.publish(host, publish_port, "/publish/func", button1State, button2State, button3State, button4State, button5State)
        ->setFrameRate(60.f);

}

void loop()
{
    //For all five of our input pins (2-6), read the high/low
    //With internal pullup resistors, we pull to ground for a button press
    //which means low=pressed, and all pins are default set to high
    //Hence: if low, button state is 1, if high button state is 0
    
      if (digitalRead(2) == LOW)
      {
        button1State = 1;
      }
      else
      {
        button1State = 0;
      }


      if (digitalRead(3) == LOW)
      {
        button2State = 1;
      }
      else
      {
        button2State = 0;
      }
      

      if (digitalRead(4) == LOW)
      {
        button3State = 1;
      }
      else
      {
        button3State = 0;
      }
      

      if (digitalRead(5) == LOW)
      {
        button4State = 1;
      }
      else
      {
        button4State = 0;
      }

      if (digitalRead(6) == LOW)
      {
        button5State = 1;
      }
      else
      {
        button5State = 0;
      }




    //Send and Receive OSC messages:
    OscWiFi.update();

    // or do that separately, if you are using the library in a different way
    // OscWiFi.parse(); // to receive osc
    // OscWiFi.post(); // to publish osc
}
