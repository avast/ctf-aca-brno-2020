#include "display.h"
#include "terminal.h"
#include "obfuscate.h"
#include "img_2o5.h"
#include "ch_2of5.h"

//AVAST(BAUD0TRULES)
static uint32_t _rnd_state[4] = {0x00294823,0x18be6784,0x4ae13d6c,0x2cd672ae};
static char _key[] = {0xf3,0x12,0xcb,0x13,0x50,0xcb,0xa1,0xb2,0x40,0x5e,0xb6,0xeb,0xa6,0xb7,0xe8,0xc1,0xc5,0x74,0xec,0x54,0x00};
static char*  msg="AVAST2OF5POSTNET";//&_key[2];
static char  encoded[60];
static uint8_t cnt = 0;
static uint8_t pos = 0;

uint8_t code[10] = {B11000,B00011,B00101,B00110,B01001,B01010,B01100,B10001,B10010,B10100}; 
uint8_t f=0;
void ch_2of5_update(unsigned long tick)
{
 static unsigned long oldx = 0;
 if ((tick-oldx)>500) {
     

    f++;

    if (((f % 2)==0) && (pos<cnt)) { 
      disp_getiface()->fillRect(35,120,168,8, TFT_ORANGE);
    } else
    {
       disp_getiface()->fillRect(35,120,168,8, TFT_BLACK);
    }
    
    
    
    oldx=tick;
    static bool ref=true;
    if (pos<cnt) {
    if (!ref) {
      ref = true;
      disp_getiface()->fillScreen(0);
    };
    for (int x=0;x<5;x++)
    {
        disp_getiface()->fillRect(x*40+35,20,8, 80, TFT_BLACK);
      	if (encoded[pos] & (1<<(4-x))) {
      		disp_getiface()->fillRect(x*40+35,60,8, 40, TFT_WHITE);
	      } else {
		      disp_getiface()->fillRect(x*40+35,20,8, 80, TFT_WHITE);
	      }

    
    
    };
    } else {
if (ref) {
      ref = false;
      disp_getiface()->fillScreen(0);
    };
      
      disp_getiface()->pushImage(128-64, 77-64,  128, 128, img_2o5);
    }
    
    if ((f % 2)==0) { 
      pos++;
      if (pos>cnt+4)
	      pos = 0;

    }
  
    
    //disp_getiface()->display();
}
}


void ch_2of5_start(unsigned long tick)
{
//    deobfuscate key
    _crypt(_key,_rnd_state);
  
      disp_getiface()->fillScreen(0);


    cnt=0;
    for (int i=0;i<strlen(msg);i++) {  
          
            encoded[cnt++] = code[msg[i]/10];
            encoded[cnt++] = code[msg[i]%10];

     }

}
