#ifndef _DISPLAY_TIME_
#define _DISPLAY_TIME_

#include <ESP32Time.h>

enum Selected_digit {
  Seconds,
  Minutes,
  Hours,
  NUM_DIGITS
};
// get constant reference on time structure and display current time in format HH:MM:SS
void display_time(TFT_eSPI & tft, ESP32Time & esp_time);

void display_timeSetup(TFT_eSPI & tft, const tm & timeinfo, const Selected_digit & currentDigit);

#endif // _DISPLAY_TIME_