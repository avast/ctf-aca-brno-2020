#include <TFT_eSPI.h>

void disp_init();
void disp_update(unsigned long tick);
void disp_text_center(char* text, bool clear=false);

// temporrary hack to get interface
TFT_eSPI* disp_getiface();
