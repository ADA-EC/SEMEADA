
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

int animation_frame=0;
int offset_X = 0;
int offset_Y = 0;
int mood=0;

void loop() {
	delay(random(750, 1250));

	tft.fillScreen(BLACK);
	tft.drawBitmap(offset_X, offset_Y, peyes[mood][animation_frame][0], 240, 320, WHITE); //drawBitmap(x, y, bitmap, largura, altura, cor)
	Serial.println(animation_frame);

	animation_frame++;
	animation_frame%=3;
}
