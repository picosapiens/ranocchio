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

#include "ranocchio.h"

volatile RanocchioSettings MySettings;

uint8_t vcoarseindex;
uint8_t vfineadjust;
uint8_t vpower;

uint8_t datamin;
uint8_t datamax;
uint16_t datadutycyclex1000;
long int dataperiod_us;
long int datafreq_Hzx10;

int XP = 7, YP = A2, XM = A1, YM = 6;
TouchScreen_kbv ts(XP, YP, XM, YM, 325); // last argument is ohms measured between D6 and RS
TSPoint_kbv tp;                            //global point

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
  long int wholepart = MySettings.uVperdiv*2;
  int fracpart = 0;
  char prefix = 'u';
  while(wholepart >= 1000)
  {
    fracpart = (wholepart%1000)/100;
    wholepart = wholepart/1000;
    switch (prefix)
    {
      case 'u':
        prefix = 'm';
        break;
      case 'm':
        prefix = ' ';
        break;
      case ' ':
        prefix = 'k'; // Should never get this high
        break;
      default:
        prefix = '?'; // failure to prefix
    }
  }
  tft.fillRect(0,PLOTTERY, SCREENWIDTH-PLOTTERW, PLOTTERH, COLOR_BLACK);
  tft.setTextSize(1);
  tft.setTextColor(COLOR_WHITE);
  
  tft.setCursor(0,PLOTTERY);
  tft.print(wholepart);
  if( 10>wholepart )
  {
    tft.print('.');
    tft.print(fracpart);
  }
  tft.setCursor(0,PLOTTERY+8);
  tft.print('+');
  tft.print(prefix);
  tft.print('V');
  
  tft.setCursor(0,PLOTTERY+PLOTTERH-16);
  tft.print('-');
  tft.print(prefix);
  tft.print('V');
  tft.setCursor(0,PLOTTERY+PLOTTERH-8);
  tft.print(wholepart);
  if( 10>wholepart )
  {
    tft.print('.');
    tft.print(fracpart);
  }
}

void format3char( long int number, char* value, char* sign_units )
{
  Serial.print("Expressing ");
  Serial.print(number);
  Serial.print(" as whole part ");
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
  tft.fillRect(0,0, SCREENWIDTH, PLOTTERY-1, COLOR_BLACK);
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
  
  tft.setCursor(100, 0);
  number = MySettings.usperdiv;
  strcpy(sign_units,"+us");
  format3char(number,value,sign_units);
  tft.print(value);
  tft.print(sign_units[1]); tft.print(sign_units[2]);
  tft.print("/div");

  tft.setCursor(180, 0);
  number = MySettings.uVperdiv;
  strcpy(sign_units,"+uV");
  format3char(number,value,sign_units);
  tft.print(value);
  tft.print(sign_units[1]); tft.print(sign_units[2]);
  tft.print("/div");

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
    default:
      tft.print("[???]");
      
  }
}

void plotHorizScale()
{
  tft.fillRect(0,PLOTTERY+PLOTTERH+1, SCREENWIDTH, 15, COLOR_BLACK);
  tft.setTextSize(1);
  tft.setTextColor(COLOR_WHITE);
  
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
  tft.setTextSize(2);
  tft.setTextColor(COLOR_WHITE);
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
      
      dat = ((datamax-datamin)*vresbuffered_uV)/1000;
      if(dat>1000)
        sprintf(str, "Vpp=%ld.%02ldV ", dat/1000, (dat%1000)/10);
      else
        sprintf(str, "Vpp=%ldmV ", dat);
      tft.print(str);

      if(datafreq_Hzx10 < 1000 )
        sprintf(str, "f=%ld.%ldHz ", datafreq_Hzx10/10, datafreq_Hzx10%10);
      else
        sprintf(str, "f=%ldHz ", datafreq_Hzx10/10);
      tft.print(str);

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
      sprintf(str, "%ldus, %ldmV", cursorpos*dtbuffered_ns/1000, ((long int)(ADCBuffer[ADCCounter+cursorpos])-128)*(long int)vresbuffered_uV/1000);
      tft.print(str);
      break;
  }
}

void storeplotcolumn()
{
  pixelsx = PLOTTERX + index_to_hpixels( scrollindex, cursorpos );
  tft.readGRAM( pixelsx, PLOTTERY, pixels, 1, PLOTTERH);
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

void plotdata()
{
  // Plot the grid
  //tft.fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
  tft.fillRect(PLOTTERX, PLOTTERY, PLOTTERW, PLOTTERH, COLOR_BLACK);
  for( int i = 0; i<=PLOTTERW; i=i+XDIVPIXELS) tft.drawFastVLine(i+PLOTTERX,PLOTTERY,PLOTTERH,COLOR_DARKERGREY);
  for( int i = 0; i<=PLOTTERH; i=i+YDIVPIXELS) tft.drawFastHLine(PLOTTERX,i+PLOTTERY,PLOTTERW,COLOR_DARKERGREY);

  // Plot the data
  int y0 = PLOTTERY + PLOTTERH - counts_to_vpixels(0, ADCBuffer[(ADCCounter+scrollindex)%ADCBUFFERSIZE]);
  //Serial.print("Data starts here\n");
  //Serial.println(ADCBuffer[ADCCounter+waitDuration]);
  int y1;
  int x0 = PLOTTERX;
  int x1;
  rightmostindex = scrollindex;
  for (int i = scrollindex; i<ADCBUFFERSIZE; i++)
  {
    x1 = PLOTTERX + index_to_hpixels( scrollindex, i ); //map(i,0,ADCBUFFERSIZE,PLOTTERX,PLOTTERX+PLOTTERW);
    y1 = PLOTTERY + PLOTTERH - counts_to_vpixels(0, ADCBuffer[(ADCCounter+i)%ADCBUFFERSIZE]);
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

int counts_to_vpixels( int midpt, int i)
{
  return map(((long int)i-128)*vresbuffered_uV,midpt-((int32_t)PLOTTERH / YDIVPIXELS)*MySettings.uVperdiv/2,  midpt+((int32_t)PLOTTERH / YDIVPIXELS)*MySettings.uVperdiv/2, 0, PLOTTERH);
}

void datapixel(int index, int color)
{
  // Redraw the pixel as a yellow green dot
  int x = PLOTTERX + index_to_hpixels( scrollindex, index ); //map(i,0,ADCBUFFERSIZE,PLOTTERX,PLOTTERX+PLOTTERW);
  int y = PLOTTERY + PLOTTERH - counts_to_vpixels(0, ADCBuffer[(ADCCounter+index)%ADCBUFFERSIZE]);
  tft.drawPixel(x,y,color);
}

// From MCU_Friend example TouchScreen_Calibr_native
void readResistiveTouch(void)
{
    tp = ts.getPoint();
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);
    //digitalWrite(YP, HIGH);  //because TFT control pins
    //digitalWrite(XM, HIGH);
    //    Serial.println("tp.x=" + String(tp.x) + ", tp.y=" + String(tp.y) + ", tp.z =" + String(tp.z));
}

void mappoints( TSPoint_kbv* tp )
{
  //int x = tp->x;
  tp->x = map(tp->x, 180, 930, 0, 320);
  tp->y = map(tp->y, 180, 918, 0, 240);

  //PORTRAIT  CALIBRATION     240 x 320
  /*
  x = map(p.x, LEFT=181, RT=918, 0, 240)
  y = map(p.y, TOP=938, BOT=184, 0, 320)*/
}

int sum3(int i) // to filter out noise
{
  return ADCBuffer[(ADCCounter+i-1)%ADCBUFFERSIZE]+ADCBuffer[(ADCCounter+i)%ADCBUFFERSIZE]+ADCBuffer[(ADCCounter+i+1)%ADCBUFFERSIZE];
}

void analyzeData() // Analyze the portion of the data displayed on the screen
{
  // Identify signal mean
  uint8_t swingline(0);
  datamin = 255;
  datamax = 0;
  uint32_t firstpcrossingx10;
  uint32_t lastpcrossingx10;
  uint32_t lastncrossing;
  uint32_t foundpcrossings=0;
  uint32_t totalhightime=0;
  bool searchpositive=true;
  for(int i = scrollindex; i<=rightmostindex; i++)
  {
    if( ADCBuffer[(ADCCounter+i)%ADCBUFFERSIZE] > datamax )
      datamax = ADCBuffer[(ADCCounter+i)%ADCBUFFERSIZE];
    if( ADCBuffer[i] < datamin )
      datamin = ADCBuffer[(ADCCounter+i)%ADCBUFFERSIZE];
  }
  swingline = (datamax+datamin)/2;

  // Find positive crossings of the mean signal
  for(int i=scrollindex+1; i<rightmostindex; i++)
  {
    if(searchpositive)
    {
      if ((sum3(i) <= swingline*3) && (sum3(i + 1) > swingline*3)) // triple swingline because using sum3
      {
        if(0==foundpcrossings) {
          firstpcrossingx10 = 10*i + (10*(3*swingline - sum3(i))) / ( sum3(i+1) - sum3(i) );
          lastpcrossingx10 = firstpcrossingx10;
        } else {
          lastpcrossingx10 = 10*i + (10*(3*swingline - sum3(i))) / ( sum3(i+1) - sum3(i) );
        }
        foundpcrossings++;
        searchpositive = false;
      }
    } else {
      if ((sum3(i) > swingline*3) && (sum3(i + 1) <= swingline*3)) // triple swingline because using sum3
      {
        lastncrossing = i;
        totalhightime += (lastncrossing-lastpcrossingx10/10);
        searchpositive = true;
      }
    }
  }

  // Calculate period and frequency
  dataperiod_us = (lastpcrossingx10-firstpcrossingx10)*dtbuffered_ns/10000/(foundpcrossings-1);
  datafreq_Hzx10 = (long int)10000000/dataperiod_us;
  datadutycyclex1000 = 10000*(totalhightime-(searchpositive?lastncrossing*10-lastpcrossingx10:0))/(lastpcrossingx10-firstpcrossingx10);
  #warning does not consider partial cycles
  
  
}
