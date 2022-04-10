//-----------------------------------------------------------------------------
// touchkbd.cpp
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
#include "touchkbd.h"

extern MCUFRIEND_kbv tft;

char keyboardkeys[4][10] = { {'1','2','3','4','5','6','7','8','9','0'}, {'Q','W','E','R','T','Y','U','I','O','P'}, {'A','S','D','F','G','H','J','K','L','!'}, {'Z','X','C',' ',' ','<','V','B','N','M'} };

int touchkeyinput(char* s, int numchars, char* instructions, char* toggleoptions[], int numtoggleoptions, int* togglechoice)
{
  int index = 0;
  s[0] = '\0'; // May want to change this eventually so there can be default text filled in by the caller?
  tft.fillScreen(COLOR_BLACK);
  tft.setTextSize(2);
  tft.setCursor(0,0);
  tft.print(instructions);
  for(int i=0;i<5;i++)
    tft.drawFastHLine(0,KEYBOARDY+i*KEYSIZE,SCREENWIDTH,COLOR_WHITE);
  for(int r=0;r<4;r++)
  {
    for(int c=0;c<10;c++)
    {
      tft.setCursor(KEYSIZE/3 + c*KEYSIZE, KEYBOARDY + KEYSIZE/3 + r*KEYSIZE);
      tft.print(keyboardkeys[r][c]);
    }
  }

  if( (NULL != toggleoptions) && (0<numtoggleoptions) )
  {
    if(*togglechoice >= numtoggleoptions)
      *togglechoice = 0;
    tft.setCursor(10,60);
    tft.print(toggleoptions[*togglechoice]);
  }
  
  tft.setCursor(20,35);
  
  bool done = false;
  while(!done)
  {
    tp.z = 0;
    readResistiveTouch();
    if(MINPRESSURE>tp.z || MAXPRESSURE<tp.z)
      continue;
    int row = (tp.y - KEYBOARDY)/KEYSIZE;
    int col = tp.x/KEYSIZE;
    Serial.print("row = "); Serial.print(row); Serial.print(", col = "); Serial.print(col);
    if( 0 <= row && 4 > row)
    {
      if( 0 <= col && 10 > col)
      {
        switch( keyboardkeys[row][col] )
        {
            case '!':
              done = true;
              break;
            case '<':
              if(0<index)
              {
                s[--index]='\0';
                tft.fillRect(20,30,160,19,COLOR_BLACK);
                tft.setCursor(20,30);
                tft.print(s);
              }
              break;
            default:
              if(numchars>index)
              {
                s[index] = keyboardkeys[row][col];
                s[index+1] = '\0';
                tft.print(s[index]);
                Serial.print(", char = "); Serial.println(s[index]);
                index ++;
              }
        }
      }
    } else { // Negative row means the tap occurred above the keyboard
      *togglechoice = (*togglechoice+1)%numtoggleoptions;
      if( numtoggleoptions )
      {
        int x,y;
        x = tft.getCursorX();
        y = tft.getCursorY();
        tft.fillRect(0,60,SCREENWIDTH,12,COLOR_BLACK);
        tft.setCursor(10,60);
        tft.print(toggleoptions[*togglechoice]);
        tft.setCursor(x,y);
      }
    }
    delay(200);
  }
  return index;
}
