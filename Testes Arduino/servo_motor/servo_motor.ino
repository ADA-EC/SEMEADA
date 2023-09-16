#include <Servo.h>

Servo servos[5];  // create servo object to control a servo

int16_t msg[12];        //variavel que recebe todas as infos do python
int16_t pos_at[7];      //variavel que guarda a posicao atual dos membros do robô
int16_t incremento[5]; //variavel que guarda o quanto os servos têm que se movimentar
int i, j, pos;
byte buff[24];

void setup() {
  Serial.begin(9600);
  for(i = 0; i < 5; i ++){
    servos[i].attach(5+i);  
  }

  memset(msg,0,12*sizeof(int16_t)); //set msg to 0
  memset(pos_at,0,7*sizeof(int16_t)); //set msg to 0

  for(i = 0; i < 5; i ++){
    servos[i].write(0);  
  }
}
  
void loop() {
  //Código para comunicação com python
  while(!Serial.available());
  Serial.readBytes(buff, 24);

  for(i = 0; i < 12; i++){
    msg[i] = buff[2*i] + (buff[(2*i)+1] << 8);
  }

  for(i = 0; i < 5; i ++){
    servos[i].write(msg[2*i]);  
  }

  delay(100);
  Serial.write(buff, 24);
  delay(1000);
  

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
  
//  Serial.write(msg[0]);
//  Serial.print(msg[0]);
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
