#include "ansiterm.h"

void    term_init(char* banner);
int     term_update();
char*   term_getinput();
void    term_print(char* text, int fore=ANSWHITE, int back=ANSBLACK);
void    term_setprompt(char* inprompt);
#define TERM_USERINPUT 1