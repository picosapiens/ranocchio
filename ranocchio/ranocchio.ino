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
#include "TouchScreen_kbv.h"

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
  plotVertScale();
  plotHorizScale();
  plotStatusBar();
  plotdata();
}

void loop() {
  // put your main code here, to run repeatedly:
  //state = false;
  //tft.fillRect(0,PLOTTERY+PLOTTERH+2, SCREENWIDTH, 14, COLOR_BLACK);
  
  tp.z = 0;
  while(tp.z < 200 )
  {
    tp = ts.getPoint();
    /*state = tp.z > 200;     //ADJUST THIS VALUE TO SUIT YOUR SCREEN e.g. 20 ... 250
    if(state)
      break;*/
    delay(50);
  }
  pinMode(YP, OUTPUT);      //restore shared pins
  pinMode(XM, OUTPUT);
  
  mappoints(&tp);
  Serial.print("TOUCH: ");
  Serial.print(tp.x);
  Serial.print(" ");
  Serial.print(tp.y);
  Serial.print(" ");
  Serial.println(tp.z);
  if( (PLOTTERX+PLOTTERW/3) > tp.x )                                                   // ******LEFT THIRD******
  {
    //Serial.println("Touch in the left third...");
    if( PLOTTERY + PLOTTERH/2 > tp.y ) // Top half of plot region
    {
      leftfunc = (leftfunc+1)%2;
      plotStatusBar();
      delay(50);
    } else if ( (PLOTTERY + PLOTTERH/2 < tp.y) && (PLOTTERY + PLOTTERH > tp.y) ) { // Bottom half of plot region
      switch(rightfunc)
      {
        case SCALE:
          MySettings.usperdiv = MySettings.usperdiv/(2+4*leftfunc);
          plotdata();
          plotHorizScale();
          plotStatusBar();
          break;
        case SCROLL:
          scrollindex = min( (scrollindex-500*(1+2*leftfunc)*MySettings.usperdiv/dtbuffered_ns) , 0);
          plotdata();
          plotHorizScale();
          plotStatusBar();
          break;
        case CURSOR:
          restoreplotcolumn();
          cursorpos = cursorpos - 1 - 4*leftfunc;
          if(cursorpos<scrollindex);
            cursorpos = scrollindex;
          storeplotcolumn();
          tft.drawFastVLine(PLOTTERX + index_to_hpixels( scrollindex, cursorpos ),PLOTTERY,PLOTTERH,COLOR_RED);
          datapixel(cursorpos,COLOR_GREENYELLOW); // redraw the data pixel
          plotInformation();
          delay(25);
          break;
      }
      //Serial.print("usperdiv = ");
      //Serial.println(MySettings.usperdiv);
    } else if ( PLOTTERY+PLOTTERH < tp.y) { // Very bottom of screen
      //Serial.println("Running scope...");
      memset( (void *)ADCBuffer, 0, sizeof(ADCBuffer) ); // clear buffer
      sei();
      initPins();
      initADC();
      delay(10);
      //ADCCounter=0;
      startADC();
      delay(10); // Takes a little while to get going?
      stopIndex = ( ADCCounter + waitDuration ) % ADCBUFFERSIZE;
      /*Serial.print("stopIndex: ");
      Serial.print(stopIndex);
      Serial.print("\n");*/
      wait = true; freeze=false;
      for(int i=0;i<10;i++)
      {
        delay(100);
        if(freeze);
          break;
        if(!freeze && 9==i)
        {
          //tft.setCursor(160,220); // tft may not like me writing to it while ADC is in girino mode
          //tft.println("hung up");
          Serial.print("hung up");
        }
      }
      //while(!freeze)
      //  delay(100);
      deinitADC();
      scrollindex = 0;
      plotdata();
      plotInformation();
      //tft.begin(ID);
      //tft.setRotation(1); // Landscape
      }
    } else if ( (PLOTTERX + PLOTTERW/3 < tp.x) && ( PLOTTERX + 2*PLOTTERW/3 > tp.x) ) { // ******MIDDLE THIRD******
      //Serial.println("Touch in the middle third...");
      if( PLOTTERY + PLOTTERH/2 > tp.y ) // Top half
      {
        if(COARSEADJUST == leftfunc)
        {
          vcoarseindex++;
          if(9==vcoarseindex)
          {
            vcoarseindex = 0;
            vpower++;
          }
        } else {
          vfineadjust++;
          if(vfineadjust > vcoarsescale[vcoarseindex+1]-vcoarsescale[vcoarseindex])
          {
            vfineadjust = 0;
            vcoarseindex++;
            if(9==vcoarseindex)
            {
              vcoarseindex = 0;
              vpower++;
            }
          }
        }
        MySettings.uVperdiv = pow((long int)10,vpower)*(vcoarsescale[vcoarseindex]+vfineadjust);
        plotVertScale();
        plotdata();
        plotStatusBar();
        //Serial.print("uVperdiv = ");
        //Serial.println(MySettings.uVperdiv);
      } else if ( (PLOTTERY + PLOTTERH/2 < tp.y) && (PLOTTERY + PLOTTERH > tp.y) ) { // Bottom half
        if(COARSEADJUST == leftfunc)
        {
          if(0<vcoarseindex)
          {
            vcoarseindex--;
          } else {
            vcoarseindex = 7;
            vpower--;
          }
        } else {
          if(0==vfineadjust)
          {
            if(0<vcoarseindex)
            {
              vcoarseindex--;
            } else {
              vcoarseindex = 7;
              vpower--;
            }
            vfineadjust = vcoarsescale[vcoarseindex+1]-vcoarsescale[vcoarseindex]+1;
          }
          vfineadjust--;
        }
        MySettings.uVperdiv = pow((long int)10,vpower)*(vcoarsescale[vcoarseindex]+vfineadjust);
        plotVertScale();
        plotdata();
        plotStatusBar();
        //Serial.print("uVperdiv = ");
        //Serial.println(MySettings.uVperdiv);
      }
      //Serial.println("Undefined touch in the middle third");
    } else {                                                                             // ******RIGHT THIRD******
      //Serial.println("Touch in the right third...");
      if( PLOTTERY + PLOTTERH/2 > tp.y ) // Top half
      {
        if(CURSOR==rightfunc)
        {
          restoreplotcolumn();
        }
        rightfunc = (rightfunc+1)%3;
        plotStatusBar();
        if( CURSOR == rightfunc )
        {
          cursorpos = min( ADCBUFFERSIZE, scrollindex + 3*MySettings.usperdiv*1000/dtbuffered_ns );
          storeplotcolumn();
          tft.drawFastVLine(PLOTTERX + index_to_hpixels( scrollindex, cursorpos ),PLOTTERY,PLOTTERH,COLOR_RED);
        }
        plotInformation();
        delay(50); // Not doing a data redraw, so pause a moment to prevent too many responses to touches
      } else if ( (PLOTTERY + PLOTTERH/2 < tp.y) && (PLOTTERY + PLOTTERH > tp.y) ) { // Bottom half
        switch(rightfunc)
        {
          case SCALE:
            MySettings.usperdiv = MySettings.usperdiv*(2+4*leftfunc);
            plotHorizScale();
            plotdata();
            plotStatusBar();
            break;
          case SCROLL:
            scrollindex = min( scrollindex+500*(1+2*leftfunc)*MySettings.usperdiv/dtbuffered_ns, ADCBUFFERSIZE );
            plotHorizScale();
            plotdata();
            plotStatusBar();
            break;
          case CURSOR:
            restoreplotcolumn();
            cursorpos = cursorpos + 1 + 4*leftfunc;
            if(cursorpos>rightmostindex)
              cursorpos = rightmostindex;
            storeplotcolumn();
            tft.drawFastVLine(PLOTTERX + index_to_hpixels( scrollindex, cursorpos ),PLOTTERY,PLOTTERH,COLOR_RED);
            plotInformation();
            delay(25);
            break;
        }
      }
      //Serial.println("Undefined touch in the right third");
    }
    /*
    tft.setTextColor(COLOR_WHITE);
    tft.setTextSize(2);
    tft.fillRect(0,PLOTTERY+PLOTTERH+20, SCREENWIDTH/2, 30, COLOR_BLACK);
    tft.setCursor(2,PLOTTERY+PLOTTERH+20);
    tft.print(MySettings.usperdiv);
    tft.println(" us per div");
    tft.print(MySettings.uVperdiv);
    tft.print(" uV per div");
    //tft.println(tp.z);
    tft.println(scrollindex);*/
    // in practice will need a timeout after a touch

    //delay(1000);
  }
