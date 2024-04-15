#include <Arduino.h>
#include <string>
#include <TFT_eSPI.h>
#include <SPI.h>
#include <../.pio/libdeps/esp32-s2-kaluga-1/TFT_eSPI/User_Setups/Setup420.h>
#include <../lib/display_time.h>
#include <ESP32Time.h>

void display_time(TFT_eSPI & tft, ESP32Time & esp_time){
    tft.setTextSize(4);
    tft.setTextColor(TFT_WHITE);
    tft.setCursor(40, 5);
    // char str[50];
    // std:sprintf(str, "%d : %d : %d", t.);
    tft.println(esp_time.getTime());
}