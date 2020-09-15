#include "display.h"
#include "challenge.h"
#include "WiFi.h"
#include "img_wifi.h"
#include "esp_wifi.h"
#include "obfuscate.h"
#include "terminal.h"
#include <TFT_eSPI.h>

#include "ch_beacon.h"

#define BEACON_INTERVAL 500
#define BEACON_SSID_OFFSET 38
#define SRCADDR_OFFSET 10
#define BSSID_OFFSET 16
#define SEQNUM_OFFSET 22
#define TOTAL_LINES (sizeof(rick_ssids) / sizeof(char *))


uint16_t escalate[3] = {TFT_YELLOW, TFT_ORANGE, TFT_RED};

extern "C" {
  esp_err_t esp_wifi_80211_tx(wifi_interface_t ifx, const void *buffer, int len, bool en_sys_seq);
}


static uint32_t _rnd_state[4] = { 0x00294823,0x18be6784,0x4ae13d6c,0x2cd672ae };
static char _key[] = { 0xbb,0x0d,0xcb,0x33,0x70,0xeb,0x81,0xe1,0x40,0x2c,0x82,0xcc,0xf9,0xad,0xc7,0x00 };

static char flag[] = {'A','v','a','s','t','{','B','3','a','c','o','N','}'};
static uint8_t baseMac[8];

uint8_t beacon_raw[] = {
  0x80, 0x00,             // 0-1: Frame Control
  0x00, 0x00,             // 2-3: Duration
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff,       // 4-9: Destination address (broadcast)
  0xba, 0xde, 0xaf, 0xfe, 0x00, 0x06,       // 10-15: Source address
  0xba, 0xde, 0xaf, 0xfe, 0x00, 0x06,       // 16-21: BSSID
  0x00, 0x00,             // 22-23: Sequence / fragment number
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,     // 24-31: Timestamp (GETS OVERWRITTEN TO 0 BY HARDWARE)
  0x64, 0x00,             // 32-33: Beacon interval
  0x31, 0x04,             // 34-35: Capability info
  0x00, 0x00, /* FILL CONTENT HERE */       // 36-38: SSID parameter set, 0x00:length:content
  0x01, 0x08, 0x82, 0x84, 0x8b, 0x96, 0x0c, 0x12, 0x18, 0x24, // 39-48: Supported rates
  0x03, 0x01, 0x01,           // 49-51: DS Parameter set, current channel 1 (= 0x01),
  0x05, 0x04, 0x01, 0x02, 0x00, 0x00,       // 52-57: Traffic Indication Map
  // extra byte
  0xFF, 0x01
};

PROGMEM char *rick_ssids[] = {
	"01 A wind comes from the north",
	"02 Blowing little flocks of birds",
	"03 Like spray across the town",
	"04 And a train roaring forth",
	"05 Rushes stampeding down",
	"06 With cries and flying curds",
	"07 Of steam, out of the darkening north",
	"08 Whither I turn and set",
	"09 Like a needle steadfastly",
	"10 Waiting ever to get",
	"11 The news that she is free",
	"12 But ever fixed as yet",
	"13 To the lode of her agony"
};





void send_beacon()
{
    static int retry = 0;
    static int line = 0;
    uint16_t seqnum[TOTAL_LINES] = { 0 };
   // printf("%i %i %s\r\n", strlen(rick_ssids[line]), TOTAL_LINES, rick_ssids[line]);
    uint8_t beacon_rick[500];
    memcpy(beacon_rick, beacon_raw, BEACON_SSID_OFFSET - 1);
    beacon_rick[BEACON_SSID_OFFSET - 1] = strlen(rick_ssids[line]);
    memcpy(&beacon_rick[BEACON_SSID_OFFSET], rick_ssids[line], strlen(rick_ssids[line]));
    memcpy(&beacon_rick[BEACON_SSID_OFFSET + strlen(rick_ssids[line])], &beacon_raw[BEACON_SSID_OFFSET], sizeof(beacon_raw) - BEACON_SSID_OFFSET);

    // Last byte of source address / BSSID will be line number - emulate multiple APs broadcasting one song line each
    memcpy(&beacon_rick[SRCADDR_OFFSET], baseMac,6);
    memcpy(&beacon_rick[BSSID_OFFSET], baseMac,6);

    // Update sequence number
    beacon_rick[SEQNUM_OFFSET] = (seqnum[line] & 0x0f) << 4;
    beacon_rick[SEQNUM_OFFSET + 1] = (seqnum[line] & 0xff0) >> 4;
    seqnum[line]++;
    if (seqnum[line] > 0xfff)
      seqnum[line] = 0;

    // change last byte to flag one
    beacon_rick[sizeof(beacon_raw) + strlen(rick_ssids[line])-1] = flag[line];

    esp_wifi_80211_tx(WIFI_IF_AP, beacon_rick, sizeof(beacon_raw) + strlen(rick_ssids[line]), false);

 
    if ((retry++ % 5)==0) {
	 if (++line >= TOTAL_LINES)
     		line = 0; 
    }
}


void ch_beacon_update(unsigned long tick)
{
     TFT_eSPI* tft= disp_getiface();
     static unsigned long oldtick = 0;
     static int phase = 0;
     if ((tick-oldtick)>BEACON_INTERVAL) {
     	oldtick=tick;
     	send_beacon();    	

      tft->drawXBitmap(120-wifi_width/2,77-wifi_height/2,wifi_anim[phase++ % 3],wifi_width, wifi_height, escalate[phase % 3], 0x0000);
	  /*  disp_getiface()->clear();
	    disp_getiface()->setFont(ArialMT_Plain_10);
     	disp_getiface()->setTextAlignment(TEXT_ALIGN_LEFT);     	
     	disp_getiface()->drawXbm(30,0, wifi_width, wifi_height, wifi_anim[phase++ % 3]);
     	disp_getiface()->drawString(20,52,ch4_getMacAddress());
    	disp_getiface()->display();*/

     tft->setTextColor(TFT_ORANGE, TFT_BLACK);
    tft->setTextDatum(TL_DATUM);

    //drawCentreString()
  
    tft->drawString(ch4_getMacAddress(),  20, 110);
     }
}


void ch_beacon_start(unsigned long tick)
{
    _crypt(_key,_rnd_state);
    TFT_eSPI* tft= disp_getiface();
    tft->fillScreen(0);
    esp_read_mac(baseMac, ESP_MAC_WIFI_STA);


    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);
    esp_wifi_set_storage(WIFI_STORAGE_RAM);
    esp_wifi_set_mode(WIFI_MODE_NULL);
    esp_wifi_start();
    WiFi.softAP("dummy", "yummy");
    esp_wifi_set_promiscuous(true);
  
   
    esp_wifi_set_channel(8, WIFI_SECOND_CHAN_NONE);
    
}
