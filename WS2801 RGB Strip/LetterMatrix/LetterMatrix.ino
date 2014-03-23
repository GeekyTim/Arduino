#include "string.h"
#include "SPI.h"
#include "Adafruit_WS2801.h"

/*****************************************************************************
 * Example sketch for driving Adafruit WS2801 pixels!
 * 
 * 
 * Designed specifically to work with the Adafruit RGB Pixels!
 * 12mm Bullet shape ----> https://www.adafruit.com/products/322
 * 12mm Flat shape   ----> https://www.adafruit.com/products/738
 * 36mm Square shape ----> https://www.adafruit.com/products/683
 * 
 * These pixels use SPI to transmit the color data, and have built in
 * high speed PWM drivers for 24 bit color per pixel
 * 2 pins are required to interface
 * 
 * Adafruit invests time and resources providing this open source code, 
 * please support Adafruit and open-source hardware by purchasing 
 * products from Adafruit!
 * 
 * Written by David Kavanagh (dkavanagh@gmail.com).  
 * BSD license, all text above must be included in any redistribution
 * 
 *****************************************************************************/

// Choose which 2 pins you will use for output.
// Can be any valid output pins.
// The colors of the wires may be totally different so
// BE SURE TO CHECK YOUR PIXELS TO SEE WHICH WIRES TO USE!

// SPI on the UNO
//... RESET|SCK|MISO
//... GND|MOSI|5V

// For my LEDs, connect:
// RED = 5V
// Yellow = GND
// Green = MOSI
// Blue = SCK

byte f5[][5] = {
  {
    B00000,B00000,B00000,B00000,B00000        }
  ,
  {
    B00100,B00100,B00100,B00000,B00100        }
  ,
  {
    B01010,B01010,B00000,B00000,B00000        }
  ,
  {
    B01010,B11111,B01010,B11111,B01010        }
  ,
  {
    B00110,B01100,B00100,B00110,B01100        }
  ,
  {
    B10001,B00010,B00100,B01000,B10001        }
  ,
  {
    B01000,B10100,B01010,B10100,B01010        }
  ,
  {
    B00100,B00100,B00000,B00000,B00000        }
  ,
  {
    B00100,B01000,B01000,B01000,B00100        }
  ,
  {
    B01000,B00100,B00100,B00100,B01000        }
  ,
  {
    B10101,B00100,B11111,B00100,B10101        }
  ,
  {
    B00000,B00100,B01110,B00100,B00000        }
  ,
  {
    B00000,B00000,B00100,B00100,B01000        }
  ,
  {
    B00000,B00000,B01110,B00000,B00000        }
  ,
  {
    B00000,B00000,B00000,B01100,B01100        }
  ,
  {
    B00001,B00010,B00100,B01000,B10000        }
  ,
  {
    B01100,B10010,B10010,B10010,B01100        }
  ,
  {
    B00100,B01100,B00100,B00100,B01110        }
  ,
  {
    B01100,B10010,B00100,B01000,B11110        }
  ,
  {
    B01100,B00010,B00100,B00010,B01100        }
  ,
  {
    B00100,B01100,B10100,B11110,B00100        }
  ,
  {
    B11110,B10000,B11100,B00010,B11100        }
  ,
  {
    B01100,B10000,B11100,B10010,B01100        }
  ,
  {
    B11110,B00010,B00100,B01000,B01000        }
  ,
  {
    B01100,B10010,B01100,B10010,B01100        }
  ,
  {
    B01100,B10010,B01110,B00010,B01100        }
  ,
  {
    B00000,B00100,B00000,B00100,B00000        }
  ,
  {
    B00000,B00100,B00000,B00100,B01000        }
  ,
  {
    B00010,B00100,B01000,B00100,B00010        }
  ,
  {
    B00000,B01110,B00000,B01110,B00000        }
  ,
  {
    B01000,B00100,B00010,B00100,B01000        }
  ,
  {
    B00100,B01010,B00010,B00100,B00100        }
  ,
  {
    B01110,B10001,B10101,B10000,B01110        }
  ,
  {
    B01100,B10010,B11110,B10010,B10010        }
  ,
  {
    B11100,B10010,B11100,B10010,B11100        }
  ,
  {
    B01100,B10010,B10000,B10010,B01100        }
  ,
  {
    B11100,B10010,B10010,B10010,B11100        }
  ,
  {
    B11110,B10000,B11100,B10000,B11110        }
  ,
  {
    B11110,B10000,B11100,B10000,B10000        }
  ,
  {
    B01100,B10010,B10000,B10110,B01100        }
  ,
  {
    B10010,B10010,B11110,B10010,B10010        }
  ,
  {
    B01110,B00100,B00100,B00100,B01110        }
  ,
  {
    B01110,B00100,B00100,B10100,B01000        }
  ,
  {
    B10010,B10100,B11000,B10100,B10010        }
  ,
  {
    B01000,B01000,B01000,B01000,B01110        }
  ,
  {
    B10001,B11011,B10101,B10001,B10001        }
  ,
  {
    B11010,B11010,B10110,B10110,B10010        }
  ,
  {
    B01100,B10010,B10010,B10010,B01100        }
  ,
  {
    B11100,B10010,B11100,B10000,B10000        }
  ,
  {
    B01100,B10010,B10010,B10010,B01101        }
  ,
  {
    B11100,B10010,B11100,B10100,B10010        }
  ,
  {
    B01100,B10000,B01100,B00010,B11100        }
  ,
  {
    B01110,B00100,B00100,B00100,B00100        }
  ,
  {
    B10010,B10010,B10010,B10010,B01100        }
  ,
  {
    B10010,B10010,B10010,B01100,B01100        }
  ,
  {
    B10001,B10001,B10101,B11011,B10001        }
  ,
  {
    B10001,B01010,B00100,B01010,B10001        }
  ,
  {
    B10001,B10001,B01110,B00100,B00100        }
  ,
  {
    B11110,B00010,B01100,B10000,B11110        }
};

#define revRED 16711680
#define revGREEN 65280
#define revBLUE 255

// Don't forget to connect the ground wire to Arduino ground,
// and the +5V wire to a +5V supply

// Set the first variable to the NUMBER of pixels in a row and
// the second value to number of pixels in a column.
Adafruit_WS2801 strip = Adafruit_WS2801((uint16_t)5, (uint16_t)5, WS2801_RGB);

void setup() {
  strip.begin();
  Serial.begin(9600);
}

void loop() {

  //  drawString("Potton Pi & Pints", Color(0, 0, 0), Color(0, 0, 0), 500);
  //  scrollLetterLeft('A', 'B', Color(128, 0, 0), Color(0, 0, 0), 1000);
  //  scrollLetterLeft('B', 'A', Color(128, 0, 0), Color(0, 0, 0), 1000);

  //   scrollLetterUp('A', 'B', Color(0, 128, 0), Color(0, 0, 0), 5000);
  // scrollLetterUp('B', 'A', Color(0, 0, 128), Color(0, 0, 0), 5000);


  /*  scrollStringUp(" Potton Pi & Pints ", Color(0, 128, 0), Color(0, 0, 0), 500);
   delay(1000);
   scrollStringLeft(" Potton Pi & Pints ", Color(0, 0, 128), Color(0, 0, 0), 500);
   delay(1000);
   scrollStringUp(" Potton Pi & Pints ", Color(128, 0, 0), Color(0, 0, 0), 500);
   delay(1000);
   scrollStringLeft(" Potton Pi & Pints ", Color(0, 128, 0), Color(0, 0, 0), 500);
   delay(1000);
   scrollStringUp(" Potton Pi & Pints ", Color(0, 0, 128), Color(0, 0, 0), 500);
   delay(1000);
   scrollStringLeft(" Potton Pi & Pints ", Color(128, 0, 0), Color(0, 0, 0), 500);
   delay(1000);*/
   drawStringFade("Potton Pi & Pints", Color(128, 0, 0), Color(0, 128, 128), 10, 50, 500);

  delay(1000);
}

// Draws a string with foreground and background colours and a delay between characters
void drawString(char *acString, uint32_t fgColour, uint32_t bgColour, int iDelay) {
  int iStringLength;
  int i;

  acString = strupr(acString);
  iStringLength = strlen(acString);

  for (i=0;i<iStringLength;i++) {
    drawLetter(acString[i], fgColour, bgColour);
    delay(iDelay);
    drawLetter(' ', bgColour, bgColour);
    delay(10);
  }
}

// Draws a single letter with foreground and background colours
void drawLetter(char cChar, uint32_t fgColour, uint32_t bgColour) {
  int x,y;

  for (x=0;x<=4;x++) {
    for (y=0;y<=4;y++) {
      if (bitRead(f5[cChar-32][x],4-y)==1) {
        strip.setPixelColor(x, y, fgColour);
      } 
      else {
        strip.setPixelColor(x, y, bgColour);
      }
    }
  }
  strip.show();
}

void scrollLetterLeft(char cChar1, char cChar2, uint32_t fgColour, uint32_t bgColour, int iDuration)
{
  int x, y, z;

  for (z=0;z<=5;z++) {

    // Letter 1
    for (x=0;x<=4;x++) {
      for (y=z;y<=4;y++) {
        if (bitRead(f5[cChar1-32][x],4-y)==1) {
          strip.setPixelColor(x, y-z, fgColour);
        } 
        else {
          strip.setPixelColor(x, y-z, bgColour);
        }
      }
    }
    // Letter 2
    for (x=0;x<=4;x++) {
      for (y=0;y<=(z-1);y++) {
        if (bitRead(f5[cChar2-32][x],4-y)==1) {
          strip.setPixelColor(x, 5-z+y, fgColour);
        } 
        else {
          strip.setPixelColor(x, 5-z+y, bgColour);
        }
      }
    }
    delay(iDuration/5);
    strip.show();
  }
}

void scrollStringLeft(char *acString, uint32_t fgColour, uint32_t bgColour, int iLetterDuration)
{
  int iStringLength;
  int iCount;

  acString = strupr(acString);
  iStringLength = strlen(acString)-1;

  for (iCount=0;iCount<iStringLength;iCount++)
  {
    scrollLetterLeft(acString[iCount], acString[iCount+1], fgColour, bgColour, iLetterDuration);
  }
}

void scrollStringUp(char *acString, uint32_t fgColour, uint32_t bgColour, int iLetterDuration)
{
  int iStringLength;
  int iCount;

  acString = strupr(acString);
  iStringLength = strlen(acString)-1;

  for (iCount=0;iCount<iStringLength;iCount++)
  {
    scrollLetterUp(acString[iCount], acString[iCount+1], fgColour, bgColour, iLetterDuration);
  }
}

void scrollLetterUp(char cChar1, char cChar2, uint32_t fgColour, uint32_t bgColour, int iDuration)
{
  int x, y, z;

  for (z=0;z<=5;z++) {

    // Letter 1
    for (x=z;x<=4;x++) {
      for (y=0;y<=4;y++) {
        if (bitRead(f5[cChar1-32][x],4-y)==1) {
          strip.setPixelColor(x-z, y, fgColour);
        } 
        else {
          strip.setPixelColor(x-z, y, bgColour);
        }
      }
    }
    // Letter 2
    for (x=0;x<=(z-1);x++) {
      for (y=0;y<=4;y++) {
        if (bitRead(f5[cChar2-32][x],4-y)==1) {
          strip.setPixelColor(5-z+x, y, fgColour);
        } 
        else {
          strip.setPixelColor(5-z+x, y, bgColour);
        }
      }
    }
    delay(iDuration/5);
    strip.show();
  }
}

void drawLetterFadeToBG(char cChar, uint32_t fgColour, uint32_t bgColour, int iSteps, int iStepDelay)
{
  int i;
  int fr, fg, fb;

  drawLetter(cChar, fgColour, bgColour);
  for (i=0;i<=iSteps;i++) {
    fr=reverseColour(fgColour, revRED);
    fg=reverseColour(fgColour, revGREEN);
    fb=reverseColour(fgColour, revBLUE);

    drawLetter(cChar, Color(fr-i*(fr-reverseColour(bgColour, revRED))/iSteps, fg-i*(fg-reverseColour(bgColour, revGREEN))/iSteps, fb-i*(fb-reverseColour(bgColour, revBLUE))/iSteps), bgColour);
    delay(iStepDelay);
  }
  drawLetter(' ', fgColour, bgColour);
}

void drawLetterFadeFromGB(char cChar, uint32_t fgColour, uint32_t bgColour, int iSteps, int iStepDelay)
{
  int i;
  int fr, fg, fb;

  drawLetter(' ', fgColour, bgColour);
  for (i=iSteps-1;i>=0;i--) {
    fr=reverseColour(fgColour, revRED);
    fg=reverseColour(fgColour, revGREEN);
    fb=reverseColour(fgColour, revBLUE);
    
    drawLetter(cChar, Color(fr-i*(fr-reverseColour(bgColour, revRED))/iSteps, fg-i*(fg-reverseColour(bgColour, revGREEN))/iSteps, fb-i*(fb-reverseColour(bgColour, revBLUE))/iSteps), bgColour);
    delay(iStepDelay);
  }
  drawLetter(cChar, fgColour, bgColour);
}

void drawLetterFade(char cChar, uint32_t fgColour, uint32_t bgColour, int iSteps, int iStepDelay, int iHold)
{
  drawLetterFadeFromGB(cChar, fgColour, bgColour, iSteps, iStepDelay);
  delay(iHold);
  drawLetterFadeToBG(cChar, fgColour, bgColour, iSteps, iStepDelay);
}

void drawStringFade(char *acString, uint32_t fgColour, uint32_t bgColour, int iSteps, int iStepDelay, int iHold)
{
  int iStringLength;
  int iCount;

  acString = strupr(acString);
  iStringLength = strlen(acString)-1;

  for (iCount=0;iCount<=iStringLength;iCount++)
  {
    drawLetterFade(acString[iCount], fgColour, bgColour, iSteps, iStepDelay, iHold);
  }
}

/* Helper functions */

// Create a 24 bit color value from R,G,B
uint32_t Color(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}

byte reverseColour(uint32_t Colour, uint32_t RGB)
{
  uint32_t c;

  c = Colour & RGB;
  if (RGB>=revRED) {
    c >>= 8;
  }
  if (RGB>=revGREEN) {
    c >>= 8;
  }

  return c;
}











