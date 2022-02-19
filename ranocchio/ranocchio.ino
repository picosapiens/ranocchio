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
            

MCUFRIEND_kbv tft;
uint16_t pixels[PLOTTERH];
int16_t pixelsx;

uint16_t ID;

volatile uint32_t dtbuffered_ns = 6535;
volatile uint32_t vresbuffered_uV = 19607;
volatile int16_t scrollindex=0;
int16_t cursorpos=0;
int16_t rightmostindex=0;

uint8_t rightfunc;

uint8_t leftfunc;

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

  analogWrite(46,128);

  vcoarseindex = 3;
  vfineadjust = 0;
  vpower = 5;
  MySettings.uVperdiv = pow((long int)10,vpower)*(vcoarsescale[vcoarseindex]+vfineadjust);
  MySettings.usperdiv = 2000;
  MySettings.ADCprescaler = 8;
  #warning ADCprescaler=4 doesn't work -- may need to do something to get it to stop at 6 bits?
  rightfunc = SCALE;
  leftfunc = COARSEADJUST;
}

void loop() {
  
  mainMenu();

}
