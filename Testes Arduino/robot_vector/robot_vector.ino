
#include <Wire.h>
#include "eyes.h"

#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <Adafruit_GFX.h> // Hardware-specific library
#include <TouchScreen.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

#define YP A3 // Y+ is on Analog1 (use A3 para o 9341)
#define XM A2 // X- is on Analog2 (use A2 para o 9341)
#define YM 9 // Y- is on Digital7 (use 9 para o 9341)
#define XP 8 // X+ is on Digital6 (use 8 para o 9341)

#define TS_MINX 150 // Use 150 para o 9341
#define TS_MINY 120 // Use 120 para o 9341
#define TS_MAXX 920
#define TS_MAXY 940

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 100);
 
//Definicao de cores
#define BLACK           0x0000
#define WHITE           0xFFFF
#define YELLOW          0xFFE0

void setup() {
  Serial.begin(9600);
  tft.reset();
  uint16_t identifier = tft.readID();
  Serial.print("ID = 0x");
  Serial.println(identifier, HEX);
  if (identifier == 0xEFEF) identifier = 0x9486;
  tft.begin(identifier);
  
  Serial.println("Booting");
}

int xp=16;
int mood=1;

void loop() {
  int n;
  static int xd=0;
  static int espera=0;
  static int step=0;
  int x1,x2;
  if (espera>0) {
    espera--;
    delay(1);
  } else {
    x1=   xd+ (xp>16? (16+2*(xp-16)):xp);
    x2=64+xd+ (xp<16? (-16+(xp*2))  :xp);
    switch (step){
      case 0:
       if (xp<6) { 
               tft.drawBitmap(x1, 8, peyes[mood][2][0], 32, 32, WHITE);
               tft.drawBitmap(x2, 8, peyes[mood][1][1], 32, 32, WHITE);
       } else if (xp<26) {
               tft.drawBitmap(x1, 8, peyes[mood][0][0], 32, 32, WHITE);
               tft.drawBitmap(x2, 8, peyes[mood][0][1], 32, 32, WHITE); 
       } else {
               tft.drawBitmap(x1, 8, peyes[mood][1][0], 32, 32, WHITE); 
               tft.drawBitmap(x2, 8, peyes[mood][2][1], 32, 32, WHITE);
       }
       espera=random(250, 1000);
       n=random(0,7);
       if (n==6) {
          step=1;
       } else {
          step=2;
       }
       break;
      case 1:
       tft.drawBitmap(x1, 8, eye0, 32, 32, WHITE);
       tft.drawBitmap(x2, 8, eye0, 32, 32, WHITE);
       espera=100;
       step=0;
       break;
      case 2:
       n=random(0,10);
       if (n<5) xd--;
       if (n>5) xd++;
       if (xd<-4) xd=-3;
       if (xd>4) xd=3; 
       espera=0;
       step=0;
       break;
    }
  }
//n=0;
n=readkey();
if (n==2) xp=(xp<=0?0:xp-1); 
if (n==4) xp=(xp>=32?32:xp+1);
if (n==1) {
  mood=(mood>=5?0:mood+1);
  do {} while (readkey()!=0);
  }
if (n!=0) { espera=0; step=0; }

}
