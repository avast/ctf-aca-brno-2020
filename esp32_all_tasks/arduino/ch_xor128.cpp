#include "terminal.h"
#include "display.h"
#include "img_mem.h"
#include "ch_xor128.h"

//intended solution: %x %x %x %x %x %s
//char FLAG[] = "AVAST{b@by_3ch0_aga1n!?}";
char FLAG[] = {0x64, 0x68, 0x6d, 0x76, 0x5c, 0xa5, 0xc0, 0xff, 0xac, 0xa0, 0x3c, 0x0f, 0xe8, 0xfd, 0x1c, 0xe9, 0x45, 0x40, 0x50, 0x00, 0x6b, 0x98, 0xf7, 0x7e, 0x1f};


char input_buffer[260];
//char input_len = 0;

//https://en.wikipedia.org/wiki/Xorshift
uint32_t xorshift128(uint32_t * state)
{
  /* Algorithm "xor128" from p. 5 of Marsaglia, "Xorshift RNGs" */
  uint32_t s, t = state[3];
  t ^= t << 11;
  t ^= t >> 8;
  state[3] = state[2]; state[2] = state[1]; state[1] = s = state[0];
  t ^= s;
  t ^= s >> 19; 
  state[0] = t;
  return t;
}

uint32_t rnd_state[4] = {1,2,3,4};

void crypt()
{
  int sz = sizeof(FLAG);  
  for (int i = 0; i<sz; ++i)
  {
    FLAG[i] ^= xorshift128(rnd_state)&0xffu;
    //Serial.printf("0x%02x, ", FLAG[i]&0xff);
  }
  //Serial.print("\n");
}



void do_echo(char * str, char * flag)
{
  char aaa[20];
  aaa[0] = 0;
  *(char**)(aaa+4) = flag;
  //*(int*)aaa = 0x00000000;
  //*(int*)(aaa+8) = 0xcafecafe;
  //Serial.printf("hint: 0x%x 0x%x 0x%x\n", str, flag);
  Serial.print("Welcome ");
  Serial.printf(str);
  Serial.print("\n");
  Serial.print(aaa);
}


void ch_xor128_update(unsigned long tick)
{
     
    
     disp_getiface()->drawXBitmap(128-mem_width/2, 77-mem_height/2 , mem_bits , mem_width, mem_height, TFT_RED, 0 );     
    

}



void ch_xor128_start(unsigned long tick)
{
  term_setprompt("name");
  disp_getiface()->fillScreen(0);
  crypt();
}

void ch_xor128_input(char* command)
{


      //char flag[200];
      //strcpy(flag, FLAG);
      do_echo( command, FLAG );
      

 


}

