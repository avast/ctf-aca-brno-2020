#include "display.h"
#include "terminal.h"

//#include "img_avast.h"
#include <TFT_eSPI.h>
//#include "img_usb.h"
#include "esp_adc_cal.h"


#include <driver/dac.h>
#include <math.h>
#include "ch_scope_qr.h"
#include "qrcode.h"
#include "img_wave.h"

 // Create the QR code
QRCode qrcode;
int x = qrcode_getBufferSize(3);
uint8_t qrcodeData[256];
uint8_t* codedata;
uint8_t  codesize;

void display_circle()

{



  for(float f = 0; f < M_PI * 2; f+= 0.01)
  {
    dac_output_voltage(DAC_CHANNEL_1, sin(f) * 120 + 120);
    dac_output_voltage(DAC_CHANNEL_2, cos(f) * 120 + 120);

  }

  dac_output_voltage(DAC_CHANNEL_1, 255);
  dac_output_voltage(DAC_CHANNEL_2, 255);

}

void display_qr(uint8_t qsize, uint8_t* data)
{

    int sc =4;
    int roz = 128;
    int qs = qsize * sc;
    int cw =  int((roz-qs)/2); 
  
    for (uint16_t y = 0; y < roz; y++) {
        for (uint16_t x = 0; x < roz; x++) {

            bool pixel = true;
      
            if (!((x<cw) || (y<cw) || (x>cw+qs) || (y>cw+qs)))
            {
              pixel = !data [ (x-cw) / sc + ((y-cw) / sc)*qsize];
              
             };
         
           if (pixel ) {
            
            dac_output_voltage(DAC_CHANNEL_1, x*(256/roz));
            dac_output_voltage(DAC_CHANNEL_2, y*(256/roz)); 
            
            }

        }

    }


  dac_output_voltage(DAC_CHANNEL_1, 255);
  dac_output_voltage(DAC_CHANNEL_2, 255);
  
}




void ch_scope_qr_update(unsigned long tick)
{
    static unsigned long oldtick = 0;
    if ((tick-oldtick)>10) {
      oldtick=tick;


      TFT_eSPI* tft= disp_getiface();


      //display_circle();

      display_qr(codesize, codedata);
    }
 //  dac_output_voltage(DAC_CHANNEL_1, 255);
//  dac_output_voltage(DAC_CHANNEL_2, 255);
  //delay(10);

}




void ch_scope_qr_start(unsigned long tick)
{


  TFT_eSPI* tft= disp_getiface();
  //if (!buff)
  //  buff = new short[1024];
  //assert(buff);
  tft->fillScreen(0);
  tft->fillTriangle(145,10,165,10,155,0, TFT_GREEN);
  tft->fillTriangle(170,10,190,10,180,0, TFT_RED);
   tft->fillTriangle(220,10,240,10,230,0, TFT_BLUE);
  tft->pushImage(128-64, 77-64,  128,128, img_wave);

    //img_unpack( (char*)pck, sizeof(pck), imgbuffer);
      
  //  tft->pushImage(10, 10,  220, 69, img_avast);
 //	memset(buffer, 0x7f, 135*240*2);
  qrcode_initText(&qrcode, qrcodeData, 3, 2, "em50MXBGcDBjcg==");
  dac_output_enable(DAC_CHANNEL_1);
  dac_output_enable(DAC_CHANNEL_2);
  Serial.print(String(x));
   Serial.print(String(qrcode.size));


  codedata = new uint8_t[qrcode.size*qrcode.size];
  codesize = qrcode.size;
  // generate array
  for (uint16_t y = 0; y < codesize; y++) {
        for (uint16_t x = 0; x < codesize; x++) {
          codedata[x + y*codesize] = qrcode_getModule(&qrcode, x,y);         
        }
  }
 


  
  


}


void ch_scope_qr_input(char* command)
{
   //term_print("To start and get first clue, just type $stage START!");
}
