#include "display.h"
#include "terminal.h"
#include "ch_logo.h"
#include "img_avast.h"
#include <TFT_eSPI.h>
//#include "img_usb.h"
#include "esp_adc_cal.h"


//uint16_t buffer[135*240];

char txt[17];
char ca[]= "CYBER ADVENTURE";
char mask[17]={0};
int rounds=0;
uint8_t error=255;
uint8_t ypos=110;

void espDelay(int ms)
{   
    esp_sleep_enable_timer_wakeup(ms * 1000);
    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH,ESP_PD_OPTION_ON);
    esp_light_sleep_start();
}


void ch_logo_update(unsigned long tick)
{

    TFT_eSPI* tft= disp_getiface();


	static unsigned long oldtick = 0;
    if ((tick-oldtick)>10) {
      oldtick=tick;

    tft->setTextColor(TFT_GREEN, TFT_BLACK);

     
    //tft.fillScreen(TFT_BLACK);
    tft->setRotation(1);
    
    for (int i=0;i<strlen(ca);i++) {

        uint8_t msk = (mask[i]==2) ? 0 : mask[i];

        if (msk==0)

          tft->fillRect(i*14+17,ypos, 14, 14, TFT_BLACK);
      
          txt[i] = msk ? ca[i] : rand() % 64 + 32;

      

      if (msk)
        
        tft->setTextColor( (msk==3) ? rand()%65535 :   0xf363, TFT_BLACK);
       else
         //tft.setTextColor(rand()%65535, TFT_BLACK);
         tft->setTextColor(TFT_DARKGREY, TFT_BLACK);
      
      tft->drawChar(txt[i],  i*14+17, ypos);
    }
    txt[strlen(ca)]='\0';


    
    //tft.drawString(txt,  tft.width() / 2, tft.height() / 2 );
    
    
    
    rounds++;


    // count if we masked everythhing already
    uint8_t masked = 0;
    for (int i=0;i<strlen(mask);i++) { 
      masked = (mask[i]) ? (masked+1) : 0;
    }



    // every now and then
    if (rounds% (rand()%20+20)==0) {
      uint8_t idx = 0;
      // if we have not masked everything
      if (masked<strlen(ca)) {

          // try to mask one
          do {
           idx=rand()%strlen(ca);
          } while (mask[idx]!=0);
          mask[idx]=1;

          
       } else {
            
          for (int i=0;i<strlen(mask);i++) {
            if (rand()%100<5) {
                  mask[i] = rand()%2+2;
                  idx++;
             } else mask[i]=1;
                  if (idx>rand()%5) break;
          }
          }
    }
           
    
	}

}


void ch_logo_start(unsigned long tick)
{
	TFT_eSPI* tft= disp_getiface();
	tft->fillScreen(TFT_BLACK);  
  tft->setTextSize(2);
    //img_unpack( (char*)pck, sizeof(pck), imgbuffer);
      
    tft->pushImage(10, 10,  220, 69, img_avast);
	//memset(buffer, 0x7f, 135*240*2);

}


void ch_logo_input(char* command)
{
   term_print("To start and get first clue, just type $stage START!");
}
