/*
  Blnky10: NTC-Sensor
  Change ssid, password, token and email
*/

char ssid[] = "";
char password[] = "";
char token[] = "";

char email[] = "";
char subject[] = "Temperatur Summary";

#define BLYNK_DEBUG
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266_SoftSer.h>
#include <BlynkSimpleShieldEsp8266_SoftSer.h>
#include <SimpleTimer.h>

#include <TimeLib.h>

// Set ESP8266 Serial object
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(11, 12); // RX, TX

ESP8266 wifi(EspSerial);
SimpleTimer timer;

//init max min value (0 makes no sense)
double tempMax = - 273;
double tempMin = +200;
bool autoSend;

void setup()
{
  // Set console baud rate
  Serial.begin(19200);
  EspSerial.begin(19200);

  Blynk.begin(token, wifi, ssid, password);
  //timer for temp measure
  timer.setInterval(500L, getTemp);
}

void loop()
{
  Blynk.run();
  timer.run(); //Call timer (other than normal timers)
}


BLYNK_CONNECTED() {
  Blynk.syncVirtual(V5); //sync email auto send state
}

void getTemp() { //get temp, convert to C and send
  double currValue = Thermistor(analogRead(A0)) ; //Convert to C !!! Pot: round((x*10)/10)

  if (currValue < tempMin) {
    tempMin = currValue;
  }
  if (currValue > tempMax) {
    tempMax = currValue;
  }

  Blynk.virtualWrite(V0, currValue);
  Blynk.virtualWrite(V1, currValue);
  Blynk.virtualWrite(V3, tempMin);
  Blynk.virtualWrite(V2, tempMax);
}

double Thermistor(int RawADC) {
  //Source: http://playground.arduino.cc/ComponentLib/Thermistor2
  double Temp;
  Temp = log(10000.0 * ((1024.0 / RawADC - 1)));
  //         =log(10000.0/(1024.0/RawADC-1)) // for pull-up configuration
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp )) * Temp );
  Temp = Temp - 273.15;            // Convert Kelvin to Celcius
  // Temp = (Temp * 9.0)/ 4.7 + 32.0; // Convert Celcius to Fahrenheit
  return Temp;
}


void sendSummary() { //send email summary
  String msg = "Tempertur Summary:\nCurrent Temperatur: " + String(Thermistor(analogRead(A0))) + " C\n\nMax. Temp: " + String(tempMax) + "C \n\nMin. Temp: " + String(tempMin) + "C \n";
  Blynk.email(email, subject, msg);
}

BLYNK_WRITE(V6) { //Timer Send
  if (autoSend) {
    sendSummary();
  }
}

BLYNK_WRITE(V4) { //Button Send
  sendSummary();
}

BLYNK_WRITE(V5) { //config email send
  autoSend = param.asInt();
}




