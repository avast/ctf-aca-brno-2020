#include "terminal.h"
#include "wps.h"
#include "display.h"
#include "img_pin.h"
#include "obfuscate.h"

#include "ch_wps.h"

unsigned long wps_pin = 0;
//AVAST{I_Will_N0t_R0ll_My_0wn_Crypt0}
static uint32_t _rnd_state1[4] = {0x00294823,0x18be6784,0x4ae13d6c,0x2cd672ae};
static char _key1[] = {0xbb,0x24,0xcb,0x13,0x50,0xcb,0xa1,0xe1,0x4b,0x40,0xb4,0xc6,0xfa,0x8f,0xe5,0xda,0xb9,0x45,0xe0,0x2f,0x9b,0x31,0x4f,0x3f,0x07,0xe0,0x2a,0xe2,0x49,0x28,0x9e,0x9f,0x09,0x7c,0x7e,0x09,0xfa,0x9e,0x00};
const char* wps_flag = &_key1[2];// "AVAST{I_Will_N0t_R0ll_My_0wn_Crypt0}";
//AVAST{I_Will_N0t\n_R0ll_My_0wn_Crypt0}
static uint32_t _rnd_state[4] = {0x00294823,0x18be6784,0x4ae13d6c,0x2cd672ae};
static char _key[] = {0xbb,0x25,0xcb,0x13,0x50,0xcb,0xa1,0xe1,0x4b,0x40,0xb4,0xc6,0xfa,0x8f,0xe5,0xda,0xb9,0x45,0xb5,0x22,0xf9,0x6d,0x4f,0x0c,0x15,0xd4,0x0c,0x8d,0x0e,0x31,0xaf,0x83,0x38,0x77,0x77,0x0d,0xbe,0xd3,0x1c,0x00};
char* wps_flag_wrap = &_key[2];//"AVAST{I_Will_N0t\n_R0ll_My_0wn_Crypt0}";
static bool success = false;
static char buffer[100];

void ch_wps_start(unsigned long tick)
{
  _crypt(_key1,_rnd_state1);
  _crypt(_key,_rnd_state);
  term_setprompt("PIN");
   disp_getiface()->fillScreen(0);
  success = false;
  randomSeed(analogRead(0));
  for (unsigned char i = 0; i < 7; i++) //Generate WPS pin
    wps_pin = wps_pin * 10 + (rand() % 10);
  wps_pin *= 10;
  wps_pin += checksum(wps_pin);
}

void ch_wps_update(unsigned long tick)
{  
     static bool ref=true;
     static unsigned long x=0;
     if ((tick-x)>100) {
     x=tick;

     if (success) { 
        if (!ref) {
          disp_getiface()->fillScreen(0);
          ref =!ref;
        }
        disp_getiface()->setTextColor(TFT_ORANGE, TFT_BLACK);
        disp_getiface()->setTextDatum(MC_DATUM);

    //drawCentreString()
    
        disp_getiface()->setTextSize(1);
        disp_getiface()->drawString(String("  ")+String(wps_flag),  15, 77);
       //disp_getiface()->setFont(ArialMT_Plain_10);
       //disp_text_center(wps_flag_wrap, 1);
       
     } else {
        if (ref) {
          disp_getiface()->fillScreen(0);
          ref =!ref;
        }
     
     disp_getiface()->drawXBitmap(128-pin_width/2,77-pin_height/2, pin_bits, pin_width, pin_height, TFT_ORANGE, 0);     
     //disp_getiface()->display();

     }
     }

}

void ch_wps_input(char* cmd)
{

    unsigned char result = check(cmd, wps_pin);
    success = generate_response(buffer, 100, result, wps_flag);
    term_print(buffer);

}

