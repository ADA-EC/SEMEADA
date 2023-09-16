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

Servo servos[5];  // create servo object to control a servo

int16_t msg[12];        //variavel que recebe todas as infos do python
int16_t pos_at[7];      //variavel que guarda a posicao atual dos membros do robô
int16_t incremento[5]; //variavel que guarda o quanto os servos têm que se movimentar
int i, j, pos;
byte buff[24];

void setup() {
	Serial.begin(9600);
	// for(i = 0; i < 5; i ++){
	// 	servos[i].attach(5+i);
	// }

	uint16_t ID;
	Serial.begin(9600);
	// Serial.print("Show BMP files on TFT with ID:0x");
	ID = tft.readID();
	// Serial.println(ID, HEX);
	if (ID == 0x0D3D3) ID = 0x9481;
	tft.begin(ID);
	tft.fillScreen(0x001F);
	tft.setTextColor(0xFFFF, 0x0000);
	if (!SD.begin(SD_CS)) {
		Serial.print(F("cannot start SD"));
		while (1);
	}
	showBMP("parrot.bmp", 0, 0);

	memset(msg,0,12*sizeof(int16_t)); //set msg to 0
	memset(pos_at,0,7*sizeof(int16_t)); //set msg to 0

	// for(i = 0; i < 5; i ++){
	// 	servos[i].write(0);
	// }
}
  
void loop() {
	//Código para comunicação com python
	while(!Serial.available());
	Serial.readBytes(buff, 24);

	for(i = 0; i < 12; i++){
		msg[i] = buff[2*i] + (buff[(2*i)+1] << 8);
	} 

  switch(msg[10]){
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
    // default:
    //   showBMP("parrot.bmp", 0, 0);
    //   break;
  }

	// for(i = 0; i < 5; i ++){
	// 	servos[i].write(msg[2*i]);  
	// }

	delay(100);
	Serial.write(buff, 24); //Envia os dados da mensagem recebida
	delay(500);
  // showBMP("parrot.bmp", 0, 0);
  // delay(500);
  // tft.fillScreen(0x0000);
}