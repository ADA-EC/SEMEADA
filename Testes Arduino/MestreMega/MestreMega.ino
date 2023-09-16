#include <Servo.h>
#include <SPI.h>            // f.k. for Arduino-1.5.2
#include <SD.h>             // Use the official SD library on hardware pins

int pathlen;
File root;

Servo servos[5];  // create servo object to control a servo

// int16_t incremento[5];	//array que guarda o quanto os servos têm que se movimentar
// int16_t pos_at[7];	//array que guarda a posicao atual dos componentes do robô
int16_t msg[12];	//array que recebe todas o comando decodificado
byte buff[24];	//array que recebe a comunicação serial
int i;


void setup() {
  // Begin the Serial at 9600 Baud
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  
  for(i = 0; i < 5; i ++){
    servos[i].attach(5+i);  //Cria objetos dos servos
  }
  for(i = 0; i < 5; i ++){
    servos[i].write(0);  //Reseta os servos para a posição inicial
  }
  
  memset(msg,0,12*sizeof(int16_t)); //set msg to 0
//   memset(pos_at,0,7*sizeof(int16_t)); //set pos to 0
}


void loop() {
  while(!Serial.available());	//Aguarda mensagem serial
  Serial.readBytes(buff, 24);	//Recebe a mensagem serial

  for(i = 0; i < 12; i++){
    msg[i] = buff[2*i] + (buff[(2*i)+1] << 8);	//Decodifica a mensagem para números
  } 

  Serial1.write(msg[10]);	//Envia mensagem para Olho_1
  Serial2.write(msg[11]);	//Envia mensagem para Olho_2
  
  for(i = 0; i < 5; i ++){
    servos[i].write(msg[2*i]);  //Movimenta servo-motores
  }
}
