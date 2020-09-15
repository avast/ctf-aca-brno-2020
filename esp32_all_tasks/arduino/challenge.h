typedef void (*updatefnc)(unsigned long tick);
typedef void (*commandfnc)(char* cmd);

// stage structure with callbacks
struct tstage{
  char* code;
  updatefnc update;
  updatefnc start; 
  commandfnc input;
  updatefnc event; 
};


int ch4_init(tstage* stagetable);
int ch4_getstage();
int ch4_nextstage();
unsigned long ch4_update();
int ch4_input(char* input);
String ch4_getMacAddress();
#define CH4_STAGE 1
