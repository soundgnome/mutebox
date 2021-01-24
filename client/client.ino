#include <M5StickC.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "config.h"

void setup() {
  M5.begin();
  M5.Lcd.setRotation(1);
  M5.Lcd.printf("connecting to %s\n", WIFI_NAME);
  M5.Lcd.print(WiFi.macAddress());
  WiFi.begin(WIFI_NAME, WIFI_PASS);
}

void loop() {
  M5.update();
  if (M5.BtnA.wasPressed()) {
    send_signal_wifi();
  } else if (M5.BtnB.wasPressed()) {
    show_network_status();
  }
}

void show_network_status() {
  if (WiFi.isConnected()) {
    M5.Lcd.print("\nconnected at ");
    M5.Lcd.print(WiFi.localIP());
  } else {
    M5.Lcd.print("\nnot connected, status ");
    M5.Lcd.print(WiFi.status());
    WiFi.begin(WIFI_NAME, WIFI_PASS);
  }
}

void send_signal_wifi() {
  HTTPClient http;
  http.begin(WIFI_ENDPOINT);
  http.GET();
  http.end();
}
