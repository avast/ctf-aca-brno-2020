#include "display.h"
#include "terminal.h"
#include "ch_binpin.h"
#include "img_bin_pin.h"

#include "bin_arcane.h"
int cnt=0;

bool getbit(int idx) {
   return (bin_arcane[idx/8] & (1<< (idx % 8)))!=0 ? 1 : 0;
}
void ch_binpin_update(unsigned long tick)
{
     static unsigned long oldtick = 0;
     if ((tick - oldtick)>5000) {
     	oldtick = tick;
      disp_getiface()->fillScreen(0);

     	//disp_getiface()->clear();
  	//disp_getiface()->drawXBitmap(0,0,  bin_pin_bits, bin_pin_width, bin_pin_height, 0xFFFF, 0);


   int s = sizeof(bin_arcane);


  
  int page = cnt % 3;
  
 for (int y=0;y<27;y++)
    for (int x=0;x<48;x++) {
        int bi = (y*48+x)*3 + (page * 27*48*3);
        if (bi<(s*8)) {

            uint16_t c = (getbit(bi)*31)<<11 | (getbit(bi+1)*63)<<5 | (getbit(bi+2)*31);
            
            disp_getiface()->fillRect (x*5,y*5,4,4,c); 
          
         }
         
  }
  cnt++;
	  /*  disp_getiface()->clear();
	    disp_getiface()->setFont(ArialMT_Plain_10);
     	disp_getiface()->setTextAlignment(TEXT_ALIGN_LEFT);     	
     	//disp_getiface()->display();*/
 	}
}



void ch_binpin_start(unsigned long tick)
{
	disp_getiface()->fillScreen(0);
 cnt=0;
	
}








void ch_binpin_input(char* command)
{
   term_print("To start and get first clue, just type $stage START!");
}
