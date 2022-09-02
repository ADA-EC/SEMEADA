#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int16_t msg[13];        //variavel que recebe todas as infos do python
int16_t pos_at[7];      //variavel que guarda a posicao atual dos membros do robô
int16_t incremento[5]; //variavel que guarda o quanto os servos têm que se movimentar
int i, j, pos;
byte buff[4];

void setup() {
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  memset(msg,0,13*sizeof(int16_t)); //set msg to 0
  memset(pos_at,0,7*sizeof(int16_t)); //set msg to 0

  myservo.write(0);
}

void loop() {
  //Código para comunicação com python
  while(!Serial.available());
  for(i=0;i<2;i++){
//    msg[i] = Serial.read();
  }
  Serial.readBytes(buff, 4);
  msg[0] = buff[0] + (buff[1] << 8);
  msg[1] = buff[2] + (buff[3] << 8);
//  Serial.write(buff);
  
  //Serial.readBytes((char*)msg, 13*sizeof(int16_t));
  //Serial.println(msg[0]);

  for(i=0; i<2; i++){
    delay(3000);
    myservo.write(msg[i]);
  }

  

  //Cálculo para movimento do braço
//  for(i=0; i<2; i++){
//    incremento[i] = (msg[i]-pos_at[i])/200;
//  }
//
//  for(i=0;i<200; i++){
//    myservo.write(pos_at[0]);
//    delay(15);
//    pos_at[0]=pos_at[0]+incremento[0];
//  }
//
//  incremento[1] = (msg[1]-pos_at[0])/200;
//  
//  for(i=0;i<200; i++){
//    myservo.write(pos_at[0]);
//    delay(15);
//    pos_at[0]=pos_at[0]+incremento[1];
//  }
  
  Serial.write(msg[0]);
  Serial.print(msg[0]);
//  Serial.write(msg[1]);
  

  /*  for(i=0; i<5; i++){
        incremento[i] = (msg[2*i]-pos_at[i])/200;
      }
  
   for(i=0; i<msg[12];i++){    //roda a quantidade de vezes pedida pelo .py
    for (pos = 0; pos < 200; pos++) {  //Loop de 1s para realizar o movimento
      for(j=0; j<5; j++){
        pos_at[j]+=incremento[j];
      }
      myservo.write(pos_at[0]);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15 ms for the servo to reach the position
    }
  }*/

}
