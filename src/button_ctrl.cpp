#include <Arduino.h>

void ADC_setup(int resolution = 12, adc_attenuation_t attenuation = ADC_11db) {
    analogReadResolution(resolution);
    analogSetAttenuation(attenuation);
}

//checks adc if any button is pressed, returns 0 for none and 1-6 for coresponding buttons
int checkButtons(int pinNum) {
    uint32_t buttonVal = analogReadMilliVolts(pinNum);
    
    if (buttonVal <= 1300 && buttonVal > 1120) {
        return 1;
    }
    if (buttonVal <= 1120 && buttonVal > 920) {
        return 2;
    }
    if (buttonVal <= 920 && buttonVal > 630) {
        return 3;
    }
    if (buttonVal <= 630 && buttonVal > 500) {
        return 4;
    }
    if (buttonVal <= 500 && buttonVal > 310) {
        return 5;
    }
    if (buttonVal <= 310) {
        return 6;
    }
    return 0;
}

/*  
    #include <../lib/Free_Fonts.h>
    #include <../lib/button_ctrl.h>

    //main loop code for debugging. Shows returned pin number,
    //measured millivolts (uncalibrated) and binary adc value
    
    tft.fillScreen(TFT_BLACK);
    tft.setFreeFont(FF18);                 // Select the font
    tft.drawString(sFF7, 160, 60, GFXFF);// Print the string name of the font
    tft.setFreeFont(FF7);
    tft.drawString(String(checkButtons(pinButtonsADC)), 160, 120, GFXFF);
    tft.drawString(String(analogReadMilliVolts(pinButtonsADC)), 160, 150, GFXFF);
    tft.drawString(String(analogRead(pinButtonsADC)), 160, 180, GFXFF);
    delay(100);
*/