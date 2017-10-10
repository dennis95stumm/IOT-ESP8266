/*
  Test for Wifi connection and ping-time
  Change SSID and PASSWORD.
*/

#include <NanoESP.h>
#include <SoftwareSerial.h>

//Change SSID and PASSWORD here:
#define SSID ""
#define PASSWORD ""

#define LED_WLAN 13

NanoESP nanoesp = NanoESP();

void setup() {
  Serial.begin(19200);
  nanoesp.init();

  //Station Mode, Connect to WiFi
  if (!nanoesp.configWifi(STATION, SSID, PASSWORD)) {
    Serial.println(F("Error: WLAN not Connected\n"));
  }
  else {
    Serial.println(F("WLAN Connected\n"));
    digitalWrite(LED_WLAN, HIGH);
  }

 //Print IP in Terminal
  Serial.println(nanoesp.getIp());

  //Time for Ping
  int vTime = nanoesp.ping("www.google.de");

  if (vTime > 0 ){
    Serial.println("Internet Connection OK\nPing: " + String(vTime) + "ms"); 
  }
  else {
    Serial.println(F("Error: Internet Connection"));
  }
}

void loop() {

}

