/*
  Blnky9: PushAlarm
  Change ssid, password and token
*/

char ssid[] = "";
char password[] = "";
char token[] = "";

String passwordAlarm = "password";
String  alarmMsg = "Alarm! Someone touched the NanoESP!";

#define BLYNK_DEBUG
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266_SoftSer.h>
#include <BlynkSimpleShieldEsp8266_SoftSer.h>
#include <SimpleTimer.h>

// Set ESP8266 Serial object
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(11, 12); // RX, TX

ESP8266 wifi(EspSerial);
SimpleTimer timer;

WidgetTerminal terminal(V1);

boolean alarm = false;

void setup()
{
  // Set console baud rate
  Serial.begin(19200);
  EspSerial.begin(19200);

  Blynk.begin(token, wifi, ssid, password);

  //push msg
  Blynk.notify("Alarm active");

  pinMode(2, INPUT_PULLUP);
  
  //timer for blinking led on alarm
  timer.setInterval(1000L, blinkAlarm);
}

void loop()
{
  Blynk.run();
  if (alarm) timer.run(); else digitalWrite(13, LOW); //blink if alarm active

  if (digitalRead(2)) { //read tilt sensor
    if (!alarm) {
      alarm = true;

      Blynk.notify(alarmMsg); //push msg on alarm

      terminal.println(F("Alarm! Type in Password:"));
      terminal.flush();
    }
  }
}


BLYNK_CONNECTED() {
  Blynk.syncAll();

  terminal.println(F("Blynk v" BLYNK_VERSION ": Device started"));
  terminal.println("-------------");
  terminal.flush();
}


BLYNK_WRITE(V1) //Terminal
{
  //type in password on alarm
  if (alarm) {

    String passInput = param.asStr();
    
    if (passwordAlarm == passInput) {
      alarm = false;
      terminal.println(F("Alarm deaktivated"));
      terminal.flush();

    }
    else {
      terminal.println(F("Wrong password!"));
      terminal.flush();
    }
  }
}


//timer function for blinking led on alarm
void blinkAlarm()
{
  digitalWrite(13, !digitalRead(13));
}





