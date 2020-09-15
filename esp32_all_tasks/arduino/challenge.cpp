#include <Preferences.h>
#include "ansiterm.h"
#include "terminal.h"
#include "challenge.h"
#include "esp_system.h"
#include <string.h>
#define STAGE_KEY "stage"
#define LIFE_KEY "life"
#define MINUTE_TICKS 1000*60
Preferences config;
unsigned long start_tick = 0;
unsigned long last_update = 0;
static int  stage = -1;
static tstage* stages=0;
static char tmp[250];

String ch4_getMacAddress() {
	uint8_t baseMac[6];
	// Get MAC address for WiFi station
	esp_read_mac(baseMac, ESP_MAC_WIFI_STA);
	char baseMacChr[18] = {0};
	sprintf(baseMacChr, "%02X:%02X:%02X:%02X:%02X:%02X", baseMac[0], baseMac[1], baseMac[2], baseMac[3], baseMac[4], baseMac[5]);
	return String(baseMacChr);
}


int ch4_init(tstage* intstages) {
   stages = intstages;
   config.begin("ch4",false);	
   start_tick = config.getULong(LIFE_KEY, 0);
   stage = -1;
   ch4_getstage();
   stages[stage].start(0);
   return stage;
}

int ch4_getstage() {
   if (stage==-1)	
	stage = config.getUChar(STAGE_KEY, 0);
   return stage;	
}

int ch4_nextstage() {
   int tmp = ch4_getstage();
   config.putUChar(STAGE_KEY, tmp + 1);
   stage = -1;
   return ch4_getstage();
}

unsigned long ch4_update()
{
   unsigned long current_tick = millis();
   if (current_tick-last_update>MINUTE_TICKS) {
      config.putULong(LIFE_KEY, start_tick + current_tick);
      last_update = current_tick;    
   }
 
   stages[stage].update(start_tick + current_tick);
	

   return start_tick + current_tick;
   
}



int ch4_input(char* input){

        static int   paramscnt = 0;
	static char* params[20];

	if (input[0]!='$') {
		if ((stage!=-1) && (stages[stage].input))
			stages[stage].input(input);
		
		return 0;
	}

	paramscnt = 0;
	char* ptr = &input[1];
	char* old = ptr;

	while (1) {
	   if ((*ptr==' ') || (*ptr=='\0')) {
		if (ptr!=old) {
			params[paramscnt] = old;
			paramscnt++;
		}
		if (*ptr=='\0')
			break;
		*ptr = '\0';
		ptr++;
		old = ptr;
	   } else {
	       ptr++;
	   }
 	}
	



	if  (paramscnt>0) {



		if ( strcmp( params[0], "stage" ) == 0 ) {

		   if (paramscnt>1) {

			// match code to stage and change the stage
			
			tstage* start = stages;
			while (start && (start->code)) {

				if (strcmp(start->code, params[1])==0) {

					int idx = start-stages;
					sprintf(tmp,"Stage [%s] activated!\n\r", stages[idx].code);
					
   					config.putUChar(STAGE_KEY, idx);
   					stage = -1;
   					ch4_getstage();
					term_print(tmp);			
					term_setprompt("");
					// call start
					stages[stage].start(0);
					break;
					
				}

				start++;
			}
		 	// TODO No such stage



		   }


		} else

		if ( strcmp( params[0], "help" ) == 0 ) {
			  term_print("$stage - run/display challenge stage\n\r");

		} else {
	   
		  term_print("unknown command [",ANSRED);
		  term_print(params[0],ANSWHITE);
		  term_print("] type $help for known commands\n\r",ANSRED);
		}

	}
	return 0;

}
