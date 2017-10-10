/*
  MQTT Present
  Change SSID and PASSWORD.
*/

#include <NanoESP.h>
#include <NanoESP_MQTT.h>
#include <SoftwareSerial.h>

#include <RGBLED.h>
#include <RGBColor.h>

#include "pitches.h"
#include "songs.h"

#define SSID ""
#define PASSWORD ""

#define LED_WLAN 13
#define DEBUG true

#define RED 3
#define GREEN 5
#define BLUE 6
#define GND 4
#define BUTTON 7

#define PIEZO 8

#define IR A1
#define PHOTO A0

NanoESP nanoesp = NanoESP();
NanoESP_MQTT mqtt = NanoESP_MQTT(nanoesp);

RGBLED rgbLED = RGBLED(RED, GREEN, BLUE, 0, 3, 0);

String ip, mqttId;

RGBColor newColor = RGBColor(0, 0, 0);
RGBColor offColor = RGBColor(0, 0, 0);
int curSong;
bool isOpen = true;

mqtt_msg opened = {"", "Opened", 0, true};

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  pinMode(GND, OUTPUT);
  digitalWrite(GND, LOW);

  pinMode(IR, OUTPUT);

  Serial.begin(19200);

  nanoesp.init();

  //Station Mode
  nanoesp.configWifiMode(STATION);

//  nanoesp.configWifiStation(SSID, PASSWORD);

  if (nanoesp.wifiConnected()) {
    Serial.println(F("Wifi Connected"));
    digitalWrite(LED_WLAN, HIGH);
  }
  else {
    Serial.println(F("Wifi not Connected"));
  }


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

    if (mqtt.subscribe(0, "NanoESP/" + mqttId + "/present", 2, newPresent)) Serial.println(F("Subscribed to present")); else Serial.println(F("Error Subscribe to present"));
  }
  else {
    Serial.println(F("error connecting"));
  }
  setSongs();
}

void loop() {
  int id, len;

  if (nanoesp.recvData(id, len)) {
    mqtt.recvMQTT(id, len); //auto hanlder mit Funktionen
  }

  mqtt.stayConnected(0);

//Present opened?
  if  (!isOpen) {
    if (checkIsOpen()) {
      isOpen = true;
      Serial.println("Open");
      mqtt.publish(0, &opened);
      rgbLED.crossfade(newColor);
      play(curSong);
    }
  }
  else { //Present closed?
    if (!checkIsOpen()) {
      isOpen = false;
      Serial.println("Closed");
      rgbLED.crossfade(offColor);
    }
  }
}


bool checkIsOpen()
{
  int high; int low;

  digitalWrite(IR, HIGH);
  delay(1);
  high = analogRead(PHOTO);
  digitalWrite(IR, LOW);
  delay(1);
  low = analogRead(PHOTO);

  digitalWrite(IR, HIGH);
  delay(1);
  high += analogRead(PHOTO);
  digitalWrite(IR, LOW);
  delay(1);
  low += analogRead(PHOTO);

  if (high > (2 * low)) {
    return false;
  }
  else {
    return true;
  }
}

String oldTopic;

void newPresent(String value) {
  Serial.println("New Present for " + value);
  if (opened.topic != "") {
    mqtt.unsubscribe(0, opened.topic + "/color");
    Serial.println(F("Unsubscribed old color"));

    mqtt.unsubscribe(0, opened.topic + "/song");
    Serial.println(F("Unsubscribed old song"));
  }

  opened.topic = "NanoESP/" + mqttId + "/present/" + value;
  mqtt.subscribe(0, opened.topic + "/color", 2, gotnewColor); Serial.println(F("Subscribed new Color"));

  // Recieve retained msg before subscribing next
  int id, len;
  for (int i = 0; i <= 250; i++) {
    if (nanoesp.recvData(id, len)) {
      if (mqtt.recvMQTT(id, len)) {
        break; //auto hanlder mit Funktionen
      }
    }
    delay(10);
  }
  mqtt.subscribe(0, opened.topic + "/song", 2, gotnewSong); Serial.println(F("Subscribed new Song"));
}


void gotnewColor(String value) {
  Serial.println("New color: " + value);

  value = value.substring(value.indexOf('(') + 1); //255,23,226)
  int red = value.substring(0, value.indexOf(',')).toInt();

  value = value.substring(value.indexOf(',' ) + 1); //23,226)
  int green = value.substring(0, value.indexOf(',')).toInt();

  value = value.substring(value.indexOf(',') + 1); //226)
  int blue = value.substring(0, value.indexOf(')')).toInt();

  newColor   = RGBColor(red, green, blue);

  //for direct change
  //analogWrite(RED, red); analogWrite(GREEN, green); analogWrite(BLUE, blue);
}

void gotnewSong(String value) {
  Serial.println("New Song: " + value);
  curSong = value.toInt();
}

void setSongs() {
  //Configuration for songs, you may change some songs
  int numTunes = 5;

  tunes[0] = {weWish, weWishDurations, sizeof(weWish) / sizeof(int), 80, N_C6, N_C5};
  tunes[1] = {alleJahre, alleJahreDurations, sizeof(alleJahre) / sizeof(int), 80, N_C6, N_C5};
  tunes[2] = {jingleBells, jingleBellsDurations, sizeof(jingleBells) / sizeof(int), 60, 784, 523};
  tunes[3] = {firstNoel, firstNoelDurations, sizeof(firstNoel) / sizeof(int), 60, 523, 262};
  //tunes[3] = {oHolyNight, oHolyNightDurations, sizeof(oHolyNight) / sizeof(int), 100, 659, 262};
  tunes[4] = {whatChild, whatChildDurations, sizeof(whatChild) / sizeof(int), 100, 587, 247};
  tunes[5] = {weThreeKings, weThreeKingsDurations, sizeof(weThreeKings) / sizeof(int), 100, 587, 294};
  
}

void play(int tuneNum) {

  int randomOffset = random(32);

  int numNotes = tunes[tuneNum].numCount;
  int tempo = tunes[tuneNum].tempo;
  for (int thisNote = 0; thisNote < numNotes; thisNote++) {

    int freq = pgm_read_word_near(tunes[tuneNum].melody + thisNote) * 2;
    int noteDuration =   tempo *  pgm_read_byte_near(tunes[tuneNum].durations + thisNote);

    if (freq > 0) {
      int n = (map(freq, tunes[tuneNum].low, tunes[tuneNum].high, 1, 31) + randomOffset) % 31 + 1;
      tone(PIEZO, freq, noteDuration);

    } else {
      // REST
      delay(noteDuration);
    }

    delay(noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 0.30;
    delay(pauseBetweenNotes);

    noTone(PIEZO);
  }
}



