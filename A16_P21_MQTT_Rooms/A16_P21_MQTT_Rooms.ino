/*
  MQTT Roons
  Change SSID and PASSWORD.
*/

#include <NanoESP.h>
#include <NanoESP_MQTT.h>
#include <SoftwareSerial.h>

#define SSID ""
#define PASSWORD ""

NanoESP nanoesp = NanoESP();
NanoESP_MQTT mqtt = NanoESP_MQTT(nanoesp);

String ip, mqttId;

#define SWITCH_ROOM_1 5
#define SWITCH_ROOM_2 7
#define ALARMSENSOR_ROOM_1 A3
#define ALARMSENSOR_ROOM_2 A2

#define LIGHT_ROOM_1 9
#define LIGHT_ROOM_2 13
#define PIEZO 8

unsigned long previousMillisAlarm = 0;
unsigned long intervalAlarm = 1000;
int durationAlarm;
bool alarmActive = false;
bool alarmToggle;

bool alarm_status_v;
bool room1_light_stauts_v;
bool room2_light_stauts_v;

void setup() {
  pinMode(SWITCH_ROOM_1, INPUT_PULLUP);
  pinMode(SWITCH_ROOM_2, INPUT_PULLUP);
  pinMode(ALARMSENSOR_ROOM_1, INPUT);
  pinMode(ALARMSENSOR_ROOM_2, INPUT);

  pinMode(LIGHT_ROOM_1, OUTPUT);
  pinMode(LIGHT_ROOM_2, OUTPUT);

  pinMode(A1,OUTPUT);pinMode(A1,OUTPUT);digitalWrite(A1,HIGH);digitalWrite(A1,HIGH);

  Serial.begin(19200);
  nanoesp.init();

 //! Only if you want to change the ACCESPOINT configuration
  //nanoesp.configWifi(ACCESSPOINT, "NanoESP", "");

  //! Only if you use a new Network
  // nanoesp.configWifi(DUAL, SSID, PASSWORD);

  //Station Mode
  nanoesp.configWifiMode(STATION);
  //delay(1000);

  // Wait till Connected to WiFi
  if (nanoesp.wifiConnected())Serial.println(F("WLAN Connected")); else Serial.println(F("Error WLAN Connect"));

  //Print IP in Terminal
  nanoesp.getIpMac( ip,  mqttId);
  Serial.println("My IP: " + ip);

  //Print MQTTid in Terminal
  mqttId.replace(":", "");
  Serial.println("My MQTT ID: " + mqttId+"\n");

  if (mqtt.connect(0, "broker.fkainka.de", 1883, mqttId)) {
    Serial.println(F("Connected to Broker"));

    Serial.println(F("My personal Topic is:"));
    Serial.println("NanoESP/" + mqttId + "/\n");

    //subcribe: Connection ID, Topic, Max Qualitiy of Service, Function to call when msg recieved
    if (mqtt.subscribe(0, "NanoESP/" + mqttId + "/room1/light", 2, room1_light_status)) Serial.println(F("Subscribed to /room1/light"));
    if (mqtt.subscribe(0, "NanoESP/" + mqttId + "/room1/light", 2,  room1_light)) Serial.println(F("Subscribed to /room1/light"));
    if (mqtt.subscribe(0, "NanoESP/" + mqttId + "/room2/light", 2,  room2_light_status)) Serial.println(F("Subscribed to /room2/light"));
    if (mqtt.subscribe(0, "NanoESP/" + mqttId + "/room2/light", 2,  room2_light)) Serial.println(F("Subscribed to /room2/light"));
    if (mqtt.subscribe(0, "NanoESP/" + mqttId + "/+/alarm", 2,  alarm_status)) Serial.println(F("Subscribed to alarm"));
  }
  else {
    Serial.println(F("error connecting"));
  }
}


void loop() {
  int id, len;

  if (nanoesp.recvData(id, len)) {
    mqtt.recvMQTT(id, len); //auto handle recieved data by defined functions
  }

  checkConditions();    
  mqtt.stayConnected(0);
  if (alarm_status_v) alarm();
}

void checkConditions() {
  room1_alarmsensor_check();
  room2_alarmsensor_check();
  room1_button_check();
  room2_button_check();
}


//----------------------------Room1---------------------------------------------
//____________________________Switch__________________________________________

//Switch knows about the light status so it can toggle the light
void room1_light_status (String value) {
  Serial.println("Light status Room 1 :" + value);
  if (value == "1") {
    room1_light_stauts_v = true;
  }
  else if (value == "0") {
    room1_light_stauts_v = false;
  }

}

void room1_button_check () {
  if (!digitalRead(SWITCH_ROOM_1)) {
    if (mqtt.publish(0, "NanoESP/" + mqttId + "/room1/light", String(!room1_light_stauts_v))) Serial.println(F("Button 1 pressed\n"));
    while (!digitalRead(SWITCH_ROOM_1)) {};
  }
}

//____________________________Light___________________________________________
void room1_light (String value) {
  if (value == "1") {
    Serial.println(F("Light on"));
    digitalWrite(LIGHT_ROOM_1, HIGH);
  }
  else if (value == "0") {
    Serial.println(F("Light off"));
    digitalWrite(LIGHT_ROOM_1, LOW);
  }
}

//____________________________Alarmsensor___________________________________________
void room1_alarmsensor_check () {
  if (!digitalRead(ALARMSENSOR_ROOM_1)) {
    if (mqtt.publish(0, "NanoESP/" + mqttId + "/room1/alarm", "1")) Serial.println(F("Alarm Room 1\n"));
    while (!digitalRead(ALARMSENSOR_ROOM_1)) {};
  }
}

//----------------------------Room2---------------------------------------------


//____________________________Switch__________________________________________

//Switch knows about the light status so it can toggle the light
void room2_light_status (String value) {
  Serial.println("Light status Room 2 :" + value);
  if (value == "1") {
    room2_light_stauts_v = true;
  }
  else if (value == "0") {
    room2_light_stauts_v = false;
  }
}

void room2_button_check () {
  if (!digitalRead(SWITCH_ROOM_2)) {
    if (mqtt.publish(0, "NanoESP/" + mqttId + "/room2/light", String(!room2_light_stauts_v))) Serial.println(F("Button 2 pressed\n"));
    while (!digitalRead(SWITCH_ROOM_2)) {};
  }
}


//____________________________Light___________________________________________

void room2_light (String value) {
  if (value == "1") {
    Serial.println(F("Light on"));
    digitalWrite(LIGHT_ROOM_2, HIGH);
  }
  else if (value == "0") {
    Serial.println(F("Light off"));
    digitalWrite(LIGHT_ROOM_2, LOW);
  }

}

//____________________________Alarmsensor___________________________________________

void room2_alarmsensor_check () {
  if (!digitalRead(ALARMSENSOR_ROOM_2)) {
    if (mqtt.publish(0, "NanoESP/" + mqttId + "/room2/alarm", "1")) Serial.println(F("Alarm Room 2\n"));
    while (!digitalRead(ALARMSENSOR_ROOM_2)) {};
  }
}


//----------------------------ALARM---------------------------------------------
void alarm_status (String value) {
  if (value == "1") {
    Serial.println(F("ALARM"));
    durationAlarm = 20;
    alarm_status_v = true;
  }
  if (value == "0") {
    Serial.println(F("ALARM DEACTIVATED"));
    durationAlarm = 20;
    alarm_status_v = false;
  }
}


void alarm() {
  if (millis() - previousMillisAlarm >= intervalAlarm) {
    alarmToggle != alarmToggle;
    if (alarmToggle) tone(PIEZO, 400, 500); else tone(PIEZO, 800, 500);
    previousMillisAlarm = millis(); //Reset time till AlarmToggle;
    durationAlarm--;
    if (durationAlarm <= 0) alarmActive = false;
  }
}










