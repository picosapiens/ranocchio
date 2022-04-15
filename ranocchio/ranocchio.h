//-----------------------------------------------------------------------------
// ranocchio.h
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

#ifndef RANOCCHIO_H
#define RANOCCHIO_H

#include <SPI.h>          // f.k. for Arduino-1.5.2
#include "Adafruit_GFX.h"// Hardware-specific library
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include <avr/io.h>
#include <util/delay.h>
#include "Girino.h"
#include "touchkbd.h"
//include "fix_fft.h"
#include <arduinoFFT.h>
#include <SD.h>
//define TouchScreen TouchScreen_kbv
//define TSPoint TSPoint_kbv;

#define NOP __asm__ __volatile__ ("nop\n\t")

extern volatile bool keeprunning;

#define SCREENWIDTH 320
#define SCREENHEIGHT 240

#define XDIVPIXELS 50
#define YDIVPIXELS 45

#define PLOTTERX 19
#define PLOTTERY 10
#define PLOTTERW 301
#define PLOTTERH 180

#define DIGITALH 17
#define DIGITALSPACE 4

#define MINPRESSURE 200
#define MAXPRESSURE 1000

const uint8_t vcoarsescale[9] = {10, 15, 20, 25, 30, 40, 50, 75, 100};
extern uint8_t vcoarseindex;
extern uint8_t vfineadjust;
extern uint8_t vpower;
extern long int vrange_uV;

extern long int dataperiod_us;
extern long int datafreq_Hzx10;
extern uint16_t datadutycyclex1000;

extern int XP;
extern int YP;
extern int XM;
extern int YM;

void updateCurrentRange();

extern TouchScreen ts;
extern TSPoint tp;

extern volatile bool redrawinfo;

extern bool SDready;

extern volatile uint32_t dtbuffered_ns;
extern volatile uint32_t vresbuffered_uV;

#define SIMULATION

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

extern MCUFRIEND_kbv tft;
extern uint16_t pixels[SCREENWIDTH];
extern int16_t pixelsx;

//extern int ADCCounter;

#define COLOR_BLACK 0x0000       ///<   0,   0,   0
#define COLOR_NAVY 0x000F        ///<   0,   0, 123
#define COLOR_DARKGREEN 0x03E0   ///<   0, 125,   0
#define COLOR_DARKERGREEN 0x01E0
#define COLOR_DARKCYAN 0x03EF    ///<   0, 125, 123
#define COLOR_MAROON 0x7800      ///< 123,   0,   0
#define COLOR_PURPLE 0x780F      ///< 123,   0, 123
#define COLOR_OLIVE 0x7BE0       ///< 123, 125,   0
#define COLOR_LIGHTGREY 0xC618   ///< 198, 195, 198
#define COLOR_DARKGREY 0x7BEF    ///< 123, 125, 123
#define COLOR_DARKERGREY 0x18E3
#define COLOR_BLUE 0x001F        ///<   0,   0, 255
#define COLOR_GREEN 0x07E0       ///<   0, 255,   0
#define COLOR_CYAN 0x07FF        ///<   0, 255, 255
#define COLOR_RED 0xF800         ///< 255,   0,   0
#define COLOR_MAGENTA 0xF81F     ///< 255,   0, 255
#define COLOR_YELLOW 0xFFE0      ///< 255, 255,   0
#define COLOR_WHITE 0xFFFF       ///< 255, 255, 255
#define COLOR_ORANGE 0xFD20      ///< 255, 165,   0
#define COLOR_GREENYELLOW 0xAFE5 ///< 173, 255,  41
#define COLOR_PINK 0xFC18        ///< 255, 130, 198


#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a, b) (((a) < (b)) ? (b) : (a))
#endif

extern uint16_t waitDuration;

extern uint8_t rightfunc;
#define SCALE 0
#define SCROLL 1
#define CURSOR 2
#define TRIGGER 3
#define NUMRFUNCS 4

extern uint8_t triggerstatus;
extern uint16_t triggerindex;

extern uint8_t triggertype;
#define RISINGEDGE 0
#define FALLINGEDGE 1
#define NOTRIGGER 2
#define NUMTTYPES 3

extern uint16_t tripletrig;
extern uint16_t triplesum;

extern uint8_t triggermode;
extern uint8_t triggerlevel;
#define NORMAL 0
#define SINGLE 1

extern uint8_t leftfunc;
#define COARSEADJUST 1
#define FINEADJUST 0

// May ultimately want to use PROGMEM to help this persist?
typedef struct {
  uint32_t uVperdiv;
  uint32_t usperdiv;
  uint8_t ADCprescaler;
  bool displayrms;
  uint32_t currentrange_mV;
} RanocchioSettings;

extern volatile int16_t scrollindex;
extern volatile int32_t verticalmidpoint;
extern int16_t rightmostindex;
extern int16_t cursorpos;

extern RanocchioSettings MySettings;

void plotanalogdata(); //analog data
void plotdigitaldata();
int index_to_hpixels( int start, int i );
int counts_to_vpixels( long int midpt, int i);
void plotVertScale();
void plotHorizScale();
void plotStatusBar();
void plotInformation();
void plotDigitalInformation();
void datapixel(int index, int color);
void storeplotcolumn();
void storeplotrow();
void restoreplotcolumn();
void restoreplotrow();
void format3char( long int number, char* value, char* sign_units );

void mappoints( TSPoint* tp );

void plotlogic();

void mainMenu();
void meterMode();
void scopeMode();
void logicMode();
void fftsubmode(bool justdraw=false);
void runScope();

void triggerInterrupt();
void rangeToggled();

void saveBufferToSd();
void saveScreenshotToSd(char* filename);

void scopeSettings();

int seconddigit(int x);

void readResistiveTouch(void);

void exportData();


// These signal analysis functions are inspired by Creative Inventor's oscilloscope project
// https://www.youtube.com/watch?v=exiWoeLm4Wc
extern uint8_t datamin;
extern uint8_t datamax;
extern uint32_t datarms;
int sum3(int i);
void analyzeData(bool adjustwindow=false);

#endif // RANOCCHIO_H
