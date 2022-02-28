#include "ranocchio.h"
#include "touchkbd.h"

extern MCUFRIEND_kbv tft;

char keyboardkeys[4][10] = { {'1','2','3','4','5','6','7','8','9','0'}, {'Q','W','E','R','T','Y','U','I','O','P'}, {'A','S','D','F','G','H','J','K','L','!'}, {'Z','X','C',' ',' ','<','V','B','N','M'} };

void touchkeyinput(char* s, int numchars, char* instructions)
{
  int index = 0;
  s[0] = '\0'; // May want to change this eventually so there can be default text filled in by the caller?
  tft.setTextSize(2);
  tft.setCursor(0,0);
  tft.print(instructions);
  tft.fillScreen(COLOR_BLACK);
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
  tft.setCursor(20,20);
  
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
        if( index < numchars )
        {
          switch(s[index])
          { 
            case '!':
              done = true;
              break;
            case '<':
              if(0<index)
              {
                s[--index]='\0';
                tft.fillRect(20,20,100,18,COLOR_BLACK);
                tft.setCursor(20,20);
                tft.print(s);
              }
              break;
            default:
              if(numchars>index)
              {
                s[index] = keyboardkeys[row][col];
                tft.print(s[index]);
                Serial.print(", char = "); Serial.println(s[index]);
                index ++;
              }
            break;
          }
        }
      }
    }
    delay(200);
  }
}
