
/*
  MQTT Cheerlights
  Change SSID and PASSWORD.
*/

#include <NanoESP.h>
#include <NanoESP_MQTT.h>
#include <SoftwareSerial.h>
#include <RGBLED.h>
#include <RGBColor.h>

//#define SSID "YourSSID"
//#define PASSWORD "YourPassword"

#define LED_WLAN 13

#define RED 3
#define GREEN 5
#define BLUE 6
#define GND 4

#define BUTTON 7

NanoESP nanoesp = NanoESP();
NanoESP_MQTT mqtt = NanoESP_MQTT(nanoesp);

RGBLED rgbLED = RGBLED(RED, GREEN, BLUE, 0, 3, 0);

RGBColor red   = RGBColor(100, 0, 0);
RGBColor green = RGBColor(0, 100, 0);
RGBColor blue  = RGBColor(0, 0, 100);

RGBColor cyan   = RGBColor(0, 100, 100);
RGBColor white = RGBColor(100, 100, 100);
RGBColor warmwhite  = RGBColor(100, 87, 87);
RGBColor purple = RGBColor(50, 0, 50);
RGBColor magenta = RGBColor(100, 0, 100);

RGBColor yellow = RGBColor(100, 100 , 0);
RGBColor orange = RGBColor(100, 65 , 0);

RGBColor pink = RGBColor(100, 75 , 100);

String ip, mqttId;

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  pinMode(GND, OUTPUT);
  digitalWrite(GND, LOW);

  pinMode(BUTTON, INPUT_PULLUP);

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
  nanoesp.getIpMac( ip,  mqttId);
  Serial.println("My IP: " + ip);

  //Print MQTTid in Terminal
  mqttId.replace(":", "");
  Serial.println("My MQTT ID: " + mqttId+"\n");

  //  if (mqtt.connect(0, "broker.hivemq.com", 1883, mqttId)) { //alternative broker
  if (mqtt.connect(0, "broker.fkainka.de", 1883, mqttId)) {  //connect to broker
 
    Serial.println(F("Connected to Broker"));

    Serial.println(F("My personal Topic is:"));
    Serial.println("NanoESP/" + mqttId + "/\n");

    if (mqtt.subscribe(0, "NanoESP/" + mqttId + "/rgb/mode", 2, changeMode)) Serial.println("Subscribed to:\nNanoESP/" + mqttId + "/rgb/mode"); else Serial.println(F("Error Subscribe to rgb Mode"));
  }
  else {
    Serial.println(F("error connecting"));
  }
}

bool cheerlightsMode;

void loop() {
  int id, len;

  if (nanoesp.recvData(id, len)) {
    mqtt.recvMQTT(id, len); //auto handle recieved data by defined functions
  }
  mqtt.stayConnected(0);

  if (!digitalRead(BUTTON)) { //change cheerlights mode

    mqtt_msg msgMode = {"NanoESP/" + mqttId + "/rgb/mode", String(!cheerlightsMode), 0, true};  //type: mqtt_msg (topic, msg, qos, retain)
    if (mqtt.publish(0, &msgMode)) Serial.println(F("Changed mode\n"));
    msgMode.value = "1";
    while (!digitalRead(BUTTON)) {};
  }

}

void changeMode(String value) {

  if (value == "1") {
    Serial.println("Cheerlights mode\n");
    if (mqtt.unsubscribe(0, "NanoESP/" + mqttId + "/rgb/color")) Serial.println("Unsubscribed from: NanoESP/" + mqttId + "/rgb/color");
    if (mqtt.subscribe(0, "Info/Cheerlights", 2, changeCheerlights)) Serial.println(F("Subscribed to Cheerlights"));
    cheerlightsMode = true;
  }
  else {
    Serial.println("Personal light mode\n");
    if (mqtt.unsubscribe(0, "Info/Cheerlights"))  Serial.println(F("Unsubscribed from Cheerlights")); else Serial.println(F("Error"));
    if (mqtt.subscribe(0, "NanoESP/" + mqttId + "/rgb/color", 2, changeColor)) Serial.println("Subscribed to: NanoESP/" + mqttId + "/rgb/color");
    cheerlightsMode = false;
  }

}

void changeCheerlights(String color) {
  Serial.println("New Cheerlights color : " + color);

  if (color == "red") rgbLED.crossfade(red);
  else if (color == "green") rgbLED.crossfade(green);
  else if (color == "blue") rgbLED.crossfade(blue);
  else if (color == "cyan") rgbLED.crossfade(cyan);
  else if (color == "white") rgbLED.crossfade(white);
  else if (color == "warmwhite") rgbLED.crossfade(warmwhite);
  else if (color == "purple") rgbLED.crossfade(purple);
  else if (color == "magenta") rgbLED.crossfade(magenta);
  else if (color == "yellow") rgbLED.crossfade(yellow);
  else if (color == "orange") rgbLED.crossfade(orange);
}

void changeColor(String value) {
  Serial.println("New color: " + value);
  //rgb(255,23,226)
  value = value.substring(value.indexOf('(') + 1); //255,23,226)
  int red = value.substring(0, value.indexOf(',')).toInt();

  value = value.substring(value.indexOf(',' ) + 1); //23,226)
  int green = value.substring(0, value.indexOf(',')).toInt();

  value = value.substring(value.indexOf(',') + 1); //226)
  int blue = value.substring(0, value.indexOf(')')).toInt();

  RGBColor vColor   = RGBColor(red, green, blue);
  rgbLED.crossfade(vColor);
  //for direct change
  //analogWrite(RED, red); analogWrite(GREEN, green); analogWrite(BLUE, blue);
}





