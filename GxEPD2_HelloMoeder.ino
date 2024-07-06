#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <GxEPD2_4C.h>
#include <GxEPD2_7C.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <WiFi.h>


#include "GxEPD2_display_selection_new_style.h"

//Internet
WiFiUDP ntpUDP;
int btnGPIO = 0;
const char SSID[] = "Maaike en Selmer";
const char password[] = "Wodan Kissa Maaike";

NTPClient timeClient(ntpUDP);

void setup() {
  display.init(115200, true, 2, false);  // USE THIS for Waveshare boards with "clever" reset circuit, 2ms reset pulse
  pinMode(btnGPIO, INPUT);
  setupWiFi();
  timeClient.begin();
  helloWorld();
  display.hibernate();
}

void setupWiFi() {
  Serial.begin(115200);
  WiFi.begin(SSID, password);
  while ( WiFi.status() != WL_CONNECTED ) {
  delay ( 500 );
  }
  
}
//const char HelloWorld[] = "Hello World Moeder!\n\n       Vandaag is het donderdag";

void helloWorld() {
  display.setRotation(2);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_RED);
  int16_t tbx, tby;
  uint16_t tbw, tbh;
  timeClient.update();

  String helloWorld(timeClient.getFormattedTime());
  
  char HelloWorld[helloWorld.length()+1];
  helloWorld.toCharArray(HelloWorld, helloWorld.length());

  display.getTextBounds(HelloWorld, 0, 0, &tbx, &tby, &tbw, &tbh);
  // center the bounding box by transposition of the origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.setTextColor(GxEPD_RED);
    display.print(helloWorld);    
    
  } while (display.nextPage());
}

void loop(){};

