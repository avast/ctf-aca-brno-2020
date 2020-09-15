#include <TFT_eSPI.h>
#include <SPI.h>

#ifndef TFT_DISPOFF
#define TFT_DISPOFF 0x28
#endif

#ifndef TFT_SLPIN
#define TFT_SLPIN   0x10
#endif

#define TFT_MOSI            19
#define TFT_SCLK            18
#define TFT_CS              5
#define TFT_DC              16
#define TFT_RST             23

#define TFT_BL          4  // Display backlight control pin
#define ADC_EN          14
#define ADC_PIN         34
#define BUTTON_1        35
#define BUTTON_2        0

TFT_eSPI tft = TFT_eSPI(135, 240); // Invoke custom library

#include "display.h"





//                                      static SSD1306 display(0x3c, 5, 4);

void disp_init() {
  //pin init

  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(0, 0);
  tft.setTextDatum(MC_DATUM);
  tft.setTextSize(2);
  tft.setSwapBytes(true);
 


	
}

void disp_text_center(char* text, bool clear){
  /*if (clear)
    display.clear();
    
  display.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
  display.drawString( display.width()/2, display.height()/2, text);  
  display.display();*/
}

TFT_eSPI* disp_getiface(){
  return &tft;
}

void disp_update(unsigned long tick) {



}

/*
void disp_xbm(int x, int y, int w, int h, uint8_t* data)
{

    int scanline = w / 8 + w%8 ? 1 : 0;
    for (int i = 0; i<w; w++)
      for (int j = 0; j<h; h++)
      {

          if (data[i / 8 + j* scanline] & (1<<i%8)) {


          } 

          

      }
*/
      





