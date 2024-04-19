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

int pinButtonsADC = 6;

// TFT_eSPI tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT);       // Invoke custom library

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
  // tft.init();
  // tft.setRotation(0);
  // tft.fillScreen(TFT_BLACK);
  // tft.setTextSize(1);
  // tft.setTextColor(TFT_WHITE);
  // tft.setCursor(0, 0);
  kit.setVolume(0);

}

void loop() {
  // tft.fillScreen(TFT_BLACK);
  // delay(1000);
  // tft.fillScreen(TFT_WHITE);
  // delay(1000);
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

  // tft.fillScreen(TFT_BLACK);
  // tft.setFreeFont(FF18);                 // Select the font
  // tft.drawString(sFF7, 160, 60, GFXFF);// Print the string name of the font
  // tft.setFreeFont(FF7);
  // tft.drawString(String(checkButtons(pinButtonsADC)), 160, 120, GFXFF);
  // tft.drawString(String(analogReadMilliVolts(pinButtonsADC)), 160, 150, GFXFF);
  // tft.drawString(String(analogRead(pinButtonsADC)), 160, 180, GFXFF);
  // delay(100);

}

// #define GRIDX 120
// #define GRIDY 90
// #define CELLXY 4

// // #define GRIDX 320
// // #define GRIDY 240
// // #define CELLXY 2

// #define GEN_DELAY 0

// //Current grid
// uint8_t grid[GRIDX][GRIDY];

// //The new grid for the next generation
// uint8_t newgrid[GRIDX][GRIDY];

// //Number of generations
// #define NUMGEN 600

// uint16_t genCount = 0;


// //Draws the grid on the display
// void drawGrid(void) {

//   uint16_t color = TFT_WHITE;
//   for (int16_t x = 1; x < GRIDX - 1; x++) {
//     for (int16_t y = 1; y < GRIDY - 1; y++) {
//       if ((grid[x][y]) != (newgrid[x][y])) {
//         if (newgrid[x][y] == 1) color = 0xFFFF; //random(0xFFFF);
//         else color = 0;
//         tft.fillRect(CELLXY * x, CELLXY * y, CELLXY, CELLXY, color);
//       }
//     }
//   }
// }

// //Initialise Grid
// void initGrid(void) {
//   for (int16_t x = 0; x < GRIDX; x++) {
//     for (int16_t y = 0; y < GRIDY; y++) {
//       newgrid[x][y] = 0;

//       if (x == 0 || x == GRIDX - 1 || y == 0 || y == GRIDY - 1) {
//         grid[x][y] = 0;
//       }
//       else {
//         if (random(3) == 1)
//           grid[x][y] = 1;
//         else
//           grid[x][y] = 0;
//       }

//     }
//   }
// }

// // Check the Moore neighbourhood
// int getNumberOfNeighbors(int x, int y) {
//   return grid[x - 1][y] + grid[x - 1][y - 1] + grid[x][y - 1] + grid[x + 1][y - 1] + grid[x + 1][y] + grid[x + 1][y + 1] + grid[x][y + 1] + grid[x - 1][y + 1];
// }

// //Compute the CA. Basically everything related to CA starts here
// void computeCA() {
//   for (int16_t x = 1; x < GRIDX; x++) {
//     for (int16_t y = 1; y < GRIDY; y++) {
//       int neighbors = getNumberOfNeighbors(x, y);
//       if (grid[x][y] == 1 && (neighbors == 2 || neighbors == 3 ))
//       {
//         newgrid[x][y] = 1;
//       }
//       else if (grid[x][y] == 1)  newgrid[x][y] = 0;
//       if (grid[x][y] == 0 && (neighbors == 3))
//       {
//         newgrid[x][y] = 1;
//       }
//       else if (grid[x][y] == 0) newgrid[x][y] = 0;
//     }
//   }
// }



// void loop() {

//   //Display a simple splash screen
//   tft.fillScreen(TFT_BLACK);
//   tft.setTextSize(2);
//   tft.setTextColor(TFT_WHITE);
//   tft.setCursor(40, 5);
//   tft.println(F("Arduino"));
//   tft.setCursor(35, 25);
//   tft.println(F("Cellular"));
//   tft.setCursor(35, 45);
//   tft.println(F("Automata"));

//   delay(1000);

//   tft.fillScreen(TFT_BLACK);

//   initGrid();

//   genCount = NUMGEN;

//   drawGrid();

//   //Compute generations
//   for (int gen = 0; gen < genCount; gen++)
//   {
//     computeCA();
//     drawGrid();
//     delay(GEN_DELAY);
//     for (int16_t x = 1; x < GRIDX-1; x++) {
//       for (int16_t y = 1; y < GRIDY-1; y++) {
//         grid[x][y] = newgrid[x][y];
//       }
//     }

//   }
// }





