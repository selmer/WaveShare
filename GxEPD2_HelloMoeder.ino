#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <GxEPD2_4C.h>
#include <GxEPD2_7C.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <WiFi.h>

#include "GxEPD2_display_selection_new_style.h"

int btnGPIO = 0;

//Wifi Connection
WiFiUDP ntpUDP;
const char SSID[] = "Maaike en Selmer";
const char password[] = "Wodan Kissa Maaike";

//NTP
NTPClient timeClient(ntpUDP);
unsigned long time_now = 0;
int period = 1000*60*3;
//App variables
char const * wdays[] = {"zondag", "maandag", "dinsdag", "woensdag", "donderdag", "vrijdag", "zaterdag"};

void setup() {
  display.init(115200, true, 2, false);  // USE THIS for Waveshare boards with "clever" reset circuit, 2ms reset pulse
  pinMode(btnGPIO, INPUT);
  setupWiFi();

  //Zomertijd Nederland
  timeClient.setTimeOffset(7200);
  timeClient.begin();
  
  setDisplay();
  display.hibernate();
}

void setupWiFi() {
  Serial.begin(115200);
  WiFi.begin(SSID, password);
  while ( WiFi.status() != WL_CONNECTED ) {
  delay ( 500 );
  } 
}

void setDisplay() {
  display.setRotation(2);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_RED);
  int16_t tbx, tby;
  uint16_t tbw, tbh;
  timeClient.update();
  
  String displayText("Het is vandaag " + String(wdays[timeClient.getDay()]));


  display.getTextBounds(displayText, 0, 0, &tbx, &tby, &tbw, &tbh);

  // center the bounding box by transposition of the origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.setTextColor(GxEPD_RED);
    display.print(displayText);    
    
  } while (display.nextPage());
}

void loop(){
  time_now = millis();
  while (millis() <time_now + period){  }
  timeClient.update();
  setDisplay();
};
//https://www.digikey.com/en/maker/tutorials/2022/how-to-avoid-using-the-delay-function-in-arduino-sketches

