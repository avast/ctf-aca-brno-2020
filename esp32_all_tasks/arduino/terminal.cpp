#include "ansiterm.h"

#include "terminal.h"

Ansiterm ansi;
static char inputBuffer[256];
static int idx=0;
static int flags = 0;
static char sprompt[30]="";

void term_init(char* banner){
  ansi.home();//works
  ansi.setBackgroundColor(ANSBLACK);//works
  ansi.setForegroundColor(ANSGREEN);//realterm doesn't do this, macos does
  ansi.eraseScreen();
  Serial.println(banner);
  memset(inputBuffer,0,256);
  flags |=1;
  idx=0;
}

int prompt() {
  ansi.setBackgroundColor(ANSBLACK);//works
  ansi.setForegroundColor(ANSRED);//realterm doesn't do this, macos does
  Serial.print(sprompt);
  Serial.print(">");
  ansi.setForegroundColor(ANSWHITE);
}


void term_setprompt(char* inprompt)
{
  strncpy(sprompt, inprompt,30);
}

void term_print(char* text, int fore, int back)
{
  ansi.setBackgroundColor(back);//works
  ansi.setForegroundColor(fore);//realterm doesn't do this, macos does
  Serial.print(text);

}

int term_update() {

  if (flags & 1) {
	idx=0;
        inputBuffer[idx] = '\0';
  	prompt();
	flags &= ~1;
  }

  if (Serial.available() > 0) {
  
    // read the incoming byte:
    char incomingByte = Serial.read();


    switch (incomingByte) {
       case 8:
	      if (idx>0) {
        	Serial.print((char)incomingByte);
        	Serial.print(' ');
        	ansi.backward(1);
        	inputBuffer[--idx] = '\0';
      		}
         break;

       case 10:
		break; 
       case 13: 
      		Serial.print("\n\r");
		flags |= 1;
		return TERM_USERINPUT;
	  break;
	default:
      		if (idx<256) {
      			inputBuffer[idx++] = incomingByte;
      			inputBuffer[idx] = '\0';
      			Serial.print((char)incomingByte);
		}


    }

    
 }
}

char* term_getinput(){
	return inputBuffer;
}