// Setup for the ESP32 S2 Kaluga
// Note SPI DMA with ESP32 S2 is not currently supported

#define errorline

#define USER_SETUP_ID 420
// See SetupX_Template.h for all options available

#define ILI9341_DRIVER
// #define ILI9341_2_DRIVER
// #define ST7796_DRIVER
// #define ILI9488_DRIVER

// For ST7735, ST7789 and ILI9341 ONLY, define the colour order IF the blue and red are swapped on your display
// Try ONE option at a time to find the correct colour order for your display

//  #define TFT_RGB_ORDER TFT_RGB  // Colour order Red-Green-Blue
//  #define TFT_RGB_ORDER TFT_BGR  // Colour order Blue-Green-Red


//ESP32 C2 Kaluga
#define TFT_WIDTH   320
#define TFT_HEIGHT  240
// #define TFT_SDA_READ      // This option is for ESP32 ONLY, tested with ST7789 and GC9A01 display only



#define TFT_MOSI  9
#define TFT_MISO  8
#define TFT_SCLK  15
#define TFT_CS    11
#define TFT_DC    13
#define TFT_RST   16

//#define TOUCH_CS 16 // Optional for touch screen

#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define LOAD_FONT6
#define LOAD_FONT7
#define LOAD_FONT8
#define LOAD_GFXFF

#define SMOOTH_FONT

// FSPI port will be used unless the following is defined
#define USE_HSPI_PORT

//#define SPI_FREQUENCY  27000000
#define SPI_FREQUENCY  40000000   // Maximum for ILI9341

#define SPI_READ_FREQUENCY  6000000 // 6 MHz is the maximum SPI read speed for the ST7789V

#define SPI_TOUCH_FREQUENCY 2500000