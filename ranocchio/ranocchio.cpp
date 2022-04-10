//-----------------------------------------------------------------------------
// ranocchio.cpp
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

volatile bool keeprunning;

#include "ranocchio.h"

RanocchioSettings MySettings;

volatile bool redrawinfo=false;

uint8_t vcoarseindex;
uint8_t vfineadjust;
uint8_t vpower;

uint8_t triggermode=0;
uint8_t triggerlevel;
uint16_t triggerindex;
uint8_t triggerstatus;
uint16_t tripletrig;
#warning unused variables
uint16_t triplesum;


uint8_t datamin;
uint8_t datamax;
uint32_t datarms;
uint16_t datadutycyclex1000;
long int dataperiod_us;
long int datafreq_Hzx10;
long int vrange_uV = 5000000;

int XP = 7, YP = A2, XM = A1, YM = 6;
TouchScreen ts(XP, YP, XM, YM, 325); // last argument is ohms measured between D6 and RS
TSPoint tp;                            //global point

/*define ADCBUFFERSIZE 512
  volatile uint8_t ADCBuffer[ADCBUFFERSIZE] = {
   128,  131,  134,  137,  140,  143,  146,  149,
   152,  156,  159,  162,  165,  168,  171,  174,
   176,  179,  182,  185,  188,  191,  193,  196,
   199,  201,  204,  206,  209,  211,  213,  216,
   218,  220,  222,  224,  226,  228,  230,  232,
   234,  236,  237,  239,  240,  242,  243,  245,
   246,  247,  248,  249,  250,  251,  252,  252,
   253,  254,  254,  255,  255,  255,  255,  255,
   255,  255,  255,  255,  255,  255,  254,  254,
   253,  252,  252,  251,  250,  249,  248,  247,
   246,  245,  243,  242,  240,  239,  237,  236,
   234,  232,  230,  228,  226,  224,  222,  220,
   218,  216,  213,  211,  209,  206,  204,  201,
   199,  196,  193,  191,  188,  185,  182,  179,
   176,  174,  171,  168,  165,  162,  159,  156,
   152,  149,  146,  143,  140,  137,  134,  131,
   128,  125,  122,  119,  116,  113,  110,  107,
   104,  100,   97,   94,   91,   88,   85,   82,
    80,   77,   74,   71,   68,   65,   63,   60,
    57,   55,   52,   50,   47,   45,   43,   40,
    38,   36,   34,   32,   30,   28,   26,   24,
    22,   20,   19,   17,   16,   14,   13,   11,
    10,    9,    8,    7,    6,    5,    4,    4,
     3,    2,    2,    1,    1,    1,    1,    1,
     1,    1,    1,    1,    1,    1,    2,    2,
     3,    4,    4,    5,    6,    7,    8,    9,
    10,   11,   13,   14,   16,   17,   19,   20,
    22,   24,   26,   28,   30,   32,   34,   36,
    38,   40,   43,   45,   47,   50,   52,   55,
    57,   60,   63,   65,   68,   71,   74,   77,
    80,   82,   85,   88,   91,   94,   97,  100,
   104,  107,  110,  113,  116,  119,  122,  125,
   128,  131,  134,  137,  140,  143,  146,  149,
   152,  156,  159,  162,  165,  168,  171,  174,
   176,  179,  182,  185,  188,  191,  193,  196,
   199,  201,  204,  206,  209,  211,  213,  216,
   218,  220,  222,  224,  226,  228,  230,  232,
   234,  236,  237,  239,  240,  242,  243,  245,
   246,  247,  248,  249,  250,  251,  252,  252,
   253,  254,  254,  255,  255,  255,  255,  255,
   255,  255,  255,  255,  255,  255,  254,  254,
   253,  252,  252,  251,  250,  249,  248,  247,
   246,  245,  243,  242,  240,  239,  237,  236,
   234,  232,  230,  228,  226,  224,  222,  220,
   218,  216,  213,  211,  209,  206,  204,  201,
   199,  196,  193,  191,  188,  185,  182,  179,
   176,  174,  171,  168,  165,  162,  159,  156,
   152,  149,  146,  143,  140,  137,  134,  131,
   128,  125,  122,  119,  116,  113,  110,  107,
   104,  100,   97,   94,   91,   88,   85,   82,
    80,   77,   74,   71,   68,   65,   63,   60,
    57,   55,   52,   50,   47,   45,   43,   40,
    38,   36,   34,   32,   30,   28,   26,   24,
    22,   20,   19,   17,   16,   14,   13,   11,
    10,    9,    8,    7,    6,    5,    4,    4,
     3,    2,    2,    1,    1,    1,    1,    1,
     1,    1,    1,    1,    1,    1,    2,    2,
     3,    4,    4,    5,    6,    7,    8,    9,
    10,   11,   13,   14,   16,   17,   19,   20,
    22,   24,   26,   28,   30,   32,   34,   36,
    38,   40,   43,   45,   47,   50,   52,   55,
    57,   60,   63,   65,   68,   71,   74,   77,
    80,   82,   85,   88,   91,   94,   97,  100,
   104,  107,  110,  113,  116,  119,  122,  125,
};*/

void plotVertScale()
{ 
  char value[4];
  char sign_units[4] = " uV";
  
  
  tft.fillRect(0,PLOTTERY, SCREENWIDTH-PLOTTERW, PLOTTERH+1, COLOR_BLACK);
  if(NOTRIGGER != triggertype)
  {
    tft.drawFastHLine(0,PLOTTERY + PLOTTERH - counts_to_vpixels(verticalmidpoint,triggerlevel),PLOTTERX,COLOR_BLUE);
  }
  tft.setTextSize(1);
  tft.setTextColor(COLOR_WHITE);

  sprintf(sign_units," uV");
  format3char( verticalmidpoint+MySettings.uVperdiv*2, value, sign_units );
  tft.setCursor(0,PLOTTERY);
  tft.print(value);
  tft.setCursor(0,PLOTTERY+8);
  tft.print(sign_units);

  sprintf(sign_units," uV");
  format3char( verticalmidpoint-MySettings.uVperdiv*2, value, sign_units );
  tft.setCursor(0,PLOTTERY+PLOTTERH-16);
  tft.print(sign_units);
  tft.setCursor(0,PLOTTERY+PLOTTERH-8);
  tft.print(value);
}

void format3char( long int number, char* value, char* sign_units )
{
  if(0>number)
  {
    number = abs(number);
    sign_units[0] = '-';
  } else {
    sign_units[0] = '+';
  }
  
  uint16_t fractpart = 0;
  while(number >= 1000)
  {
    fractpart = number % 1000;
    number = number/1000;
    switch (sign_units[1])
    {
      case 'n':
        sign_units[1] = 'u';
        break;
      case 'u':
        sign_units[1] = 'm';
        break;
      case 'm':
        sign_units[1] = ' ';
        break;
      case ' ':
        sign_units[1] = 'k'; // Should never get this high
        break;
      default:
        sign_units[1] = '?'; // failure to prefix
    }
  }
  fractpart = (fractpart+50)/100; // +50 for rounding
  if( 10 == fractpart )
  {
    number += 1;
    fractpart = 0;
  }

  if( 10 > number )
    sprintf(value,"%ld.%d",number,fractpart);
  else
    sprintf(value,"%ld",number);
}

void plotStatusBar()
{
  long int number;
  char value[4], sign_units[4];
  tft.fillRect(0,0, SCREENWIDTH, PLOTTERY, COLOR_BLACK);
  tft.setTextColor(COLOR_WHITE);
  tft.setTextSize(1);

  tft.setCursor(0,0);
  switch(leftfunc)
  {
    case COARSEADJUST:
      tft.print("[COARSE]");
      break;
    case FINEADJUST:
      tft.print("[FINE]");
      break;
  }
  
  tft.setCursor(75, 0);
  number = MySettings.usperdiv;
  strcpy(sign_units,"+us");
  format3char(number,value,sign_units);
  tft.print(value);
  tft.print(sign_units[1]); tft.print(sign_units[2]);
  tft.print("/div");

  tft.setCursor(150, 0);
  number = MySettings.uVperdiv;
  strcpy(sign_units,"+uV");
  format3char(number,value,sign_units);
  tft.print(value);
  tft.print(sign_units[1]); tft.print(sign_units[2]);
  tft.print("/div");

  switch(triggertype)
  {
    case RISINGEDGE:
      tft.drawFastHLine(226,8,7,COLOR_WHITE);
      tft.drawFastVLine(232,0,8,COLOR_WHITE);
      tft.drawFastHLine(233,0,7,COLOR_WHITE);
      break;
    case FALLINGEDGE:
      tft.drawFastHLine(226,0,7,COLOR_WHITE);
      tft.drawFastVLine(232,0,8,COLOR_WHITE);
      tft.drawFastHLine(233,8,7,COLOR_WHITE);
      break;
    case NOTRIGGER:
      tft.setCursor(226,0);
      tft.print("TR");
      tft.drawLine(227,0,236,5,COLOR_RED);
      tft.drawLine(227,1,236,6,COLOR_RED);
      break;
  }
  tft.setCursor(237,0);
  switch(triggermode)
  {
    case NORMAL:
      tft.print("Con");
      break;
    case SINGLE:
      tft.print("Sin");
      break;
  }
  

  tft.setCursor(270,0);
  switch(rightfunc)
  {
    case SCALE:
      tft.print(" [SCALE]");
      break;
    case SCROLL:
      tft.print("[SCROLL]");
      break;
    case CURSOR:
      tft.print("[CURSOR]");
      break;
    case TRIGGER:
      tft.print("[TRIGGR]");
      break;
    default:
      tft.print("[???]");
      
  }
}

void plotHorizScale()
{
  tft.fillRect(0,PLOTTERY+PLOTTERH+1, SCREENWIDTH, 15, COLOR_BLACK);
  tft.setTextSize(1);
  tft.setTextColor(COLOR_WHITE);

  // Show trigger time, if applicable
  if( triggerindex > ADCCounter )
    tft.drawFastVLine(PLOTTERX+index_to_hpixels(scrollindex,triggerindex-ADCCounter),PLOTTERY+PLOTTERH+1,7,COLOR_RED);
  else
    tft.drawFastVLine(PLOTTERX+index_to_hpixels(scrollindex,(ADCBUFFERSIZE+triggerindex-ADCCounter)%ADCBUFFERSIZE),PLOTTERY+PLOTTERH+1,7,COLOR_RED);
   
  // Leftmost label
  long int number = scrollindex*dtbuffered_ns;
  char value[8], sign_units[8];
  strcpy(sign_units,"+ns");
  format3char( number, value, sign_units );
  tft.setCursor(PLOTTERX,PLOTTERY+PLOTTERH+1);
  tft.print(value);
  tft.print(sign_units[1]); tft.print(sign_units[2]); // don't use the leading char for purely positive quantities

  number = scrollindex*dtbuffered_ns + PLOTTERW/XDIVPIXELS*MySettings.usperdiv*500;
  strcpy(sign_units,"+ns");
  format3char( number, value, sign_units);
  tft.setCursor(PLOTTERX+PLOTTERW/2-12,PLOTTERY+PLOTTERH+1);
  tft.print(value);
  tft.print(sign_units[1]); tft.print(sign_units[2]);

  number = scrollindex*dtbuffered_ns + PLOTTERW/XDIVPIXELS*MySettings.usperdiv*1000;
  strcpy(sign_units,"+ns");
  format3char( number, value, sign_units);
  tft.setCursor(PLOTTERX+PLOTTERW-30,PLOTTERY+PLOTTERH+1);
  tft.print(value);
  tft.print(sign_units[1]); tft.print(sign_units[2]);
}

void plotInformation()
{
  tft.fillRect(0, PLOTTERY+PLOTTERH+16, SCREENWIDTH, SCREENHEIGHT-PLOTTERY-PLOTTERH-16, COLOR_BLACK);
  tft.setTextColor(COLOR_WHITE);
  tft.setTextSize(1);
  
  tft.setCursor(0,SCREENHEIGHT-10);
  tft.print(F("[RUN "));
  tft.print(MySettings.currentrange_mV/1000);
  tft.print(F(" Vp]"));
  //tft.print(tp.z);                                                                             

  tft.setCursor(SCREENWIDTH/2-20,SCREENHEIGHT-10);
  tft.print(F("[SETTINGS]"));

  tft.setCursor(SCREENWIDTH-40,SCREENHEIGHT-10);
  tft.print(F("[HOME]"));

  tft.setTextSize(2);
  
  long int dat;

  char str[45];
  
  switch(rightfunc)
  {
    case SCALE:
    case SCROLL: // breakthrough
      // This is where statistics like Vpp, Vrms, Freq can go
      analyzeData();
      tft.setTextColor(COLOR_WHITE);
      tft.setCursor(0,PLOTTERY+PLOTTERH+16);
      
      if(MySettings.displayrms)
      {
        dat = (datarms*vresbuffered_uV)/1000;
        if(dat>1000)
          sprintf(str, "RMS=%ld.%02ldV ", dat/1000, (dat%1000)/10);
        else
          sprintf(str, "RMS=%ldmV ", dat);
      } else {
        dat = ((datamax-datamin)*vresbuffered_uV)/1000;
        if(dat>1000)
          sprintf(str, "P-P=%ld.%02ldV ", dat/1000, (dat%1000)/10);
        else
          sprintf(str, "P-P=%ldmV ", dat);
      }
      tft.print(str);
      if(datafreq_Hzx10 < 0)
        sprintf(str, "f=??? ");
      else if(datafreq_Hzx10 < 1000 )
        sprintf(str, "f=%ld.%ldHz ", datafreq_Hzx10/10, datafreq_Hzx10%10);
      else if (datafreq_Hzx10 > 0)
        sprintf(str, "f=%ldHz ", datafreq_Hzx10/10);
        
      tft.print(str);

      if( datadutycyclex1000 > 1000)
        sprintf(str, "d%%=???");
      else
        sprintf(str, "d%%=%u.%u", datadutycyclex1000/10, datadutycyclex1000%10);
      tft.print(str);
        /*
      if(datafreq_Hzx10 < 1000 )
        sprintf(str, "Vpp=%lumV,f=%ld.%ldHz,d%%=%u", ((datamax-datamin)*vresbuffered_uV)/1000, datafreq_Hzx10/10, datafreq_Hzx10%10, datadutycyclex1000/10);
      else
        sprintf(str, "Vpp=%lumV,f=%ldHz,d%%=%u", ((datamax-datamin)*vresbuffered_uV)/1000, datafreq_Hzx10/10, datadutycyclex1000/10);
      #warning duty cycle seems to be off by 10x*/
      
      break;
    case CURSOR:
      tft.setTextColor(COLOR_RED);
      tft.setCursor(0,PLOTTERY+PLOTTERH+16);
      sprintf(str, "%ldus, %ldmV", cursorpos*dtbuffered_ns/1000, ((long int)(ADCBuffer[(ADCCounter+cursorpos)%ADCBUFFERSIZE])-128)*(long int)vresbuffered_uV/1000);
      tft.print(str);
      break;
  }
}

void plotDigitalInformation()
{
  tft.fillRect(0, PLOTTERY+PLOTTERH+16, SCREENWIDTH, SCREENHEIGHT-PLOTTERY-PLOTTERH-16, COLOR_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(COLOR_WHITE);
  long int dat;

  char str[45];
  
  switch(rightfunc)
  {
    case SCALE:
    case SCROLL: // breakthrough
      // This is where statistics like duty cycle and frequency can go
      break;
    case CURSOR:
      tft.setTextColor(COLOR_RED);
      tft.setCursor(0,PLOTTERY+PLOTTERH+16);
      sprintf(str, "%ldus: 0x%02x", cursorpos*dtbuffered_ns/1000, ADCBuffer[(ADCCounter+cursorpos)%ADCBUFFERSIZE]);
      tft.print(str);
      break;
  }
}

void storeplotcolumn()
{
  pixelsx = PLOTTERX + index_to_hpixels( scrollindex, cursorpos );
  tft.readGRAM( pixelsx, PLOTTERY, pixels, 1, PLOTTERH);
}

void storeplotrow()
{
  pixelsx = PLOTTERY + PLOTTERH - counts_to_vpixels( verticalmidpoint, triggerlevel); // y coordinate
  tft.readGRAM( PLOTTERX, pixelsx, pixels, PLOTTERW, 1);
}

void restoreplotcolumn()
{
  tft.setAddrWindow( pixelsx, PLOTTERY, pixelsx, PLOTTERY+PLOTTERH-1 );
  tft.pushColors(pixels, PLOTTERH, true);
  tft.setAddrWindow(0, 0, tft.width() - 1, tft.height() - 1);
  /*for(int i = 0; i<PLOTTERH; i++)
  {
    tft.drawPixel(cursorpos, PLOTTERY+i, pixels[i]);
  }*/
}

void restoreplotrow()
{
  tft.setAddrWindow( PLOTTERX, pixelsx, PLOTTERX+PLOTTERW, pixelsx);
  tft.pushColors(pixels,PLOTTERW, true);
  tft.setAddrWindow(PLOTTERX, 0, tft.width() - 1, tft.height() - 1);
}

void plotanalogdata()
{
  // Plot the grid
  //tft.fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
  tft.fillRect(PLOTTERX, PLOTTERY, PLOTTERW, PLOTTERH, COLOR_BLACK);
  for( int i = 0; i<=PLOTTERW; i=i+XDIVPIXELS) tft.drawFastVLine(i+PLOTTERX,PLOTTERY,PLOTTERH,COLOR_DARKERGREY);
  for( int i = 0; i<=PLOTTERH; i=i+YDIVPIXELS) tft.drawFastHLine(PLOTTERX,i+PLOTTERY,PLOTTERW,COLOR_DARKERGREY);

  // Plot the data
  int y0 = PLOTTERY + PLOTTERH - counts_to_vpixels(verticalmidpoint, ADCBuffer[(ADCCounter+scrollindex)%ADCBUFFERSIZE]);
  //Serial.print("Data starts here\n");
  //Serial.println(ADCBuffer[ADCCounter+waitDuration]);
  int y1;
  int x0 = PLOTTERX;
  int x1;
  rightmostindex = scrollindex;
  for (int i = scrollindex; i<ADCBUFFERSIZE; i++)
  {
    x1 = PLOTTERX + index_to_hpixels( scrollindex, i ); //map(i,0,ADCBUFFERSIZE,PLOTTERX,PLOTTERX+PLOTTERW);
    y1 = PLOTTERY + PLOTTERH - counts_to_vpixels(verticalmidpoint, ADCBuffer[(ADCCounter+i)%ADCBUFFERSIZE]);
    if( x1 > PLOTTERX + PLOTTERW )
    {
      break;
    }
    rightmostindex = i;
    if( y1 > PLOTTERY+PLOTTERH || y1 < PLOTTERY )
    {
      y1 = constrain(y1,PLOTTERY,PLOTTERY+PLOTTERH);
      tft.drawLine(x0, y0, x1, y1, COLOR_DARKERGREEN); 
    } else {
      //Serial.println(ADCBuffer[(ADCCounter+i)%ADCBUFFERSIZE]);
      tft.drawLine(x0, y0, x1, y1, COLOR_GREENYELLOW);  
    }
    y0 = y1;
    x0 = x1;
  }
  //Serial.print("Done drawing.\n");
}

int index_to_hpixels( int start, int i )
{
  // To try to minimize rounding error, this calculates based on two screens of scroll.
  return map(i,start,start+(2000*(uint32_t)PLOTTERW / XDIVPIXELS)*MySettings.usperdiv/dtbuffered_ns,0,2*PLOTTERW);
}

int counts_to_vpixels( long int midpt, int i)
{
  //Serial.print("counts_to_vpixels called with midpoint = "); Serial.println(midpt);
  if(  100000 > vresbuffered_uV ) // do the math in microvolts
    return map(((long int)i-128)*vresbuffered_uV,midpt-((int32_t)PLOTTERH / YDIVPIXELS)*MySettings.uVperdiv/2,  midpt+((int32_t)PLOTTERH / YDIVPIXELS)*MySettings.uVperdiv/2, 0, PLOTTERH);
  else // do the math in millivolts
    return map(((long int)i-128)*(vresbuffered_uV/1000),midpt/1000-((int32_t)PLOTTERH / YDIVPIXELS)*(MySettings.uVperdiv/2000),  midpt/1000+((int32_t)PLOTTERH / YDIVPIXELS)*(MySettings.uVperdiv/2000), 0, PLOTTERH);
}

void scopeSettings()
{
  bool returntomain = false;
  while(!returntomain)
  {
    // Draw menu
    tft.fillScreen(COLOR_BLACK);
    tft.setTextColor(COLOR_WHITE);
    tft.drawFastHLine(0,SCREENHEIGHT/3,SCREENWIDTH,COLOR_WHITE);
    tft.drawFastHLine(0,2*SCREENHEIGHT/3,SCREENWIDTH,COLOR_WHITE);
    tft.drawFastVLine(SCREENWIDTH/2,0,SCREENHEIGHT,COLOR_WHITE);
    int pageno = 0;
  
    tft.setTextSize(2);
    
    tft.setCursor(5,5);
    tft.print("Return");
    tft.setCursor(5+SCREENWIDTH/2,5);
    tft.print("V display: ");
    tft.setCursor(5+SCREENWIDTH/2,20);
    if(MySettings.displayrms)
      tft.print("RMS");
    else
      tft.print("P-P");
  
    tft.setCursor(5,5+SCREENHEIGHT/3);
    tft.print(F("Auto Scale"));

    tft.setCursor(5+SCREENWIDTH/2,5+SCREENHEIGHT/3);
    tft.print(F("Save to SD"));

    tft.setCursor(5, 5 + 2*SCREENHEIGHT/3);
    tft.println(F("Sample Rate:"));
    tft.print(16000/MySettings.ADCprescaler/13);
    tft.print(F(" kS/s"));

    tft.setCursor(5 + SCREENWIDTH/2, 5 + 2*SCREENHEIGHT/3);
    tft.print("FFT");

    tp.z = 0;
    while(MINPRESSURE>tp.z || MAXPRESSURE<tp.z)
      readResistiveTouch();

    if( tp.x < SCREENWIDTH/2 ) // ***  Left column ***
    {
      if( tp.y < SCREENHEIGHT/3 ) // Top
      {
        // Return
        returntomain = true;
      } else if (tp.y < 2*SCREENHEIGHT/3) { // Middle
        // Auto scale
        scrollindex = 0;
        rightmostindex = waitDuration;
        analyzeData(true);
        returntomain = true;
      } else { // Bottom
        // Adjust sample rate
        MySettings.ADCprescaler = 2*MySettings.ADCprescaler;
        if(32 < MySettings.ADCprescaler)
          MySettings.ADCprescaler = 4;
      }
    } else { //                   *** Right column ***
      if( tp.y < SCREENHEIGHT/3 ) // Top
      {
        // Toggle between RMS and P-P voltage display in the info bar
        MySettings.displayrms = !(MySettings.displayrms);
      } else if ( tp.y < 2*SCREENHEIGHT/3) { // Middle
        // Save data (or screenshot) to SD Card
        saveBufferToSd(); // Gives options for data file, bmp screenshot, or both
      } else {
        // Frequency analysis
        fftsubmode();
      }
    }
  }
}

/*
int powerToMilliDB(int num)
{
  return 20000*log10(sqrt((float)num));
}*/

void fftsubmode()
{
  tft.fillScreen(COLOR_BLACK);
  
  // Resample to 256 points
  #define FFTSIZE 256
  uint8_t fundindex = 2; // third index, assuming two complete cycles appeared in the on-screen interval
  int8_t data[FFTSIZE], im[FFTSIZE];
  int d = rightmostindex - scrollindex;
  float fsam = 1000000000.0/((float)d*dtbuffered_ns/FFTSIZE);
  int n;
  long int mysum = 0;
  bool returntomain = false;
  //Serial.println(F("Downsample:"));
  //Serial.print(F("d = "));Serial.println(d);
  for(int i=0;i<FFTSIZE;i++)
  {
       mysum = 0;
       n=0;
       /*
       for(int j = 0; j<d/FFTSIZE; j++)
       {
         mysum += (long int)(ADCBuffer[(scrollindex+map(i,0,FFTSIZE-1,0,d)+j)%ADCBUFFERSIZE]);
         n++;
       }
       data[i] = (mysum/n - 128); // Might be better to subtract mean rather than 128 */
       data[i] = (long int)(ADCBuffer[(scrollindex+map(i,0,FFTSIZE-1,0,d))%ADCBUFFERSIZE]);
       im[i] = 0;
  }
  fix_fft(data, im, 8, 0);
  
  int* pwr = (int*)(&(data[0]));

  for(int i=0; i<FFTSIZE/2; i++)
    pwr[(i+FFTSIZE/4)%(FFTSIZE/2)] = (int)data[i]*data[i] + (int)im[i]*im[i];

  for(int i=1; i<FFTSIZE/2; i++)
    {
      // TODO: Would it be better to plot sqrt(pwr), possibly converted to dB?
      tft.drawLine(map(i-1,0,FFTSIZE/2,0,SCREENWIDTH),SCREENHEIGHT - 25 - map(pwr[(i-1+FFTSIZE/4)%(FFTSIZE/2)],0,1024,0,SCREENHEIGHT-25),map(i,0,FFTSIZE/2,0,SCREENWIDTH),SCREENHEIGHT -25 - map(pwr[(i+FFTSIZE/4)%(FFTSIZE/2)],0,1024,0,SCREENHEIGHT-25),COLOR_GREENYELLOW);
      //tft.drawLine(map(i-1,0,FFTSIZE/2,0,SCREENWIDTH),SCREENHEIGHT - 25 - map(powerToMilliDB(pwr[(i-1+FFTSIZE/4)%(FFTSIZE/2)]),-60000,60000,0,SCREENHEIGHT-25),map(i,0,FFTSIZE/2,0,SCREENWIDTH),SCREENHEIGHT -25 - map(powerToMilliDB(pwr[(i+FFTSIZE/4)%(FFTSIZE/2)]),-60000,60000,0,SCREENHEIGHT-25),COLOR_GREENYELLOW);
    }
  
  //Serial.print("mysum = "); Serial.print(mysum); Serial.print(", principal = ");Serial.println(pwr[(2+FFTSIZE/4)%(FFTSIZE/2)] );
  int thdx10;
  pixelsx = map(fundindex,0,FFTSIZE-1,0,SCREENWIDTH);
  tft.readGRAM( pixelsx, 0, pixels, 1, SCREENHEIGHT-25);
  while(!returntomain)
  {
    mysum = 0;
    for(int i=fundindex+1; i<FFTSIZE/2; i++)
    {
      if( 0 == (i%fundindex) ) // harmonics only
        mysum += pwr[(i+FFTSIZE/4)%(FFTSIZE/2)];
      //Serial.println(pwr[(i+FFTSIZE/4)%(FFTSIZE/2)]);
    }

    tft.setAddrWindow( pixelsx, 0, pixelsx, SCREENHEIGHT-25 );
    tft.pushColors(pixels, SCREENHEIGHT-25, true);
    tft.setAddrWindow(0, 0, tft.width() - 1, tft.height() - 1);
    pixelsx = map(fundindex,0,FFTSIZE-1,0,SCREENWIDTH);
    tft.readGRAM( pixelsx, 0, pixels, 1, SCREENHEIGHT-25);
    tft.drawFastVLine( pixelsx,0,SCREENHEIGHT-25,COLOR_RED);

    thdx10 = (int)sqrt( 1000000*mysum / pwr[(fundindex+FFTSIZE/4)%(FFTSIZE/2)] );
    tft.fillRect(0,SCREENHEIGHT-24,SCREENWIDTH,SCREENHEIGHT,COLOR_BLACK);
    tft.setCursor(0,SCREENHEIGHT-23);
    tft.setTextSize(2);
    tft.setTextColor(COLOR_WHITE);
    tft.print(F("FUND ")); tft.print(fundindex*fsam/FFTSIZE); //tft.print('.'); tft.print((fundindex*fsamx10)%10);
    tft.print(F("Hz:THD+N=")); tft.print(thdx10/10); tft.print('.'); tft.print(thdx10%10); tft.print('%');
    returntomain = false;
    
    tp.z = 0;
    while(MINPRESSURE>tp.z || MAXPRESSURE<tp.z)
      readResistiveTouch();
    if( tp.y < SCREENHEIGHT-25 ) // *** TOP PART ***
    {
      if( tp.x < SCREENWIDTH/2 ) // Left side
      {
        //if(fundindex>0) // Just let it wrap around
          fundindex--;
      } else { // Right side
        //if(255>fundindex) // Just let it wrap around
          fundindex++;
      }
    } else {                     // *** BOTTOM PART ***
      returntomain = true;
    }
    delay(200);
  }
}

void datapixel(int index, int color)
{
  // Redraw the pixel as a yellow green dot
  int x = PLOTTERX + index_to_hpixels( scrollindex, index ); //map(i,0,ADCBUFFERSIZE,PLOTTERX,PLOTTERX+PLOTTERW);
  int y = PLOTTERY + PLOTTERH - counts_to_vpixels(verticalmidpoint, ADCBuffer[(ADCCounter+index)%ADCBUFFERSIZE]);
  tft.drawPixel(x,y,color);
}

// based on similar function from MCU_Friend example TouchScreen_Calibr_native
void readResistiveTouch(void)
{
    tp = ts.getPoint();
   /* if( MINPRESSURE < tp.z && MAXPRESSURE>tp.z )
  {
    Serial.print("tp.x = ");
    Serial.print(tp.x);
    Serial.print(", tp.y = ");
    Serial.print(tp.y);
    Serial.print(", tp.z = ");
    Serial.println(tp.z);
  }*/

    mappoints(&tp);
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);

    // https://forum.arduino.cc/t/touchscreen-and-tft-sharing-uno-pins-help-needed/218910/3
    /*pinMode(XM, OUTPUT);
    digitalWrite(XM, LOW);
    pinMode(YP, OUTPUT);
    digitalWrite(YP, HIGH);*/

    //digitalWrite(YP, HIGH);  //because TFT control pins
    //digitalWrite(XM, HIGH);
    //    Serial.println("tp.x=" + String(tp.x) + ", tp.y=" + String(tp.y) + ", tp.z =" + String(tp.z));
}

void mappoints( TSPoint* tp )
{
  //int x = tp->x;
  /*tp->x = map(tp->x, 180, 930, 0, 320);
  tp->y = map(tp->y, 180, 918, 0, 240);*/
  
  /*//PORTRAIT  CALIBRATION     240 x 320
  x = map(p.x, LEFT=138, RT=909, 0, 240)
  y = map(p.y, TOP=935, BOT=146, 0, 320)*/
  
  //LANDSCAPE CALIBRATION     320 x 240
  int x = map(tp->x, 146, 935, 0, 320);
  int y = map(tp->y, 138, 909, 0, 240);
  tp->x = x;
  tp->y = y;

  //PORTRAIT  CALIBRATION     240 x 320
  /*
  x = map(p.x, LEFT=181, RT=918, 0, 240)
  y = map(p.y, TOP=938, BOT=184, 0, 320)*/

/*
  if( MINPRESSURE < tp->z && MAXPRESSURE>tp->z )
  {
    Serial.print("tp.x = ");
    Serial.print(tp->x);
    Serial.print(", tp.y = ");
    Serial.print(tp->y);
    Serial.print(", tp.z = ");
    Serial.println(tp->z);
  }*/
}

void mainMenu()
{
  tft.setTextSize(3);

  //TODO would be nice to come up with proper icons
  tft.fillRect(0,0, SCREENWIDTH/2, SCREENHEIGHT/2, COLOR_RED);
  tft.setCursor(30,SCREENHEIGHT/6);
  tft.setTextColor(COLOR_WHITE);
  tft.print(F("SCOPE"));
  tft.fillRect(SCREENWIDTH/2,0, SCREENWIDTH/2, SCREENHEIGHT/2, COLOR_GREEN);
  tft.setCursor(SCREENWIDTH/2+30,SCREENHEIGHT/6);
  tft.setTextColor(COLOR_BLACK);
  tft.print(F("METER"));
  tft.fillRect(0,SCREENHEIGHT/2, SCREENWIDTH/2, SCREENHEIGHT/2, COLOR_BLUE);
  tft.setCursor(30,SCREENHEIGHT/2+SCREENHEIGHT/6);
  tft.setTextColor(COLOR_WHITE);
  tft.print(F("LOGIC"));
  tft.fillRect(SCREENWIDTH/2,SCREENHEIGHT/2, SCREENWIDTH/2, SCREENHEIGHT/2, COLOR_BLACK);
  /*tft.setCursor(SCREENWIDTH/2+20, SCREENEIGHT/2+SCREENHEIGHT/6);
  tft.print("Future?");*/

  tp.z = 0;
  while(MINPRESSURE>tp.z || MAXPRESSURE<tp.z)
    readResistiveTouch();

  if( (SCREENWIDTH/2) > tp.x )                                   // ******LEFT HALF******
  {
    if( SCREENHEIGHT/2 > tp.y ) // TOP HALF
    {
      scopeMode();
    } else { // BOTTOM HALF
      logicMode();
    }
  } else {                                                             // ******RIGHT HALF******
    if( SCREENHEIGHT/2 > tp.y ) // TOP HALF
    {
      meterMode();
    } else { // BOTTOM HALF
      // Nothing yet
    }
  }
}

void meterMode()
{
  bool returntomain = false;
  int counter = 0;
  int value;
  int lastvalue=0;
  long int vres2_uV = vrange_uV/2048; // half the actual resolution because I'm double sampling
  char str[8];
  bool signbit = false;

  tp.z = 0;
  
  sbi(ADCSRA,ADPS2);
  sbi(ADCSRA,ADPS1);
  sbi(ADCSRA,ADPS0);
  //cbi(ADMUX,ADLAR);
  dtbuffered_ns = 9615;

  tft.fillScreen(COLOR_BLACK);
  tft.setTextSize(4);

  while(!returntomain)
  {
    // Read pin
    value = analogRead(ADCPIN); // This is the slow way of doing it, but we don't need to be fast here
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);

    // Update plot
    tft.fillRect(counter,SCREENHEIGHT-64,3,64,COLOR_BLACK);
    tft.drawLine(max(counter-1,0), SCREENHEIGHT-1-(lastvalue>>4), counter, SCREENHEIGHT-1-(value>>4), COLOR_GREENYELLOW);
    lastvalue = value;

    if(0==(counter%(SCREENWIDTH/2)))
    {
      // Update digits
      tft.fillRect(0,40,SCREENWIDTH,90,COLOR_BLACK);
      tft.setCursor(40,50);
      value = (value+lastvalue-1024)*vres2_uV/1000;
      signbit = (0<value);
      value = abs(value);
      sprintf(str,"%c%04d.%03d",(signbit?' ':'-'),value/1000,value%1000);
      tft.println(str);
    } else {
      delay(10);
    }

    readResistiveTouch();
    if(MINPRESSURE<tp.z && MAXPRESSURE>tp.z)
      returntomain = true;
    
    counter = (counter+1)%SCREENWIDTH;
  }
}

void scopeMode()
{
  bool returntomain = false;
  int num;

  plotVertScale();
  plotHorizScale();
  plotStatusBar();
  plotanalogdata();
  plotInformation();
  
  while(!returntomain)
  {
    //deinitADC(); // SHOULDN'T BE NECESSARY??
    //delay(10);
    tp.z = 0;
    while(MINPRESSURE>tp.z || MAXPRESSURE<tp.z)
    {
      if(redrawinfo)
      {
        //delay(10);
        redrawinfo=false;
        updateCurrentRange();
        plotInformation();
      }
      readResistiveTouch();
    }
  
    if( (PLOTTERX+PLOTTERW/3) > tp.x )                                                   // ******LEFT THIRD******
    {
      //Serial.println("Touch in the left third...");
      if( PLOTTERY + PLOTTERH/2 > tp.y ) // Top half of plot region
      {
        leftfunc = (leftfunc+1)%2;
        plotStatusBar();
        delay(200);
      } else if ( (PLOTTERY + PLOTTERH/2 < tp.y) && (PLOTTERY + PLOTTERH > tp.y) ) { // Bottom half of plot region
        switch(rightfunc)
        {
          case SCALE:
            num = MySettings.usperdiv - (MySettings.usperdiv>=10000?1000:100)*(1+3*leftfunc);
            if(num<50)
              MySettings.usperdiv = 50;
            else
              MySettings.usperdiv = num;
            plotanalogdata();
            plotHorizScale();
            plotStatusBar();
            break;
          case SCROLL:
            num = (scrollindex-(int)500*(1+2*leftfunc)*MySettings.usperdiv/dtbuffered_ns);
            if(num>0)
              scrollindex = num;
            else
              scrollindex = 0;
            plotanalogdata();
            plotHorizScale();
            plotStatusBar();
            break;
          case CURSOR:
            restoreplotcolumn();
            cursorpos = cursorpos - 1 - 4*leftfunc;
            if(cursorpos<scrollindex)
              cursorpos = scrollindex;
            storeplotcolumn();
            tft.drawFastVLine(PLOTTERX + index_to_hpixels( scrollindex, cursorpos ),PLOTTERY,PLOTTERH,COLOR_RED);
            datapixel(cursorpos,COLOR_GREENYELLOW); // redraw the data pixel
            plotInformation();
            delay(25);
            break;
          case TRIGGER:
            triggertype = (triggertype+1)%NUMTTYPES;
            plotStatusBar();
            delay(100);
            break;
        }
      } else if ( PLOTTERY+PLOTTERH < tp.y) { // Very bottom of screen
        // TODO: Move most of this to a separate function. Maybe saving the stack will take less time in a smaller chunk?
        tft.fillRect(0,PLOTTERY+PLOTTERH+1,SCREENWIDTH,SCREENHEIGHT-PLOTTERY-PLOTTERH,COLOR_BLACK);
        tft.setCursor(10,PLOTTERY+PLOTTERH+2);
        tft.setTextSize(2);
        tft.print(F("Running..."));
        tft.setCursor(0,SCREENHEIGHT-10); tft.setTextSize(1);
        if( SINGLE == triggermode )
          tft.print(F("[Change range to abort]"));
        else
          tft.print(F("[Long press to stop; Change range to abort]"));
        keeprunning = true;
        do
        {
          runScope();
          plotanalogdata();
      
          tp.z = 0;
          readResistiveTouch();
          if( MINPRESSURE<tp.z && MAXPRESSURE>tp.z)
          {
            tft.fillRect(0,PLOTTERY+PLOTTERH+1,SCREENWIDTH,SCREENHEIGHT-PLOTTERY-PLOTTERH,COLOR_BLACK);
            tft.setCursor(50,PLOTTERY+PLOTTERH+5);
            tft.setTextSize(2);
            tft.print(F("STOP"));
            delay(300);
            break;
          }
        } while (SINGLE != triggermode);
        plotHorizScale();
        plotInformation();
        }
      } else if ( (PLOTTERX + PLOTTERW/3 < tp.x) && ( PLOTTERX + 2*PLOTTERW/3 > tp.x) ) { // ******MIDDLE THIRD******
        //Serial.println("Touch in the middle third...");
        if( PLOTTERY + PLOTTERH/2 > tp.y ) // Top half
        {
          switch(rightfunc)
          {
            case SCALE:
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
              plotanalogdata();
              analyzeData();
              plotStatusBar();
              plotVertScale();
              //Serial.print("uVperdiv = ");
              //Serial.println(MySettings.uVperdiv);
              break;
            case SCROLL:
              verticalmidpoint = verticalmidpoint + MySettings.uVperdiv/(COARSEADJUST==leftfunc?1:5);
              Serial.print(F("verticalmidpoint = ")); Serial.println(verticalmidpoint);
              plotanalogdata();
              plotVertScale();
              break;
            case TRIGGER:
              restoreplotrow();
              if(255>triggerlevel)
                triggerlevel++;
              analogWrite(44,triggerlevel);
              storeplotrow();
              tft.drawFastHLine(PLOTTERX,PLOTTERY+PLOTTERH-counts_to_vpixels(verticalmidpoint,triggerlevel),PLOTTERW,COLOR_BLUE);
              break;
          }
        } else if ( (PLOTTERY + PLOTTERH/2 < tp.y) && (PLOTTERY + PLOTTERH > tp.y) ) { // Bottom half
          switch(rightfunc)
          {
            case SCALE:
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
              plotanalogdata();
              plotStatusBar();
              plotVertScale();
              break;
            case SCROLL:
              verticalmidpoint = verticalmidpoint - MySettings.uVperdiv/(COARSEADJUST==leftfunc?1:5);
              //Serial.print(F("verticalmidpoint = ")); Serial.println(verticalmidpoint);
              plotanalogdata();
              plotVertScale();
              break;
            case TRIGGER:
              restoreplotrow();
              if(0<triggerlevel)
                triggerlevel--;
              analogWrite(44,triggerlevel);
              storeplotrow();
              tft.drawFastHLine(PLOTTERX,PLOTTERY+PLOTTERH-counts_to_vpixels(verticalmidpoint,triggerlevel),PLOTTERW,COLOR_BLUE);
              break;
          }
        } else if ( PLOTTERY+PLOTTERH < tp.y) { // Very bottom of screen
          scopeSettings();
          plotanalogdata();
          plotStatusBar();
          plotVertScale();
          plotHorizScale();
          plotInformation();
        }
        //Serial.println("Undefined touch in the middle third");
      } else {                                                                             // ******RIGHT THIRD******
        //Serial.println("Touch in the right third...");
        if( PLOTTERY + PLOTTERH/2 > tp.y ) // Top half
        {
          if(CURSOR==rightfunc)
          {
            restoreplotcolumn();
          } else if (TRIGGER == rightfunc) {
            restoreplotrow();
            plotVertScale();
          }
          rightfunc = (rightfunc+1)%NUMRFUNCS;
          plotStatusBar();
          if( CURSOR == rightfunc )
          {
            cursorpos = min( ADCBUFFERSIZE, scrollindex + 3*MySettings.usperdiv*1000/dtbuffered_ns );
            storeplotcolumn();
            tft.drawFastVLine(PLOTTERX + index_to_hpixels( scrollindex, cursorpos ),PLOTTERY,PLOTTERH,COLOR_RED);
          } else if ( TRIGGER == rightfunc ) {
            storeplotrow();
            tft.drawFastHLine(PLOTTERX,PLOTTERY+PLOTTERH-counts_to_vpixels(verticalmidpoint,triggerlevel),PLOTTERW,COLOR_BLUE);
          }
          plotInformation();
          delay(50); // Not doing a data redraw, so pause a moment to prevent too many responses to touches
        } else if ( (PLOTTERY + PLOTTERH/2 < tp.y) && (PLOTTERY + PLOTTERH > tp.y) ) { // Bottom half
          switch(rightfunc)
          {
            case SCALE:
              MySettings.usperdiv = min( MySettings.usperdiv + (MySettings.usperdiv>=10000?1000:100)*(1+3*leftfunc), 1000000);
              plotHorizScale();
              plotanalogdata();
              plotStatusBar();
              break;
            case SCROLL:
              scrollindex = min( scrollindex+500*(1+2*leftfunc)*MySettings.usperdiv/dtbuffered_ns, ADCBUFFERSIZE );
              plotHorizScale();
              plotanalogdata();
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
            case TRIGGER:
              triggermode = (triggermode+1)%2;
              plotStatusBar();
              delay(100);
              break;
          }
        } else if ( PLOTTERY+PLOTTERH < tp.y) {
          returntomain = true;
        }
      }
  }
}

void runScope()
{
  #warning I think I may need to do away with ISR(ADC_vect) and just calibrate a loop here so we do not miss anything

  memset( (void *)ADCBuffer, 0, sizeof(ADCBuffer) ); // clear buffer
  vresbuffered_uV = MySettings.currentrange_mV*1000/128;
  initADC();
  ADCCounter=0;
  
  bool currentstate;
  bool lookfor;
  uint8_t trigger;
  if(NOTRIGGER == triggertype)
  {
    //trigger = 4; // triggered
    trigger = 0;
    stopIndex = ADCCounter; // fill the whole buffer
  } else {
    //trigger = 0; // initializing
    trigger = 4;
    stopIndex = ADCBUFFERSIZE+1; // will never reach this, but will update when triggered
  }
  
  switch(triggertype)
  {
    case RISINGEDGE:
      lookfor = false;
      break;
    case FALLINGEDGE:
      lookfor = true;
      break;
  }

  keeprunning = true;

  TIMSK0 = 0; // turn off timer0 for lower jitter - delay() and millis() killed
  startADC();
  if( MySettings.ADCprescaler < 8 ) // Can't spare the processor cycles to collect timely data before trigger
  {
    while(true)
    {
      while( !(ADCSRA&(1<<ADIF)) )
        if(!keeprunning) break; // Wait for new sample or indication to stop running
      ADCBuffer[ADCCounter] = ADCH; // Grab sample
      sbi(ADCSRA,ADIF); // Reset ADIF
      if(trigger)
      {
        if(lookfor == (ADCBuffer[ADCCounter]>=triggerlevel) )
        {
          lookfor = !lookfor;
          if(1==trigger--)
            stopIndex = ADCCounter; // Can't use waitDuration here because we drop some samples while checking for trigger
        }
      }
      ADCCounter = ADCCounter+1;
      if( ADCBUFFERSIZE == ADCCounter )
        ADCCounter = 0;
      if( stopIndex == ADCCounter )
        break;
    }
    triggerindex = ADCCounter;
  } else { // ordinary operation with software trigger
    while(true)
    {
        while( !(ADCSRA&(1<<ADIF)) )
          if(!keeprunning) break; // Wait for new sample or indication to stop running
        ADCBuffer[ADCCounter] = ADCH; // Grab sample
        sbi(ADCSRA,ADIF); // Reset ADIF

        currentstate = (ADCBuffer[ADCCounter]>=triggerlevel);   
        switch(trigger)
        {
          case 4: // trigger-disabled period ( to make sure we fill at least ADCBUFFERSIZE-waitDuration before trigger )
            if( ADCCounter > ADCBUFFERSIZE-waitDuration )
              trigger--;
            break;
          case 3: // waiting
            if(currentstate == lookfor)
            {
              lookfor = !lookfor;
              trigger--;
            }
            break;
          case 2: // armed
            if(currentstate == lookfor)
            {
              trigger--;
            }
            triggerindex = ADCCounter;
            break;
          case 1: // triggered
            stopIndex = ( triggerindex + waitDuration ) & (ADCBUFFERSIZE-1);
            trigger--;
            break;
        }
        
        ADCCounter = ADCCounter+1;
        if( ADCBUFFERSIZE == ADCCounter )
          ADCCounter = 0;
        if( stopIndex == ADCCounter)
          break;
    }
  }
    
  TIMSK0 = 1; 
  deinitADC();
  scrollindex = 0;
}

void exportData()
{
  
}

void logicMode()
{
  tft.fillScreen(COLOR_BLACK);
  #ifndef __AVR_ATmega2560__
  #warning logic not implemented for Uno
  #else __AVR_ATmega2560__
  DDRA = B00000000; // Set port a to inputs
  dtbuffered_ns = 893;
  #warning logic sample rate is only a rough estimate
  vresbuffered_uV = 0; // so the oscilloscope doesn't try to interpret as analog data
  for(int i = 0; i<ADCBUFFERSIZE; i++)
  {
    //PORTA is pins 22-29
    ADCBuffer[i] = PINA;
  }
  #endif
  plotStatusBar();
  plotdigitaldata();
  plotHorizScale();

  bool returntomain = false;
  while(!returntomain)
  {
    tp.z = 0;
    while(MINPRESSURE>tp.z || MAXPRESSURE<tp.z)
      readResistiveTouch();
  
    if( (PLOTTERX+PLOTTERW/3) > tp.x )                                                   // ******LEFT THIRD******
    {
      if( PLOTTERY + PLOTTERH/2 > tp.y ) // Top half of plot region
      {
        leftfunc = (leftfunc+1)%2;
        plotStatusBar();
        delay(50);
      } else if ( (PLOTTERY + PLOTTERH/2 < tp.y) && (PLOTTERY + PLOTTERH > tp.y) ) { // Bottom half of plot region
        switch(rightfunc)
        {
          case SCALE:
            MySettings.usperdiv = max( MySettings.usperdiv - (MySettings.usperdiv>=1000?100:10)*(1+3*leftfunc), 10);
            plotdigitaldata();
            plotHorizScale();
            plotStatusBar();
            break;
          case SCROLL:
            scrollindex = max( (scrollindex-500*(1+2*leftfunc)*MySettings.usperdiv/dtbuffered_ns) , 0);
            plotdigitaldata();
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
            plotDigitalInformation();
            delay(25);
            break;
          case TRIGGER:
            if(0 == triggertype)
              triggertype = FALLINGEDGE;
            else
              triggertype--;
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
        /*Serial.print("stopIndex: ");
        Serial.print(stopIndex);
        Serial.print("\n");*/
        wait = true; freeze=false;
        for(int i=0;i<10;i++)
        {
          delay(100);
          if(freeze);
            break;
            /*
          if(!freeze && 9==i)
          {
            //tft.setCursor(160,220); // tft may not like me writing to it while ADC is in girino mode
            //tft.println("hung up");
            Serial.print("hung up");
          }*/
        }
        //while(!freeze)
        //  delay(100);
        deinitADC();
        scrollindex = 0;
        plotdigitaldata();
        plotDigitalInformation();
        //tft.begin(ID);
        //tft.setRotation(1); // Landscape
        }
      } else if ( (PLOTTERX + PLOTTERW/3 < tp.x) && ( PLOTTERX + 2*PLOTTERW/3 > tp.x) ) { // ******MIDDLE THIRD******
        //Serial.println("Touch in the middle third...");
        if( PLOTTERY + PLOTTERH/2 > tp.y ) // Top half
        {
          switch(rightfunc)
          {
            case SCALE:
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
              plotdigitaldata();
              plotStatusBar();
              //Serial.print("uVperdiv = ");
              //Serial.println(MySettings.uVperdiv);
              break;
            case TRIGGER:
              restoreplotrow();
              if(255>triggerlevel)
                triggerlevel++;
              storeplotrow();
              tft.drawFastHLine(PLOTTERX,counts_to_vpixels(verticalmidpoint,triggerlevel),PLOTTERW,COLOR_BLUE);
              break;
          }
        } else if ( (PLOTTERY + PLOTTERH/2 < tp.y) && (PLOTTERY + PLOTTERH > tp.y) ) { // Bottom half
          switch(rightfunc)
          {
            case SCALE:
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
              plotdigitaldata();
              plotStatusBar();
              break;
              //Serial.print("uVperdiv = ");
              //Serial.println(MySettings.uVperdiv);
              break;
            case TRIGGER:
              restoreplotrow();
              if(0<triggerlevel)
                triggerlevel--;
              storeplotrow();
              tft.drawFastHLine(PLOTTERX,counts_to_vpixels(verticalmidpoint,triggerlevel),PLOTTERW,COLOR_BLUE);
          }
        }
        //Serial.println("Undefined touch in the middle third");
      } else {                                                                             // ******RIGHT THIRD******
        //Serial.println("Touch in the right third...");
        if( PLOTTERY + PLOTTERH/2 > tp.y ) // Top half
        {
          if(CURSOR==rightfunc)
          {
            restoreplotcolumn();
          } else if (TRIGGER==rightfunc) {
            restoreplotrow();
          }
          rightfunc = (rightfunc+1)%NUMRFUNCS;
          plotStatusBar();
          if( CURSOR == rightfunc )
          {
            cursorpos = min( ADCBUFFERSIZE, scrollindex + 3*MySettings.usperdiv*1000/dtbuffered_ns );
            storeplotcolumn();
            tft.drawFastVLine(PLOTTERX + index_to_hpixels( scrollindex, cursorpos ),PLOTTERY,PLOTTERH,COLOR_RED);
          }
          plotDigitalInformation();
          delay(50); // Not doing a data redraw, so pause a moment to prevent too many responses to touches
        } else if ( (PLOTTERY + PLOTTERH/2 < tp.y) && (PLOTTERY + PLOTTERH > tp.y) ) { // Bottom half
          switch(rightfunc)
          {
            case SCALE:
              MySettings.usperdiv = min( MySettings.usperdiv + (MySettings.usperdiv)*(1+3*leftfunc), 1000000);
              plotHorizScale();
              plotdigitaldata();
              plotStatusBar();
              break;
            case SCROLL:
              scrollindex = min( scrollindex+500*(1+2*leftfunc)*MySettings.usperdiv/dtbuffered_ns, ADCBUFFERSIZE );
              plotHorizScale();
              plotdigitaldata();
              plotStatusBar();
              break;
            case CURSOR:
              restoreplotcolumn();
              cursorpos = cursorpos + 1 + 4*leftfunc;
              if(cursorpos>rightmostindex)
                cursorpos = rightmostindex;
              storeplotcolumn();
              tft.drawFastVLine(PLOTTERX + index_to_hpixels( scrollindex, cursorpos ),PLOTTERY,PLOTTERH,COLOR_RED);
              plotDigitalInformation();
              delay(25);
              break;
            case TRIGGER:
              triggertype = (triggertype+1)%2;
              break;
          }
        } else if ( PLOTTERY+PLOTTERH < tp.y) {
          returntomain = true;
        }
      }
  }
}

void plotdigitaldata()
{
  tft.fillRect(PLOTTERX, PLOTTERY, PLOTTERW, PLOTTERH, COLOR_BLACK);

  // Plot the grid
  //tft.fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
  tft.fillRect(PLOTTERX, PLOTTERY, PLOTTERW, PLOTTERH, COLOR_BLACK);
  for( int i = 0; i<=PLOTTERW; i=i+XDIVPIXELS) tft.drawFastVLine(i+PLOTTERX,PLOTTERY,PLOTTERH,COLOR_DARKERGREY);
  tft.drawFastHLine(PLOTTERX,PLOTTERY,PLOTTERW,COLOR_DARKERGREY);
  tft.drawFastHLine(PLOTTERX,PLOTTERY+PLOTTERH,PLOTTERW,COLOR_DARKERGREY);
  
  tft.setTextSize(2);
  tft.setTextColor(COLOR_WHITE);
  for(int j=0;j<8;j++)
  {
    tft.setCursor(PLOTTERX/2, PLOTTERY + 3 + j*(DIGITALSPACE + DIGITALH));
    tft.print(j);
  }
  int x0 = PLOTTERX;
  int x1 = PLOTTERX;
  int y0[8] = {0,0,0,0,0,0,0,0};
  int y1[8] = {PLOTTERY+0+(1-bitRead(ADCBuffer[scrollindex],0))*DIGITALH, PLOTTERY+1*DIGITALSPACE+(2-bitRead(ADCBuffer[scrollindex],1))*DIGITALH, PLOTTERY+2*DIGITALSPACE+(3-bitRead(ADCBuffer[scrollindex],2))*DIGITALH, PLOTTERY+3*DIGITALSPACE+(4-bitRead(ADCBuffer[scrollindex],3))*DIGITALH, PLOTTERY+4*DIGITALSPACE+(5-bitRead(ADCBuffer[scrollindex],4))*DIGITALH, PLOTTERY+5*DIGITALSPACE+(6-bitRead(ADCBuffer[scrollindex],5))*DIGITALH, PLOTTERY+6*DIGITALSPACE+(7-bitRead(ADCBuffer[scrollindex],6))*DIGITALH, PLOTTERY+7*DIGITALSPACE+(8-bitRead(ADCBuffer[scrollindex],7))*DIGITALH};
  for(int i=scrollindex+1;i<ADCBUFFERSIZE;i++)
  {
    x0 = x1;
    x1 = PLOTTERX+index_to_hpixels( scrollindex, i );
    if(x1>SCREENWIDTH)
      break;
    memcpy(y0,y1,8*sizeof(int));
    for(int j=0;j<8;j++)
    {
      y1[j] = PLOTTERY+DIGITALSPACE*j+(j+1-bitRead(ADCBuffer[i],j))*DIGITALH;
      tft.drawLine(x0,y0[j],x1,y1[j],COLOR_GREENYELLOW);
    }
    rightmostindex = i;
  }
}

void saveBufferToSd()
{
  // Mega uses different pins for hardware SPI. In theory it should be possible to work if you change the pin connections
  // as shown below. Instead, though, the approach is taken to use software SPI. This requires modifying Sd2Card.h and .cpp
  // in the Adafruit SD card library from https://github.com/adafruit/SD, and define MEGA_SOFT_SPI 1.
  // 
  // SPI  Uno  Mega
  //  SS  10   53
  //MOSI  11   51
  //MISO  12   50
  // SCK  13   52
  #warning this will only compile properly if USE_SPI_LIB has been commented out in Sd2Card.h and .cpp, and define MEGA_SOFT_SPI 1
  
  // Initialize SD card if needed
  if(!SDready)
    SDready = SD.begin();
  if(!SDready)
  {
    tft.fillScreen(COLOR_BLACK);
    tft.setCursor(1,10);
    tft.setTextSize(2);
    tft.setTextColor(COLOR_WHITE);
    tft.print(F("Unable to open SD card!"));
    tp.z = 0;
    while(MINPRESSURE>tp.z || MAXPRESSURE<tp.z)
      readResistiveTouch();
    return;
  }

  // Get file name
  char filename[13]; // only need size 11 for .m but will reuse the array below with bmp suffix
  const char* opts[] = {"Both","Data","Pict"};
  int optionchoice = 0;
  filename[0] = '\0';
  int numchars = touchkeyinput(filename, 8, "File name(empty to cancel)", opts, 3, &optionchoice);
  if(0==numchars)
    return; // Don't proceed without at least one character in the file name

  char str[26];
  str[0] = '\0';
  touchkeyinput(str, 25, "Enter caption/note", NULL, NULL, NULL);

  if( 2 > optionchoice )
  {
    filename[numchars] = '.';
    filename[numchars+1] = 'm';
    filename[numchars+2] = '\0';
  
    File myFile = SD.open(filename, FILE_WRITE);
    if (myFile)
    {
      myFile.println(F("% Ranocchio scopemeter output file"));
      myFile.println("");
      myFile.println(str); // Notes
      myFile.println("");
      myFile.print(F("timestep_ns = ")); myFile.print(dtbuffered_ns); myFile.println(";");
      myFile.println("");
      myFile.print(F("microvolts_per_count = ")); myFile.print(vresbuffered_uV); myFile.println(";");
      myFile.println("");
      myFile.println(F("Data = ["));
      myFile.print(ADCBuffer[ADCCounter]);
      for(int i=1; i<ADCBUFFERSIZE; i++)
      {
        myFile.print(',');
        myFile.print(ADCBuffer[(ADCCounter+i)%ADCBUFFERSIZE]);
      }
      myFile.println("];");
      myFile.close();
    } else {
      myFile.close();
      tft.fillScreen(COLOR_BLACK);
      tft.setCursor(1,10);
      tft.setTextSize(2);
      tft.setTextColor(COLOR_WHITE);
      tft.print(F("Unable to write to file!"));
      tp.z = 0;
      while(MINPRESSURE>tp.z || MAXPRESSURE<tp.z)
        readResistiveTouch();
      return;
    }
  }

  if( 0 == optionchoice%3 )
  {
    filename[numchars] = '.';
    filename[numchars+1] = 'b';
    filename[numchars+2] = 'm';
    filename[numchars+3] = 'p';
    filename[numchars+4] = '\0';

    // Draw the screen we want to save
    plotanalogdata();
    plotVertScale();
    plotHorizScale();
    plotStatusBar();
    tft.fillRect(0, PLOTTERY+PLOTTERH+16, SCREENWIDTH, SCREENHEIGHT-PLOTTERY-PLOTTERH-16, COLOR_BLACK);
    tft.setTextColor(COLOR_WHITE);
    tft.setTextSize(2);
    tft.setCursor(2,SCREENHEIGHT-24);
    tft.print(str);
  
    saveScreenshotToSd(filename);
  }

}

// Derived from http://www.technoblogy.com/show?398X
// Licensing terms for this function are unclear. GPL may not apply. Contact original poster for more information.
void saveScreenshotToSd(char* filename)
{
  // Initialize SD card if needed
  if(!SDready)
    SDready = SD.begin();
  if(!SDready)
  {
    tft.fillScreen(COLOR_BLACK);
    tft.setCursor(1,10);
    tft.setTextSize(2);
    tft.setTextColor(COLOR_WHITE);
    tft.print(F("Unable to open SD card!"));
    tp.z = 0;
    while(MINPRESSURE>tp.z || MAXPRESSURE<tp.z)
      readResistiveTouch();
    return;
  }

  #define BMPSIZE (54 + 4 * 320 * 240)
  #define BMPNUM (320*240)

  uint32_t filesize, offset;
  uint16_t width = tft.width(), height = tft.height();

  #define writeFour(a) bmpFile.write((unsigned char)( (a) )); bmpFile.write((unsigned char)( (a) >> 8)); bmpFile.write((unsigned char)( (a) >> 16)); bmpFile.write((unsigned char)( (a) >> 32))
  #define writeTwo(a) bmpFile.write((unsigned char)( (a) )); bmpFile.write((unsigned char)( (a) >> 8));
  File bmpFile = SD.open(filename, FILE_WRITE);
  if (!bmpFile)
  {
    tft.fillScreen(COLOR_BLACK);
    tft.setCursor(1,10);
    tft.setTextSize(2);
    tft.setTextColor(COLOR_WHITE);
    tft.print(F("Unable to write file!"));
    tp.z = 0;
    while(MINPRESSURE>tp.z || MAXPRESSURE<tp.z)
      readResistiveTouch();
    return;
  }
  
  // File header: 14 bytes
  bmpFile.write('B'); bmpFile.write('M');
  writeFour(14+40+12+width*height*2); // File size in bytes
  writeFour(0);
  writeFour(14+40+12);                // Offset to image data from start
  //
  // Image header: 40 bytes
  writeFour(40);                      // Header size
  writeFour(width);                   // Image width
  writeFour(height);                  // Image height
  writeTwo(1);                        // Planes
  writeTwo(16);                       // Bits per pixel
  writeFour(0);                       // Compression (none)
  writeFour(0);                       // Image size (0 for uncompressed)
  writeFour(0);                       // Preferred X resolution (ignore)
  writeFour(0);                       // Preferred Y resolution (ignore)
  writeFour(0);                       // Colour map entries (ignore)
  writeFour(0);                       // Important colours (ignore)
  //
  // Colour masks: 12 bytes
  writeFour(0b0000011111100000);      // Green
  writeFour(0b1111100000000000);      // Red
  writeFour(0b0000000000011111);      // Blue
  //
  // Image data: width * height * 2 bytes
  for (int y=height-1; y>=0; y--) {
    for (int x=0; x<width; x++) {
      writeTwo(tft.readPixel(x,y));    // Each row must be a multiple of four bytes
    }
  }
  
  // Close the file
  bmpFile.close();
  
  return;
}

int sum3(int i) // to filter out noise
{
  return ADCBuffer[(ADCCounter+i-1)%ADCBUFFERSIZE]+ADCBuffer[(ADCCounter+i)%ADCBUFFERSIZE]+ADCBuffer[(ADCCounter+i+1)%ADCBUFFERSIZE];
}

void analyzeData(bool adjustwindow) // Analyze the portion of the data between scrollindex and rightmostindex
{
  // Identify signal mean
  uint8_t swingline(0);
  datamin = 255;
  datamax = 0;
  uint32_t firstpcrossingx10;
  uint32_t lastpcrossingx10;
  uint32_t lastncrossing;
  int thirdpcrossing=0;
  uint32_t foundpcrossings=0;
  uint32_t foundncrossings=0;
  uint32_t totalhightime=0;
  int num;
  bool searchpositive=true;
  datarms = sq((int16_t)ADCBuffer[(ADCCounter+scrollindex)%ADCBUFFERSIZE]-128);
  for(int i = scrollindex+1; i<=rightmostindex-1; i++)
  {
    datarms += sq((int16_t)ADCBuffer[(ADCCounter+i)%ADCBUFFERSIZE]-128);
    if( ADCBuffer[(ADCCounter+i)%ADCBUFFERSIZE] > datamax )
      datamax = ADCBuffer[(ADCCounter+i)%ADCBUFFERSIZE];
    if( ADCBuffer[(ADCCounter+i)%ADCBUFFERSIZE] < datamin )
      datamin = ADCBuffer[(ADCCounter+i)%ADCBUFFERSIZE];
  }
  datarms = sqrt(datarms/(rightmostindex-scrollindex));
  swingline = (datamax+datamin)/2;

  // Find positive crossings of the mean signal
  for(int i=scrollindex+1; i<rightmostindex-1; i++)
  {
    if(searchpositive)
    {
      if ((sum3(i) <= swingline*3) && (sum3(i + 1) > swingline*3)) // triple swingline because using sum3
      {
        if(0==foundpcrossings) {
          firstpcrossingx10 = 10*i + (10*(3*swingline - sum3(i))) / ( sum3(i+1) - sum3(i) );
          lastpcrossingx10 = firstpcrossingx10;
        } else {
          if(2==foundpcrossings)
          {
            thirdpcrossing = i;
          }
          lastpcrossingx10 = 10*i + (10*(3*swingline - sum3(i))) / ( sum3(i+1) - sum3(i) );
        }
        foundpcrossings++;
        searchpositive = false;
      }
    } else {
      if ((sum3(i) > swingline*3) && (sum3(i + 1) <= swingline*3)) // triple swingline because using sum3
      {
        foundncrossings++;
        lastncrossing = i;
        totalhightime += (lastncrossing-lastpcrossingx10/10);
        searchpositive = true;
      }
    }
  }

  // Calculate period and frequency
  dataperiod_us = (lastpcrossingx10-firstpcrossingx10)*dtbuffered_ns/10000/(foundpcrossings-1);
  datafreq_Hzx10 = (long int)10000000/dataperiod_us;
  #warning frequency count is not working
  datadutycyclex1000 = 1000*(10*totalhightime-(searchpositive?lastncrossing*10-lastpcrossingx10:0))/(lastpcrossingx10-firstpcrossingx10);

 if(adjustwindow && (2<foundpcrossings))
 {
    scrollindex = firstpcrossingx10/10;
    MySettings.usperdiv = (dtbuffered_ns*(thirdpcrossing-scrollindex)+1)/6000;
    
    verticalmidpoint = ((int)swingline-128)*vresbuffered_uV;
    MySettings.uVperdiv = (datamax-datamin+2)*vresbuffered_uV/4;
 }
}

void rangeToggled()
{
  //freeze = true;
  redrawinfo = true;
  keeprunning = false;
}

void updateCurrentRange() // Update the current setting for range
{
  switch(PIND&B11) // Port D is pins 18,19,20,21 so get the bottom two bits
  //switch( digitalRead(20)<<1 | digitalRead(21) )
  {
    case B11:
      MySettings.currentrange_mV = 221760;
      break;
    case B01:
      MySettings.currentrange_mV = 69300;
      break;
    case B10:
      MySettings.currentrange_mV = 27610;
      break;
    case B00:
      MySettings.currentrange_mV = 8628;
      break;
  }
}
