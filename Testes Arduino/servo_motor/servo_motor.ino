#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int16_t msg[13];        //variavel que recebe todas as infos do python
int16_t pos_at[7];      //variavel que guarda a posicao atual dos membros do robô
int16_t incremento[5]; //variavel que guarda o quanto os servos têm que se movimentar
int i, j, pos;

void setup() {
  Serial.begin(9600);
  myservo.attach(10);  // attaches the servo on pin 9 to the servo object
  memset(msg,0,13*sizeof(int16_t)); //set msg to 0
  memset(msg,0,7*sizeof(int16_t)); //set msg to 0
}

void loop() {
  //Código para comunicação com python
  while(!Serial.available());
  for(i=0;i<13;i++){
    msg[i] = Serial.read();
    Serial.println(msg[i]);
  }

  //Serial.readBytes((char*)msg, 13*sizeof(int16_t));
  //Serial.println(msg[0]);

  myservo.write(msg[0]);

  //Cálculo para movimento do braço
  /*for(i=0; i<5; i++){
    incremento[i] = (msg[2*i]-pos_at[i])/200;
  }
  

  for(i=0; i<msg[12];i++){    //roda a quantidade de vezes pedida pelo .py
    for (pos = 0; pos <= 200; pos++) {  //Loop de 1s para realizar o movimento
      for(j=0; j<5; j++){
        pos_at[j]+=incremento[j];
      }
      myservo.write(pos_at[0]);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15 ms for the servo to reach the position
    }
  }*/

}
