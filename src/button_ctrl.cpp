#include <Arduino.h>

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