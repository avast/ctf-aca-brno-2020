#include "display.h"
#include "challenge.h"
#include "terminal.h"
#include <TFT_eSPI.h>
#include <Button2.h>


#include "ch_logo.h"
#include "ch_ble.h"
#include "ch_binpin.h"
#include "ch_wps.h"
#include "ch_xor128.h"
#include "ch_find.h"
#include "ch_2of5.h"

#include "ch_scope_qr.h"
#include "ch_radio.h"
#include "ch_beacon.h"
#include "ch_ble.h"

#define BUTTON_1        35
#define BUTTON_2        0

Button2 btn1(BUTTON_1);
Button2 btn2(BUTTON_2);

static char tmp[250];

PROGMEM tstage codetable[] = {
    {"00000",ch_logo_update,ch_logo_start,ch_logo_input},
    {"START",ch_beacon_update,ch_beacon_start, 0,0},          
    {"WP193",ch_wps_update,ch_wps_start, ch_wps_input,0},   
    {"2FRTZ",ch_2of5_update, ch_2of5_start, 0,0},           // AVAST2OF5POSTNET .  //change picture
    {"X40R6",ch_xor128_update,ch_xor128_start, ch_xor128_input,0},  //AVAST{b@by_3ch0_aga1n!?}
    {"RADMX",ch_radio_update, ch_radio_start, 0,0},           // amguruami 70 KhZ
    {"RS0P", ch_scope_qr_update, ch_scope_qr_start, 0,0},      // mag1cSc0pe
    {"HC10", ch_binpin_update,ch_binpin_start, 0,0},          // 
    {"BLu33",ch_ble_update, ch_ble_start,0,0},               // ophidiainherba
    {0,0,0,0}
    };


typedef void (*CallbackFunction) (Button2&);

// route all callbacks for button
 void button_init(Button2* btn, CallbackFunction handler)
{

  btn->setClickHandler(handler);
  btn->setLongClickHandler(handler);
  btn->setDoubleClickHandler(handler);
  btn->setTripleClickHandler(handler);
}


/*-------  NOT USED -------- */
void btn_handler(Button2& btn) {
    switch (btn.getClickType()) {
        case SINGLE_CLICK:
            break;
        case DOUBLE_CLICK:
           // Serial.print("double ");
            break;
        case TRIPLE_CLICK:
           // Serial.print("triple ");
            break;
        case LONG_CLICK:
           // Serial.print("long");
            break;
    }
}


int t =0;
void setup() 
{
  // inititalizes buttons
  button_init(&btn1, btn_handler);
  button_init(&btn2, btn_handler);
  
  // TODO: use ESP32 HW random generator
  randomSeed(analogRead(0));

  // gives some time after bootlader
  delay(1000);
  // starts serial
  Serial.begin(9600);
 
  // initialize display
  disp_init();
  // initialize challenges table
	ch4_init(codetable);
  // welcome message  
  snprintf(tmp,250, "Avast Cyber Adventure 2020 challenge. Welcome!\n\r\n\rYou are currently at stage [%s]\n\r\n\renter answer, command or $help for list of commands\n", 
    codetable[ch4_getstage()].code);
  // init terminal with temporary buffer
  term_init(tmp);  
  // explicitly turn on PULL up on button 1
  pinMode(0, INPUT_PULLUP);

}

void loop()
{
  // get ticks
  unsigned long tick  = ch4_update();
  // update display if needed
	disp_update(tick);
  
  // check buttons        
  btn1.loop();
  btn2.loop();

  // if there is any input from terminal, process it
  if (term_update() == TERM_USERINPUT) {
    char* input = term_getinput();
    ch4_input(input);
  }
  









}
