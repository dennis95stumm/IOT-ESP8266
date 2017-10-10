/*
  MQTT Basic functions
  Change SSID and PASSWORD.
*/

#include <NanoESP.h>
#include <NanoESP_MQTT.h>  //special library for MQTT
#include <SoftwareSerial.h>

#define SSID ""
#define PASSWORD ""

#define LED_WLAN 13
#define DEBUG true

NanoESP nanoesp = NanoESP();
NanoESP_MQTT mqtt = NanoESP_MQTT(nanoesp);

String ip, mqttId;

void setup() {
  Serial.begin(19200);
  nanoesp.init();

  //! Only if you use a new Network
  // nanoesp.configWifi(STATION, SSID, PASSWORD);

  //Station Mode
  nanoesp.configWifiMode(STATION);
  //delay(1000);

  // Wait till Connected to WiFi
  if (nanoesp.wifiConnected())digitalWrite(LED_WLAN, HIGH); else Serial.println(F("Error WLAN Connect"));

  //Print IP in Terminal
  nanoesp.getIpMac(ip,  mqttId);
  Serial.println("My IP: " + ip);

  //Print MQTTid in Terminal
  mqttId.replace(":", "");
  Serial.println("My MQTT ID: " + mqttId+"\n");
 
 //if (mqtt.connect(0, "broker.hivemq.com", 1883, mqttId)) {  //connect to alternative broker
 if (mqtt.connect(0, "broker.fkainka.de", 1883, mqttId)) {  //connect to broker
    Serial.println(F("Connected to Broker\n"));

    Serial.println(F("My personal Topic is:"));
    Serial.println("NanoESP/" + mqttId + "/\n");
    
    if (mqtt.subscribe(0, "NanoESP/" + mqttId + "/test")) Serial.println("Subscribed to:\nNanoESP/" + mqttId + "/test\n"); 
    if (mqtt.publish(0, "NanoESP/" + mqttId + "/test", "Hello from my NanoESP")) Serial.println("Published to:\nNanoESP/" + mqttId + "/test\n");
  }
  else {
    Serial.println(F("error connecting"));
  }
}


void loop() {
  int id, len;

  if (nanoesp.recvData(id, len)) {        //recv data
    String topic, value;
    if (mqtt.recvMQTT(id, len, topic, value)) {      //handle recvd data as mqtt data, parameters topic and value as reference
      Serial.println("New Message:\nTopic=" + topic + " Value=" + value+"\n");         //print message
    }
   }
  
  mqtt.stayConnected(0);        //keep the connection to broker alive 
}
