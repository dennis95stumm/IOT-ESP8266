/*
  TCP-Server example
  Change SSID and PASSWORD.
*/

#include <NanoESP.h>
#include <NanoESP_HTTP.h> //special library for http-connection
#include <SoftwareSerial.h>
#include "Websites.h" //websites in a special file as progmem

#define SSID ""
#define PASSWORD ""

#define LED_WLAN 13

NanoESP nanoesp = NanoESP();
NanoESP_HTTP http = NanoESP_HTTP(nanoesp); //init http library with an instance of nanoesp

void setup() {
  Serial.begin(19200);
  nanoesp.init();

  //! Only if you want to change the ACCESPOINT configuration
  //nanoesp.configWifi(ACCESSPOINT, "NanoESP", "");
  
  //! Only if you use a new Network
  // nanoesp.configWifi(DUAL, SSID, PASSWORD);
    
  //Dual Mode
  nanoesp.configWifiMode(DUAL);
  //delay(1000);
  
  // Wait till Connected to WiFi
  if (nanoesp.wifiConnected())digitalWrite(LED_WLAN, HIGH); else Serial.println(F("Error WLAN Connect"));

  //Start TCP Server
  if (nanoesp.startTcpServer(80))    Serial.println(F("TCP Server Activ")); else   Serial.println(F("TCP Server Error"));

  //Print IP to Terminal
  Serial.println(nanoesp.getIp());
}

void loop() {
  String method, ressource, parameter;
  int id;

  if (http.recvRequest(id, method, ressource, parameter)) { //Incoming request, parameters by reference

    Serial.println("New Request from id :" + String(id) + ", method: " + method +  ", ressource: " + ressource +  " parameter: " + parameter);

    if (ressource == "/") { //index page
      http.sendFromFlash(id, index, sizeof(index)); //send website from website.h
      nanoesp.closeConnection(id); //close connection so browser knows website transmission is complete
    }
    else if (ressource == "/lib") {
      http.sendFromFlash(id, lib, sizeof(lib)); //send website from website.h
      nanoesp.closeConnection(id); //close connection so browser knows website transmission is complete
    }
    else if (ressource == "/pinout") {
      http.sendFromFlash(id, pinout, sizeof(pinout));  //send website from website.h
      nanoesp.closeConnection(id); //close connection so browser knows website transmission is complete
    }
    else {
      http.sendFromFlash(id, error404, sizeof(error404)); //send website from website.h
      nanoesp.closeConnection(id);//close connection so browser knows website transmission is complete
    }

  }
}

