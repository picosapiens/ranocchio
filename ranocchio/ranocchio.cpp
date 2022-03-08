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

uint8_t triggermode=0;
uint8_t triggerlevel;
uint8_t triggerstatus;
uint16_t tripletrig;
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
  tft.fillRect(0,PLOTTERY, SCREENWIDTH-PLOTTERW, PLOTTERH+1, COLOR_BLACK);
  if(NOTRIGGER != triggermode)
  {
    tft.drawFastHLine(0,PLOTTERY + PLOTTERH - counts_to_vpixels(0,triggerlevel),PLOTTERX,COLOR_BLUE);
  }
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
  tft.print("[RUN]");

  tft.setCursor(SCREENWIDTH/2-20,SCREENHEIGHT-10);
  tft.print("[SETTINGS]");

  tft.setCursor(SCREENWIDTH-40,SCREENHEIGHT-10);
  tft.print("[HOME]");

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
          sprintf(str, "Vrms=%ld.%02ldV ", dat/1000, (dat%1000)/10);
        else
          sprintf(str, "Vrms=%ldmV ", dat);
      } else {
        dat = ((datamax-datamin)*vresbuffered_uV)/1000;
        if(dat>1000)
          sprintf(str, "Vp-p=%ld.%02ldV ", dat/1000, (dat%1000)/10);
        else
          sprintf(str, "Vp-p=%ldmV ", dat);
      }
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
  pixelsx = PLOTTERY + PLOTTERH - counts_to_vpixels( 0, triggerlevel); // y coordinate
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
    tft.print("Auto Scale");

    tft.setCursor(5+SCREENWIDTH/2,5+SCREENHEIGHT/3);
    tft.print("Save to SD");

    tp.z = 0;
    while(MINPRESSURE>tp.z || MAXPRESSURE<tp.z)
      readResistiveTouch();

    if( tp.x < SCREENWIDTH/2 ) // ***  Left column ***
    {
      if( tp.y < SCREENHEIGHT/3 ) // Top
      {
        returntomain = true;
      } else if (tp.y < 2*SCREENHEIGHT/3) { // Middle
        scrollindex = 0;
        rightmostindex = waitDuration;
        analyzeData(true);
      }
    } else { //                   *** Right column ***
      if( tp.y < SCREENHEIGHT/3 ) // Top
      {
        MySettings.displayrms = !(MySettings.displayrms);
      } else if ( tp.y < 2*SCREENHEIGHT/3) { // Middle
        saveBufferToSd();
      }
    }
  }
}

void datapixel(int index, int color)
{
  // Redraw the pixel as a yellow green dot
  int x = PLOTTERX + index_to_hpixels( scrollindex, index ); //map(i,0,ADCBUFFERSIZE,PLOTTERX,PLOTTERX+PLOTTERW);
  int y = PLOTTERY + PLOTTERH - counts_to_vpixels(0, ADCBuffer[(ADCCounter+index)%ADCBUFFERSIZE]);
  tft.drawPixel(x,y,color);
}

// based on similar function from MCU_Friend example TouchScreen_Calibr_native
void readResistiveTouch(void)
{
    tp = ts.getPoint();
    /*if( MINPRESSURE < tp.z && MAXPRESSURE>tp.z )
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

  if( MINPRESSURE < tp->z && MAXPRESSURE>tp->z )
  {
    Serial.print("tp.x = ");
    Serial.print(tp->x);
    Serial.print(", tp.y = ");
    Serial.print(tp->y);
    Serial.print(", tp.z = ");
    Serial.println(tp->z);
  }
}

void mainMenu()
{
  tft.setTextSize(3);

  //TODO would be nice to come up with proper icons
  tft.fillRect(0,0, SCREENWIDTH/2, SCREENHEIGHT/2, COLOR_RED);
  tft.setCursor(30,SCREENHEIGHT/6);
  tft.setTextColor(COLOR_WHITE);
  tft.print("SCOPE");
  tft.fillRect(SCREENWIDTH/2,0, SCREENWIDTH/2, SCREENHEIGHT/2, COLOR_GREEN);
  tft.setCursor(SCREENWIDTH/2+30,SCREENHEIGHT/6);
  tft.setTextColor(COLOR_BLACK);
  tft.print("METER");
  tft.fillRect(0,SCREENHEIGHT/2, SCREENWIDTH/2, SCREENHEIGHT/2, COLOR_BLUE);
  tft.setCursor(30,SCREENHEIGHT/2+SCREENHEIGHT/6);
  tft.setTextColor(COLOR_WHITE);
  tft.print("LOGIC");
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
    tp.z = 0;
    while(MINPRESSURE>tp.z || MAXPRESSURE<tp.z)
      readResistiveTouch();
  
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
            triggertype = (triggertype+1)%3;
            plotStatusBar();
            delay(100);
            break;
        }
        //Serial.print("usperdiv = ");
        //Serial.println(MySettings.usperdiv);
      } else if ( PLOTTERY+PLOTTERH < tp.y) { // Very bottom of screen
        //Serial.println("Running scope...");
        memset( (void *)ADCBuffer, 0, sizeof(ADCBuffer) ); // clear buffer
        triplesum = 0;
        tripletrig = 3*triggerlevel;
        sei();
        initPins();
        initADC();
        delay(10);
        //ADCCounter=0;
        startADC();
        //delay(10); // Takes a little while to get going?
        if(NOTRIGGER == triggertype)
        {
          triggerstatus = 2; //immegiately mark as triggered
          stopIndex = ( ADCCounter + waitDuration ) % ADCBUFFERSIZE;
        } else {
          triggerstatus = 0; // ready
          stopIndex = ADCBUFFERSIZE+1; // will never reach this, but will update when triggered
        }
        wait = true; freeze=false;
        
        /*Serial.print("stopIndex: ");
        Serial.print(stopIndex);
        Serial.print("\n");*/
        
        /*for(int i=0;i<10;i++)
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
        }*/
        while(!freeze)
          delay(100);
        #warning Need to implement stop button so we can't get stuck waiting forever for trigger
        #warning Should write an indicator to the screen to show measurement is running
        deinitADC();
        scrollindex = 0;
        plotanalogdata();
        plotInformation();
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
              plotanalogdata();
              analyzeData();
              plotStatusBar();
              plotVertScale();
              //Serial.print("uVperdiv = ");
              //Serial.println(MySettings.uVperdiv);
              break;
            case TRIGGER:
              restoreplotrow();
              if(255>triggerlevel)
                triggerlevel++;
              storeplotrow();
              tft.drawFastHLine(PLOTTERX,PLOTTERY+PLOTTERH-counts_to_vpixels(0,triggerlevel),PLOTTERW,COLOR_BLUE);
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
              //Serial.print("uVperdiv = ");
              //Serial.println(MySettings.uVperdiv);
              break;
            case TRIGGER:
              restoreplotrow();
              if(0<triggerlevel)
                triggerlevel--;
              storeplotrow();
              tft.drawFastHLine(PLOTTERX,PLOTTERY+PLOTTERH-counts_to_vpixels(0,triggerlevel),PLOTTERW,COLOR_BLUE);
          }
        } else if ( PLOTTERY+PLOTTERH < tp.y) { // Very bottom of screen
          scopeSettings();
          plotanalogdata();
          plotStatusBar();
          plotVertScale();
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
            tft.drawFastHLine(PLOTTERX,PLOTTERY+PLOTTERH-counts_to_vpixels(0,triggerlevel),PLOTTERW,COLOR_BLUE);
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
  #warning sample rate is only a rough estimate
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
              tft.drawFastHLine(PLOTTERX,counts_to_vpixels(0,triggerlevel),PLOTTERW,COLOR_BLUE);
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
              tft.drawFastHLine(PLOTTERX,counts_to_vpixels(0,triggerlevel),PLOTTERW,COLOR_BLUE);
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
    tft.print("Unable to open SD card!");
    tp.z = 0;
    while(MINPRESSURE>tp.z || MAXPRESSURE<tp.z)
      readResistiveTouch();
    return;
  }

  // Get file name
  char str[11];
  str[0] = '\0';
  int i = touchkeyinput(str, 8, "Enter file name");
  if(0==i)
    return; // Don't proceed without at least one character in the file name
  str[i] = '.';
  str[i+1] = 'm';
  str[i+2] = '\0';
  

  File myFile = SD.open(str, FILE_WRITE);
  if (myFile)
  {
    myFile.println("% Ranocchio scopemeter output file");
    myFile.println("");
    myFile.print("timestep_ns = "); myFile.print(dtbuffered_ns); myFile.println(";");
    myFile.println("");
    myFile.print("microvolts_per_count = "); myFile.print(vresbuffered_uV); myFile.println(";");
    myFile.println("");
    myFile.println("Data = [");
    myFile.print(ADCBuffer[ADCCounter]);
    for(int i=0; i<ADCBUFFERSIZE; i++)
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
    tft.print("Unable to write to file!");
    tp.z = 0;
    while(MINPRESSURE>tp.z || MAXPRESSURE<tp.z)
      readResistiveTouch();
    return;
  }
}

int sum3(int i) // to filter out noise
{
  return ADCBuffer[(ADCCounter+i-1)%ADCBUFFERSIZE]+ADCBuffer[(ADCCounter+i)%ADCBUFFERSIZE]+ADCBuffer[(ADCCounter+i+1)%ADCBUFFERSIZE];
}

void analyzeData(bool adjustwindow) // Analyze the portion of the data displayed on the screen
{
  // Identify signal mean
  uint8_t swingline(0);
  datamin = 255;
  datamax = 0;
  uint32_t firstpcrossingx10;
  uint32_t lastpcrossingx10;
  uint32_t lastncrossing;
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

 if(adjustwindow && foundncrossings)
 {
    scrollindex = firstpcrossingx10/10;
    MySettings.usperdiv = (2*dtbuffered_ns*lastncrossing/foundncrossings - scrollindex)/6000 + 1;
    
    #warning need to scale vertical axis and (once we have a vertical scroll) vertical position
 }
}
