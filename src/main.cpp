/*[code]
TFT_eSPI ver = 2.5.43
Processor    = ESP32
Frequency    = 240MHz
Transactions = Yes
Interface    = SPI
Display driver = 9341
Display width  = 240
Display height = 320

MOSI    =   GPIO 13
MISO    =   GPIO 12
SCK     =   GPIO 14
TFT_CS   =  GPIO 15
TFT_DC   =  GPIO 0
TFT_RST  =  GPIO 2

Font GLCD   loaded
Font 2      loaded
Font 4      loaded
Font 6      loaded
Font 7      loaded
Font 8      loaded
Smooth font enabled

Display SPI frequency = 27.00
[/code]*/
////////////////////////////////////////////////////////////////////
#include <Arduino.h>
// Walking 1 write and read pixel test

#include <TFT_eSPI.h>
#include <SPI.h>
#include <../.pio/libdeps/esp32-s2-kaluga-1/TFT_eSPI/User_Setups/Setup420.h>
#include <ESP32Time.h>
#include <time.h>
#include <../lib/display_time.h>


TFT_eSPI tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT);       // Invoke custom library
ESP32Time rtc(0);

struct tm timeinfo;

void setup()   {
  //Set up the display
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setCursor(0, 0);
  rtc.setTimeStruct(timeinfo);
  rtc.setTime(12, 12, 12, 0, 0, 0);
}

void loop() {
  int sec, min, hour;
  display_time(tft, rtc);
  sec = rtc.getSecond();
  min = rtc.getMinute();
  hour = rtc.getHour();

  // Adjust the time values by adding 1 second
    sec++;              // Advance second
    if (sec == 60) {    // Check for roll-over
      sec = 0;          // Reset seconds to zero
      min++;            // Advance minute
      if (min > 59) {   // Check for roll-over
        min = 0;
        hour++;          // Advance hour
        if (hour > 23) { // Check for 24hr roll-over (could roll-over on 13)
          hour = 0;      // 0 for 24 hour clock, set to 1 for 12 hour clock
        }
      }
    }

  rtc.setTime(sec, min, hour, 0, 0, 0);

  delay(1000);
}
