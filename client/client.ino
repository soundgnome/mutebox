#include <M5StickC.h>
#include <Ticker.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "config.h"

const int DISPLAY_TIMEOUT_SECONDS = 5;

int cursor_y;
Ticker display_timer;

void setup() {
  M5.begin();
  M5.Lcd.setRotation(1);
  M5.Lcd.printf("connecting to %s\n", WIFI_NAME);
  M5.Lcd.print(WiFi.macAddress());
  WiFi.begin(WIFI_NAME, WIFI_PASS);
  M5.Lcd.print("\n");
  cursor_y = M5.Lcd.getCursorY();
  display_timeout_start();
}

void loop() {
  M5.update();
  if (M5.BtnA.wasPressed()) {
    send_signal_wifi();
  } else if (M5.BtnB.wasPressed()) {
    show_network_status();
  }
}

void display_timeout_handle() {
  M5.Axp.SetLDO3(false);
  M5.Axp.SetLDO2(false);
}

void display_timeout_start() {
  M5.Axp.SetLDO3(true);
  M5.Axp.SetLDO2(true);
  display_timer.once(DISPLAY_TIMEOUT_SECONDS, display_timeout_handle);
}

void show_network_status() {
  M5.Lcd.setCursor(0, cursor_y);
  if (WiFi.isConnected()) {
    M5.Lcd.print("IP ");
    M5.Lcd.print(WiFi.localIP());
    M5.Lcd.printf(" batt %d    ", (int)(M5.Axp.GetBatPower()));
  } else {
    M5.Lcd.print("not connected, status ");
    M5.Lcd.print(WiFi.status());
    WiFi.begin(WIFI_NAME, WIFI_PASS);
  }
  display_timeout_start();
}

void send_signal_wifi() {
  HTTPClient http;
  http.begin(WIFI_ENDPOINT);
  http.GET();
  http.end();
}
