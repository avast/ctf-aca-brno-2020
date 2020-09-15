#include <Wire.h>
#include "terminal.h"
#include "display.h"
#include "esp_wifi.h"
//#include "img_find.h"
#include "obfuscate.h"
#include "challenge.h"

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "esp_bt_device.h"
#include "ch_ble.h"
#include "img_ble.h"


//String maclist[64][4]; 
//int listcount = 0;

bool _BLEClientConnected = false;
//String defaultTTL = "60"; // Maximum time (Apx seconds) elapsed before device is consirded offline

BLEDescriptor 	  firstDescriptor(BLEUUID((uint16_t)0x2901));
BLECharacteristic firstCharacteristic(BLEUUID((uint16_t)0x2AB6), BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);

BLEDescriptor 	  secondDescriptor(BLEUUID((uint16_t)0x2901));
BLECharacteristic secondCharacteristic(BLEUUID((uint16_t)0x2A25), BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);

BLEDescriptor 	  thirdDescriptor(BLEUUID((uint16_t)0x2901));
BLECharacteristic thirdCharacteristic(BLEUUID((uint16_t)0x2A3D), BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);

BLEDescriptor     fourthDescriptor(BLEUUID((uint16_t)0x2901));
BLECharacteristic fourthCharacteristic(BLEUUID((uint16_t)0x2A3D), BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);


class MyServerCallbacks : public BLEServerCallbacks {
	void onConnect(BLEServer* pServer) {
		_BLEClientConnected = true;
	};

	void onDisconnect(BLEServer* pServer) {
		_BLEClientConnected = false;
	}
};

static char bledress[18];
//===== SETUP =====//
void ch_ble_start(unsigned long tick) {
  	BLEDevice::init("ACA2020");
	const uint8_t* add = esp_bt_dev_get_address();
	char tmp[4];

  disp_getiface()->setTextSize(2);
  disp_getiface()->fillScreen(TFT_BLACK);  
	
	for (int i=0;i<6;i++) {
		sprintf(tmp, "%02X", add[i]);
		bledress[i*3] = tmp[0];
		bledress[i*3+1] = tmp[1];
		bledress[i*3+2] =':';
	}
	bledress[17]=0;	

  	// Create the BLE Server
	BLEServer *pServer = BLEDevice::createServer();
	pServer->setCallbacks(new MyServerCallbacks());

	// Create the BLE Service
	BLEService *pService = pServer->createService(BLEUUID((uint16_t)0x181C));
  	firstDescriptor.setValue("1");
	firstCharacteristic.addDescriptor(&firstDescriptor);
	
	
  	secondDescriptor.setValue("2");
	secondCharacteristic.addDescriptor(&secondDescriptor);

  	thirdDescriptor.setValue("3");
	thirdCharacteristic.addDescriptor(&thirdDescriptor);

  fourthDescriptor.setValue("4");
  fourthCharacteristic.addDescriptor(&fourthDescriptor);





	// https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.descriptor.gatt.client_characteristic_configuration.xml
	// Create a BLE Descriptor
	//firstCharacteristic.addDescriptor(new BLE2902());


	pService->addCharacteristic(&firstCharacteristic);
	pService->addCharacteristic(&secondCharacteristic);
	pService->addCharacteristic(&thirdCharacteristic);
  pService->addCharacteristic(&fourthCharacteristic);	
	pService->start();
	

	// Start advertising
	pServer->getAdvertising()->start();

  //_crypt(_key,_rnd_state);
  
  //unlocked = false;
  /* setup wifi */
  
}


//===== LOOP =====//
void ch_ble_update(unsigned long tick) {
  static unsigned long x = 0;
  if ((tick-x)>500) {
     x=tick;

    //if (unlocked) {
      //disp_getiface()->setFont(ArialMT_Plain_16);
      //disp_text_center(&_key[2], 1);
   //} else {

    //disp_getiface()->clear();

	if (_BLEClientConnected) {


		//BLEData *aD = new BLEData();
		//GetBLEData(aD);
		static int cnt=0;



		if ((cnt%4)==0) {
			firstCharacteristic.setValue((uint8_t*)"N3q8ryccAAQwIXsDnwEAAAAAAAAiAAAAAAAAAHufYJTgAxQBLF0AJhYAAzIAR/M/YOYrCIl8wx1fbjjHzStzq42k7oEO8qKzTzpLGdLgm10/MZi2SRV6siKacIFZve+qdXi4boZX1Y4Xq8X57LDhd7xLXE0ept/T", 160);
			firstCharacteristic.notify();
		}
		if ((cnt%4)==1) {	
		secondCharacteristic.setValue((uint8_t*)"tmQAxzwEuiMwFbd1QObWmetRMeB/bv+SmZzSmwWReV9O01outG8XD8Ffcd4dqSAk08NWH9xMNCM9WSrwa7hqL3c79zk/3++/CLW3dpFNSPCBgKMalnm7N+MQRp5OzgEReG+Ar+r8aPgZ62o3XoIYP2uqDP0TAi6T", 160);
		secondCharacteristic.notify();
		}

		if ((cnt%4)==2) {	
		thirdCharacteristic.setValue((uint8_t*)"aNmUiaXYStFOI/Tx8ljUsDqueA8IdJ3DO1bV+UdjXT0zaOV+7VoYNEsehdcWAB12u+LR07Dp94pPDLYFMRDUtn788exftToOtkCgjd5Pwuxv79ICMqljVGI37EopI7XURIAAAAAAgTMHrg/VOPjOFyTT/rNwI+Y0", 160);
		thirdCharacteristic.notify();
		}

      if ((cnt%4)==3) { 
    fourthCharacteristic.setValue((uint8_t*)"E/NI+rRNJICI6a0sdDfbGQnII4EhBqcySaOeW15Em+wU1KBHLCCs4bOKwuDmSohmcMH9xhG0QoiJqhfblPU6dVNfT9rrZXcWJ594ozHW6tfR1gcJAAAAFwaBNAEJawAHCwEAASMDAQEFXQAQAAAMgIYKASJvfv8AAA==", 164);
    fourthCharacteristic.notify();
    }
		cnt+=1;

	}

	  TFT_eSPI* tft= disp_getiface();
   
     static int phase = 0;
	 // disp_getiface()->clear();
	// disp_getiface()->setFont(ArialMT_Plain_10);
    // disp_getiface()->setTextAlignment(TEXT_ALIGN_LEFT);     	
    
     
    // disp_getiface()->drawXbm(0,0, ble_width, ble_height, ble_anim[phase++ % 2]);
	// disp_getiface()->drawString(20,52,bledress);
//     disp_getiface()->drawString(20,52,ch4_getMacAddress());
     //disp_getiface()->display();

    tft->drawXBitmap(120-ble_width/2,77-ble_height,  ble_anim[phase++ % 2], ble_width, ble_height, TFT_BLUE, 0);


    tft->setTextColor(TFT_ORANGE, TFT_BLACK);
    tft->setTextDatum(TL_DATUM);

    //drawCentreString()
  
    tft->drawString(ch4_getMacAddress(),  20, 110);

	}

 }    
    
