#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>   // Hardware-specific library
#include <SPI.h>            // f.k. for Arduino-1.5.2
#include <SD.h>             // Use the official SD library on hardware pins

#define PALETTEDEPTH   0     // do not support Palette modes
#define SD_CS     10

MCUFRIEND_kbv tft;
byte buff[2];
uint16_t ID;
int16_t msg;
int pathlen;
File root;


void setup() {
	Serial.begin(9600);

	ID = tft.readID();	//Lê ID do hardware para conectar
	if (ID == 0x0D3D3) ID = 0x9481;
	tft.begin(ID);	//Conecta tela

	if (!SD.begin(SD_CS)) {	//Tenta acessar cartão SD
		Serial.print(F("cannot start SD"));
		while (1);
	}
	showBMP("pisca.bmp", 0, 0);	//Inicializa com olho fechado
	msg = 0;
}

void loop() {
	while(!Serial.available());	//Aguarda mensagem serial
	Serial.readBytes(buff, 2);	//Recebe mensagem serial

	int16_t msg = buff[0] + (buff[1] << 8);	//Decodifica mensagem

	switch(msg){	//Muda para olho
		case 0: //Neutro
			showBMP("aberto.bmp", 0, 0);
			break;
		case 1: //Feliz
			showBMP("feliz.bmp", 0, 0);
			break;
		case 2: //Triste
			showBMP("triste.bmp", 0, 0);
			break;
		case 3: //Bravo
			showBMP("raiva.bmp", 0, 0);
			break;
		case 4: //Dormindo
			showBMP("pisca.bmp", 0, 0);
			break;
	}
}