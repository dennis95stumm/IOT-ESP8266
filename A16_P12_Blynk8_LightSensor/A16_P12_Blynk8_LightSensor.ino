/*
  Blynk 8: LightSensor
  Change ssid, password, token and email
*/
char ssid[] = "";
char password[] = "";
char token[] = "";

char email[] = "";
char subject[] = "Alarm NanoESP";
String  alarmMsg = "Alarm! #NanoESP";

#define BLYNK_DEBUG
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266_SoftSer.h>
#include <BlynkSimpleShieldEsp8266_SoftSer.h>

// Set ESP8266 Serial object
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(11, 12); // RX, TX

ESP8266 wifi(EspSerial);

int alarmValueMin;
int alarmValueMax;
boolean alTwitter;
boolean alEmail;

boolean alarm = false;

WidgetTerminal terminal(V1);

void setup()
{
  // Set console baud rate
  Serial.begin(19200);
  EspSerial.begin(19200);

  Blynk.begin(token, wifi, ssid, password);
}

void loop()
{
  Blynk.run();
  compValue();
}


BLYNK_CONNECTED() {
  //Sync all values and write MSG to terminal widget
  Blynk.syncAll();

  terminal.println(F("Blynk v" BLYNK_VERSION ": Device started"));
  terminal.println("-------------");
  terminal.println("Type in Alarmmessage.");
  terminal.println("Current message:");
  terminal.println(alarmMsg);
  terminal.flush();
}


BLYNK_WRITE(V1) //Terminal: get new alarm msg
{
  alarmMsg = param.asStr();

  terminal.println("Message saved: ") ;
  terminal.println(alarmMsg) ;

  terminal.flush();
}

BLYNK_WRITE(V2) //AlarmValueMin
{
  alarmValueMin = param.asInt();
}


BLYNK_WRITE(V3) //AlarmValueMax
{
  alarmValueMax = param.asInt();
}

void compValue() { //compare values to max/min
  int currValue = analogRead(A0);

  if (alarm == false) {
    if ((currValue < alarmValueMin) || (currValue > alarmValueMax)) {
      //Alarm
      terminal.println("Alarm!!!") ;

      //Twitter if twitter alarm active
      if (alTwitter) {
        Blynk.tweet(alarmMsg + " " + currValue);
        terminal.println("Tweet send");
      }
      //E-mail if E-mail alarm active
      if (alEmail) {
        Blynk.email(email, subject, alarmMsg + " Value: " + currValue);
        terminal.println("Email send");
      }

      terminal.flush();
      alarm = true;
    }
  }
  else {
    if ((currValue > alarmValueMin) && (currValue < alarmValueMax)) {
      //deactivate alarm
      terminal.println("No alarm") ;
      terminal.flush();
      alarm = false;
    }
  }

}

BLYNK_WRITE(V4) { //Email alarm activation
  alEmail = param.asInt();
  Blynk.virtualWrite(V7, param.asInt() * 255); // LED on/off
}



BLYNK_WRITE(V5) // Twitter alarm activation
{
  alTwitter = param.asInt();
  Blynk.virtualWrite(V6, param.asInt() * 255); // LED on/off
}



