//Projeto: Funcionamento do Display Touch em um Arduino MEGA
// Autor: Baú da Eletrônica (www.baudaeletronica.com.br)

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>


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
#define YELLOW          0xFFE0

//PP_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
Adafruit_TFTLCD tft(A3, A2, A1, A0, A4);

// Armazena o estado dos botões
bool valor_botao1 = 0;


void setup() {
  Serial.begin(9600);
  Serial.println("TFT Test");
  tft.reset();
  delay(500);

  uint16_t id;

  for(id=30000; id<=50000; id++){

    
    tft.begin(id);
    tft.fillScreen(YELLOW);
    tft.setRotation(1);
    Serial.println(id);

    //delay(100);
  }
  
  Serial.println("Acabei!");

}

void loop() {
  // put your main code here, to run repeatedly:

}
