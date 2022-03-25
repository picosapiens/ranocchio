//-----------------------------------------------------------------------------
// ranocchio.cpp.ino
//-----------------------------------------------------------------------------
// Copyright 2022 Picosapiens
//
// This file is part of Ranocchio
//
//  Ranocchio is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  Ranocchio is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with Girino.  If not, see <http://www.gnu.org/licenses/>.
//
//-----------------------------------------------------------------------------


#include "ranocchio.h"
//include "TouchScreen_kbv.h"
#include "TouchScreen.h"
#include "touchkbd.h"
//include <SoftwareSerial.h>

//bool state;

//-----------------------------------------------------------------------------
// Girino Variables
//-----------------------------------------------------------------------------

volatile  boolean wait;
         uint16_t waitDuration;
volatile uint16_t stopIndex;
volatile uint16_t ADCCounter=0;
volatile  uint8_t ADCBuffer[ADCBUFFERSIZE];
volatile  boolean freeze;

          uint8_t prescaler;
          uint8_t triggerEvent;
          uint8_t threshold;

             char commandBuffer[COMBUFFERSIZE+1];

             bool SDready;
            

MCUFRIEND_kbv tft;
uint16_t pixels[SCREENWIDTH];
int16_t pixelsx;

uint16_t ID;

uint8_t triggertype = 0;

volatile uint32_t dtbuffered_ns = 6535;
volatile uint32_t vresbuffered_uV = 19607;
volatile int16_t scrollindex=0;
volatile int32_t verticalmidpoint;
int16_t cursorpos=0;
int16_t rightmostindex=0;

uint8_t rightfunc;

uint8_t leftfunc;

File root;


void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ID = tft.readID(); //
  Serial.print("ID = 0x");
  Serial.println(ID, HEX);
  tft.begin(ID);
  tft.setRotation(1); // Landscape
  tft.fillScreen(COLOR_BLACK);

  // Clear buffers
  memset( (void *)ADCBuffer, 0, sizeof(ADCBuffer) );
 //memset( (void *)commandBuffer, 0, sizeof(commandBuffer) );
  ADCCounter = 0;
  wait = false;
  waitDuration = ADCBUFFERSIZE-1; // Subtract a small amount of pretrigger time if desired, but see bug report
  stopIndex = -1;
  freeze = false;

  triggerEvent = 3;

  threshold = 127;

  // Activate interrupts
  sei();
  
  //initPins();
  //initADC();
  /*initAnalogComparator();

  Serial.println("Girino ready");*/
  // Something about starting up girino is making the touch screen always read tp.z = 1024
  // Maybe it doesn't like it being left adjusted? rawVal = (ADCL | (ADCH << 8))
  // initADC makes it go to 1023. Something in there isn't playing nice with analogRead()

  TCCR5B = TCCR5B & B11111000 | B00000001;  // for PWM frequency of 31372.55 Hz
  //TCCR5B = TCCR5B & B11111000 | B00000010;  // for PWM frequency of  3921.16 Hz on pins 44-46  https://www.etechnophiles.com/how-to-change-pwm-frequency-of-arduino-mega/
  pinMode(46,OUTPUT);
  analogWrite(46,128); // For the negative charge pump
  pinMode(45,OUTPUT);
  analogWrite(45,128); // For the positive charge pump
 
  vcoarseindex = 3;
  vfineadjust = 0;
  vpower = 5;
  triggerlevel = 160;
  pinMode(44,OUTPUT);
  analogWrite(44,triggerlevel);
  MySettings.uVperdiv = pow((long int)10,vpower)*(vcoarsescale[vcoarseindex]+vfineadjust);
  MySettings.usperdiv = 2000;
  MySettings.ADCprescaler = 8;
  MySettings.displayrms = true;
  verticalmidpoint = 0;
  #warning ADCprescaler=4 doesn't work -- may need to do something to get it to stop at 6 bits?
  rightfunc = SCALE;
  leftfunc = COARSEADJUST;
  triggertype = RISINGEDGE;
  pinMode(18,INPUT);
  SDready = false;
}

void loop() {
  //char s[10] = "";
  //touchkeyinput(s, 8, "");
  mainMenu();

}
