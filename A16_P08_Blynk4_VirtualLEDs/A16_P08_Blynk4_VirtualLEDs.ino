/*
Blynk 4: Virtual LEDs
Change ssid, password and token
*/

char ssid[] = "";
char password[] = "";
char token[] = "";

#define BLYNK_DEBUG
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266_SoftSer.h>
#include <BlynkSimpleShieldEsp8266_SoftSer.h>

// Set ESP8266 Serial object
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(11, 12); // RX, TX

ESP8266 wifi(EspSerial);

#define BUTTON 7

//Virtual LED Widgets
 WidgetLED led1(V0);
 WidgetLED led2(V1);

void setup()
{
  // Set console baud rate
  Serial.begin(19200);
  EspSerial.begin(19200);

  Blynk.begin(token, wifi, ssid, password);

  pinMode(BUTTON, INPUT_PULLUP);
}

void loop()
{
  Blynk.run();
  checkPin();
  checkPoti(); 
}

boolean currState = false ;

void checkPin()
{
  if (!digitalRead(BUTTON))
  {
    currState = !currState;

    //write current state to virtual LED
    if (currState){
       led1.on();
    }
    else{
       led1.off();
    }

    //wait till button is released
    while (!digitalRead(BUTTON)){  
    }
   
  }
}
int lastValue = 0;

void checkPoti()
{
  //read A0 and convert it to values 0-255
  int currValue = map(analogRead(A0), 0, 1023, 0, 255);

  //if values have changed write to virtual led2
  if (!(currValue == lastValue)){
      lastValue = currValue;
      Blynk.virtualWrite(V1, currValue);
  }
}

