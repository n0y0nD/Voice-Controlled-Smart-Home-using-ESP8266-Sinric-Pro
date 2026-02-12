
#ifdef ENABLE_DEBUG
  #define DEBUG_ESP_PORT Serial
  #define NODEBUG_WEBSOCKETS
  #define NDEBUG
#endif

#include <Arduino.h>
#include <WiFi.h>
#include "SinricPro.h"
#include "SinricProSwitch.h"
#include <map>

/* ========= WiFi & Sinric ========= */
#define WIFI_SSID     "Arups wifi"
#define WIFI_PASS     "99999999"

#define APP_KEY       "1450d421-a2a0-485f-a6be-e52752631c13"
#define APP_SECRET    "b096cdfe-247c-4c32-8009-35678157f384-040b1c5e-8888-4a8f-b8ab-b9dc056cb014"

/* ========= Device IDs ========= */
#define device_ID_1   "xxxxxxxxxxxxxxxxxxxx"
#define device_ID_2   "69467bf6729a4887d7e6ee6d"
#define device_ID_3   "69467bdc6ebb39d664d0b93e"
#define device_ID_4   "69467b7b6ebb39d664d0b8f8"

/* ========= ESP329 GPIO Mapping ========= */
/* Relays */
#define RelayPin1  23
#define RelayPin2  22
#define RelayPin3  21
#define RelayPin4  19

/* Switches */
#define SwitchPin1 18
#define SwitchPin2 17
#define SwitchPin3 16
#define SwitchPin4 4

#define wifiLed 2        // ESP32 onboard LED
#define BAUD_RATE 9600
#define DEBOUNCE_TIME 250

/* ========= Structs ========= */
typedef struct {
  int relayPIN;
  int switchPIN;
} deviceConfig_t;

typedef struct {
  String deviceId;
  bool lastState;
  unsigned long lastChange;
} switchConfig_t;

/* ========= Maps ========= */
std::map<String, deviceConfig_t> devices = {
  {device_ID_1, {RelayPin1, SwitchPin1}},
  {device_ID_2, {RelayPin2, SwitchPin2}},
  {device_ID_3, {RelayPin3, SwitchPin3}},
  {device_ID_4, {RelayPin4, SwitchPin4}}
};

std::map<int, switchConfig_t> switches;

/* ========= Relay Setup ========= */
void setupRelays() {
  for (auto &d : devices) {
    pinMode(d.second.relayPIN, OUTPUT);
    digitalWrite(d.second.relayPIN, HIGH); // OFF
  }
}

/* ========= Switch Setup ========= */
void setupSwitches() {
  for (auto &d : devices) {
    switchConfig_t cfg;
    cfg.deviceId = d.first;
    cfg.lastState = HIGH;
    cfg.lastChange = 0;

    switches[d.second.switchPIN] = cfg;
    pinMode(d.second.switchPIN, INPUT_PULLUP);
  }
}

/* ========= Sinric Callback ========= */
bool onPowerState(String deviceId, bool &state) {
  digitalWrite(devices[deviceId].relayPIN, !state);
  return true;
}

/* ========= Manual Switch Handling ========= */
void handleSwitches() {
  unsigned long now = millis();

  for (auto &s : switches) {
    if (now - s.second.lastChange > DEBOUNCE_TIME) {
      bool current = digitalRead(s.first);

      if (current != s.second.lastState) {
        s.second.lastChange = now;

        int relay = devices[s.second.deviceId].relayPIN;
        bool newState = !digitalRead(relay);
        digitalWrite(relay, newState);

        SinricProSwitch &sw = SinricPro[s.second.deviceId];
        sw.sendPowerStateEvent(!newState);

        s.second.lastState = current;
      }
    }
  }
}

/* ========= WiFi ========= */
void setupWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) delay(300);
  digitalWrite(wifiLed, LOW);
}

/* ========= Sinric ========= */
void setupSinricPro() {
  for (auto &d : devices) {
    SinricProSwitch &sw = SinricPro[d.first];
    sw.onPowerState(onPowerState);
  }
  SinricPro.begin(APP_KEY, APP_SECRET);
  SinricPro.restoreDeviceStates(true);
}

/* ========= SETUP ========= */
void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(wifiLed, OUTPUT);
  digitalWrite(wifiLed, HIGH);

  setupRelays();
  setupSwitches();
  setupWiFi();
  setupSinricPro();
}

/* ========= LOOP ========= */
void loop() {
  SinricPro.handle();
  handleSwitches();
}

