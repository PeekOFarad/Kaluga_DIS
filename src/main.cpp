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
/*
LAMBADA
E5 = 659
D5 = 587
C5 = 523
H4 = 494
A4 = 440
A4 = 440
C5 = 523
H4 = 494
A4 = 440
G4 = 392
A4 = 440
E4 = 330
D4 = 294
E4 = 330
*/
////////////////////////////////////////////////////////////////////
#include <Arduino.h>
// Walking 1 write and read pixel test

#include <TFT_eSPI.h>
#include <SPI.h>
#include <../.pio/libdeps/esp32-s2-kaluga-1/TFT_eSPI/User_Setups/Setup420.h>
#include <../lib/Free_Fonts.h>
#include <../lib/button_ctrl.h>

#include <../lib/arduino-audiokit-main/src/AudioKitHAL.h>
#include <../lib/arduino-audiokit-main/src/AudioKitSettings.h>
#include <../lib/arduino-audiokit-main/examples/output/SineWaveGenerator.h>
#include <Wire.h>

AudioKit kit;
SineWaveGenerator wave;
const int BUFFER_SIZE = 1024;
uint8_t buffer[BUFFER_SIZE];

int volume = 0;
int my_frequency = 1000;
// Define musical note frequencies for the range from C4 to B5
const int BPM_DEFAULT = 120;  // Default Beats Per Minute (BPM)
const int quarterNoteDuration = 60000 / BPM_DEFAULT; // Duration of a quarter note in milliseconds
struct t_Note_duration {
  int Whole     = 240000/ BPM_DEFAULT;
  int Half      = 120000/ BPM_DEFAULT;
  int Quarter   = 60000/ BPM_DEFAULT;
  int Eighth    = 30000/ BPM_DEFAULT;
  int Sixteenth = 15000/ BPM_DEFAULT;
  int _32nd     = 7500/ BPM_DEFAULT;
  int _64th     = 3750/ BPM_DEFAULT;
};

const t_Note_duration ND;

struct t_Note_freq {
  int C4      = 261;
  int Cs4_Db4 = 277;
  int D4      = 293;
  int Ds4_Eb4 = 311;
  int E4      = 329;
  int F4      = 349;
  int Fs4_Gb4 = 369;
  int G4      = 392;
  int Gs4_Ab4 = 415;
  int A4      = 440;
  int As4_Bb4 = 466;
  int B4      = 493;
  int C5      = 523;
  int Cs5_Db5 = 554;
  int D5      = 587;
  int Ds5_Eb5 = 622;
  int E5      = 659;
  int F5      = 698;
  int Fs5_Gb5 = 739;
  int G5      = 784;
  int Gs5_Ab5 = 830;
  int A5      = 880;
  int As5_Bb5 = 932;
  int B5      = 987;
};

const t_Note_freq NF;

struct Note {
  int frequency;
  int duration;
};
// Define musical notes and their frequencies
Note lambada[] = {
  {NF.E5, ND.Quarter+ND.Eighth},
  {NF.D5, ND.Eighth},
  {NF.C5, ND.Eighth},
  {NF.B4, ND.Eighth},
  {NF.A4, ND.Quarter},
  {0    , ND._64th},
  {NF.A4, ND.Eighth},
  {NF.C5, ND.Eighth},
  {NF.B4, ND.Eighth},
  {NF.A4, ND.Eighth},
  {NF.G4, ND.Eighth},
  {NF.A4, ND.Eighth},
  {NF.E4, ND.Eighth},
  {NF.D4, ND.Eighth},
  {NF.E4, ND.Half+ND.Quarter}
};



int pinButtonsADC = 6;

TFT_eSPI tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT);       // Invoke custom library

void playNote(Note Note) {
  unsigned long startMillis = millis();
  unsigned long currentMilis = startMillis;
  wave.setFrequency(Note.frequency);
  while (currentMilis - startMillis < Note.duration) {
    currentMilis = millis();
    size_t l = wave.read(buffer, BUFFER_SIZE);
    kit.write(buffer, l);
  }
}

void playSong(Note Song[], int size) {  
  for (int i = 0; i < size; ++i) {
    playNote(Song[i]);
  }
}

void setup()   {
  //Audio/////////////////////////////////////////////////////////////////////////////////////////////////////
  LOGLEVEL_AUDIOKIT = AudioKitInfo; 
  Serial.begin(115200);
  // open in write mode
  auto cfg = kit.defaultConfig(KitOutput);
  kit.begin(cfg);

  // 1000 hz
  wave.setFrequency(1000);
  wave.setSampleRate(cfg.sampleRate());
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ADC_setup();

  //Set up the display
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(0, 0);
  kit.setVolume(1);
  kit.setMute(false);
}

void loop() {
  size_t l = wave.read(buffer, BUFFER_SIZE);
  kit.write(buffer, l);

  if (checkButtons(pinButtonsADC) == 6) {
    if (volume < 100) {
      volume++;
    }
    kit.setVolume(volume);
    while (checkButtons(pinButtonsADC) != 0) {}
  }
  else if (checkButtons(pinButtonsADC) == 5) {
    if (volume > 0) {
      volume--;
    }
    kit.setVolume(volume);
    while (checkButtons(pinButtonsADC) != 0) {}
  }
  else if (checkButtons(pinButtonsADC) == 4) {
    my_frequency = 3000;
    wave.setFrequency(my_frequency);
    while (checkButtons(pinButtonsADC) != 0) {
      size_t l = wave.read(buffer, BUFFER_SIZE);
      kit.write(buffer, l);
    }
    wave.setFrequency(1000);
  }
  else if (checkButtons(pinButtonsADC) == 3) {
    my_frequency = 500;
    wave.setFrequency(my_frequency);
    while (checkButtons(pinButtonsADC) != 0) {
      size_t l = wave.read(buffer, BUFFER_SIZE);
      kit.write(buffer, l);
    }
    wave.setFrequency(1000);
  }
  else if (checkButtons(pinButtonsADC) == 2) {
    while (checkButtons(pinButtonsADC) != 0) {}
    int size = sizeof(lambada) / sizeof(lambada[0]);
    playSong(lambada, size);
    wave.setFrequency(0);
  }

  // tft.fillScreen(TFT_BLACK);
  // tft.setFreeFont(FF18);                 // Select the font
  // tft.drawString(sFF7, 160, 60, GFXFF);// Print the string name of the font
  // tft.setFreeFont(FF7);
  // tft.drawString(String(checkButtons(pinButtonsADC)), 160, 120, GFXFF);
  // tft.drawString(String(analogReadMilliVolts(pinButtonsADC)), 160, 150, GFXFF);
  // tft.drawString(String(analogRead(pinButtonsADC)), 160, 180, GFXFF);
  // delay(100);

}