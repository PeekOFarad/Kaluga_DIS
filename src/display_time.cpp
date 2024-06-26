#include <Arduino.h>
#include <string>
#include <TFT_eSPI.h>
#include <SPI.h>
#include <../.pio/libdeps/esp32-s2-kaluga-1/TFT_eSPI/User_Setups/Setup420.h>
#include <../lib/display_time.h>
#include <ESP32Time.h>

byte omm = 99, oss = 99;
byte xcolon = 0, xsecs = 0;

void display_time(TFT_eSPI & tft, ESP32Time & esp_time){
    
    // Update digital time
    int xpos = 0;
    int ypos = 85; // Top left corner ot clock text, about half way down
    int ysecs = ypos + 24;

    int hh = esp_time.getHour();
    int mm = esp_time.getMinute();
    int ss = esp_time.getSecond();

    if (omm != mm) { // Redraw hours and minutes time every minute
      omm = mm;
      // Draw hours and minutes
      if (hh < 10) xpos += tft.drawChar('0', xpos, ypos, 8); // Add hours leading zero for 24 hr clock
      xpos += tft.drawNumber(hh, xpos, ypos, 8);             // Draw hours
      xcolon = xpos; // Save colon coord for later to flash on/off later
      xpos += tft.drawChar(':', xpos, ypos - 8, 8);
      if (mm < 10) xpos += tft.drawChar('0', xpos, ypos, 8); // Add minutes leading zero
      xpos += tft.drawNumber(mm, xpos, ypos, 8);             // Draw minutes
      xsecs = xpos; // Sae seconds 'x' position for later display updates
    }
    if (oss != ss) { // Redraw seconds time every second
      oss = ss;
      xpos = xsecs;

      if (ss % 2) { // Flash the colons on/off
        tft.setTextColor(0x39C4, TFT_BLACK);        // Set colour to grey to dim colon
        tft.drawChar(':', xcolon, ypos - 8, 8);     // Hour:minute colon
        xpos += tft.drawChar(':', xsecs, ysecs, 6); // Seconds colon
        tft.setTextColor(TFT_YELLOW, TFT_BLACK);    // Set colour back to yellow
      }
      else {
        tft.drawChar(':', xcolon, ypos - 8, 8);     // Hour:minute colon
        xpos += tft.drawChar(':', xsecs, ysecs, 6); // Seconds colon
      }

      //Draw seconds
      if (ss < 10) xpos += tft.drawChar('0', xpos, ysecs, 6); // Add leading zero
      tft.drawNumber(ss, xpos, ysecs, 6);                     // Draw seconds
    }
}

void display_time(TFT_eSPI & tft, tm * esp_time){

    // Update digital time
    int xpos = 0;
    int ypos = 85; // Top left corner ot clock text, about half way down
    int ysecs = ypos + 24;
    
    int hh = esp_time->tm_hour;
    int mm = esp_time->tm_min;
    int ss = esp_time->tm_sec;

    if (omm != mm) { // Redraw hours and minutes time every minute
      omm = mm;
      // Draw hours and minutes
      if (hh < 10) xpos += tft.drawChar('0', xpos, ypos, 8); // Add hours leading zero for 24 hr clock
      xpos += tft.drawNumber(hh, xpos, ypos, 8);             // Draw hours
      xcolon = xpos; // Save colon coord for later to flash on/off later
      xpos += tft.drawChar(':', xpos, ypos - 8, 8);
      if (mm < 10) xpos += tft.drawChar('0', xpos, ypos, 8); // Add minutes leading zero
      xpos += tft.drawNumber(mm, xpos, ypos, 8);             // Draw minutes
      xsecs = xpos; // Sae seconds 'x' position for later display updates
    }
    if (oss != ss) { // Redraw seconds time every second
      oss = ss;
      xpos = xsecs;

      if (ss % 2) { // Flash the colons on/off
        tft.setTextColor(0x39C4, TFT_BLACK);        // Set colour to grey to dim colon
        tft.drawChar(':', xcolon, ypos - 8, 8);     // Hour:minute colon
        xpos += tft.drawChar(':', xsecs, ysecs, 6); // Seconds colon
        tft.setTextColor(TFT_YELLOW, TFT_BLACK);    // Set colour back to yellow
      }
      else {
        tft.drawChar(':', xcolon, ypos - 8, 8);     // Hour:minute colon
        xpos += tft.drawChar(':', xsecs, ysecs, 6); // Seconds colon
      }

      //Draw seconds
      if (ss < 10) xpos += tft.drawChar('0', xpos, ysecs, 6); // Add leading zero
      tft.drawNumber(ss, xpos, ysecs, 6);                     // Draw seconds
    }
}

void display_timeSetup(TFT_eSPI & tft, const tm & timeinfo, const Selected_digit & currentDigit){
    
    // Update digital time
    int xpos = 0;
    int ypos = 85; // Top left corner ot clock text, about half way down
    int ysecs = ypos + 24;
  
    int hh = timeinfo.tm_hour;
    int mm = timeinfo.tm_min;
    int ss = timeinfo.tm_sec;
    
    // Draw time
    // Draw hours
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    if (currentDigit == Hours) {
      tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    }

    if (hh < 10) xpos += tft.drawChar('0', xpos, ypos, 8); // Add hours leading zero for 24 hr clock
    xpos += tft.drawNumber(hh, xpos, ypos, 8);     

    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    xcolon = xpos; // Save colon coord for later to flash on/off later
    xpos += tft.drawChar(':', xpos, ypos - 8, 8);
    
    if (currentDigit == Minutes) {
      tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    }
    // Draw minutes
    if (mm < 10) xpos += tft.drawChar('0', xpos, ypos, 8); // Add minutes leading zero
    xpos += tft.drawNumber(mm, xpos, ypos, 8);   

    tft.setTextColor(TFT_WHITE, TFT_BLACK);
              
    xsecs = xpos; // Save seconds 'x' position for later display updates
    xpos = xsecs;
    tft.drawChar(':', xcolon, ypos - 8, 8);     // Hour:minute colon
    xpos += tft.drawChar(':', xsecs, ysecs, 6); // Seconds colon

    
    if (currentDigit == Seconds) {
      tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    }
    //Draw seconds
      if (ss < 10) xpos += tft.drawChar('0', xpos, ysecs, 6); // Add leading zero
      tft.drawNumber(ss, xpos, ysecs, 6);                     // Draw seconds
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
}