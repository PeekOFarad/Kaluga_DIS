#ifndef _DISPLAY_TIME_
#define _DISPLAY_TIME_

#include <ESP32Time.h>

// get constant reference on time structure and display current time in format HH:MM:SS
void display_time(TFT_eSPI & tft, ESP32Time & esp_time);

#endif // _DISPLAY_TIME_