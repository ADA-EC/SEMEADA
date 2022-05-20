#include <Adafruit_GFX.h> // Hardware-specific library
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

#define BLACK       0x0000
#define BLUE        0x001F
#define RED         0xF800
#define GREEN       0x07E0
#define CYAN        0x07FF
#define MAGENTA     0xF81F
#define YELLOW      0xFFE0
#define WHITE       0xFFFF
#define ORANGE      0xFD20
#define GREENYELLOW 0xAFE5
#define NAVY        0x000F
#define DARKGREEN   0x03E0
#define DARKCYAN    0x03EF
#define MAROON      0x7800
#define PURPLE      0x780F
#define OLIVE       0x7BE0
#define LIGHTGREY   0xC618
#define DARKGREY    0x7BEF

void setup() {
  Serial.begin(9600);
  tft.reset();
  uint16_t identifier = tft.readID();
  Serial.print("ID = 0x");
  Serial.println(identifier, HEX);
  if (identifier == 0xEFEF) identifier = 0x9486;
  tft.begin(identifier);

  tft.fillScreen(BLACK);

  tft.fillCircle(120, 160, 100, WHITE);
  tft.fillCircle(120, 160, 30, NAVY);

}

void loop() {
  // put your main code here, to run repeatedly:
    int emocao=0;

    emocao = Serial.read();


	switch(emocao){
        case 0:
            tft.fillScreen(YELLOW); //FELIZ
            break;
        case 1:
            tft.fillScreen(BLUE); //TRISTE
            break;
        case 2:
            tft.fillScreen(RED); //BRAVO
            break;
        case 3:
            tft.fillScreen(LIGHTGREY); //NEUTRO
            break;
	}
}
