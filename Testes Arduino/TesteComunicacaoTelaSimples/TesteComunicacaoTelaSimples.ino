#include <Servo.h>
#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>   // Hardware-specific library
#include <SPI.h>            // f.k. for Arduino-1.5.2
#include <SD.h>             // Use the official SD library on hardware pins

#define PALETTEDEPTH   0     // do not support Palette modes
#define SD_CS     10

MCUFRIEND_kbv tft;
int pathlen;
File root;

int i, j, comm;

void setup() {
	Serial.begin(9600);
	// for(i = 0; i < 5; i ++){
	// 	servos[i].attach(5+i);
	// }

	uint16_t ID;
	Serial.begin(9600);
	Serial.print("Show BMP files on TFT with ID:0x");
	ID = tft.readID();
	Serial.println(ID, HEX);
	if (ID == 0x0D3D3) ID = 0x9481;
	tft.begin(ID);
	tft.fillScreen(0x001F);
	tft.setTextColor(0xFFFF, 0x0000);
	// uint8_t ret = showBMP("parrot.bmp", 0, 0);

	// for(i = 0; i < 5; i ++){
	// 	servos[i].write(0);
	// }
}
  
void loop() {
	//Código para comunicação com python
	while(!Serial.available());
	// Serial.readBytes(buff, 24);
  comm = Serial.read();
  delay(100);

  switch(int(comm)){
    case '0': //Neutro
      tft.fillScreen(0x0000); //Preto
      break;
    case '1': //Feliz
      tft.fillScreen(0xFFE0); //Amarelo
      break;
    case '2': //Triste
      tft.fillScreen(0x07FF); //Azul
      break;
    case '3': //Bravo
      tft.fillScreen(0xF800); //Vermelho
      break;
    case '4': //Dormindo
      tft.fillScreen(0xFFFF); //Branco
      Serial.println("AAAAAAAAAAA");
      break;
  }

	// for(i = 0; i < 5; i ++){
	// 	servos[i].write(msg[2*i]);  
	// }

	delay(100);
	Serial.write(comm); //Envia os dados da mensagem recebida
	delay(1000);
}