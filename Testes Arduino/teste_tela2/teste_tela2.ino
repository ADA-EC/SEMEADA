//Projeto: Funcionamento do Display Touch em um Arduino MEGA
// Autor: Baú da Eletrônica (www.baudaeletronica.com.br)


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
#define YELLOW          0xFFE0
//
////PP_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
//Adafruit_TFTLCD tft(A3, A2, A1, A0, A4);

// Armazena o estado dos botões
bool valor_botao1 = 0;

void setup(void) 
{

  Serial.begin(9600);
  tft.reset();
  uint16_t identifier = tft.readID();
  Serial.print("ID = 0x");
  Serial.println(identifier, HEX);
  if (identifier == 0xEFEF) identifier = 0x9486;
  tft.begin(identifier);

  tft.fillScreen(YELLOW);
  tft.setRotation(1);
  Serial.println("TFT tela amarela");

  // Texto e Botão
  tft.drawRoundRect(5,15, 312,50, 5, BLACK);
  tft.setTextColor(BLACK);
  tft.setTextSize(3);
  tft.setCursor(10, 30);
  tft.println("BAU DA ELETRONICA");
  Serial.println("TFT texto bau");
 
  //Preenchimento ACENDE
  tft.drawRoundRect(100,100,135,63, 2, BLACK);
  tft.setTextColor(BLACK);
  tft.setCursor(115, 123);
  tft.println("ACENDE");
  Serial.println("TFT botao acende");
}

void loop()
{
  //Serial.println("inicio loop");
  TSPoint p = ts.getPoint();
  pinMode(XM, OUTPUT);
  digitalWrite(XM, LOW);
  pinMode(YP, OUTPUT);
  digitalWrite(YP, HIGH);
  pinMode(YM, OUTPUT);
  digitalWrite(YM, LOW);
  pinMode(XP, OUTPUT);
  digitalWrite(XP, HIGH);
 
 if (p.z > ts.pressureThreshhold)
  {
    Serial.println("identificou toque");
    p.x = tft.width() - (map(p.x, TS_MINX, TS_MAXX, tft.width(), 0));
    p.y = tft.height() - (map(p.y, TS_MINY, TS_MAXY, tft.height(),0));
    if (p.y > 90 && p.y < 135)
    {
      Serial.print("py: ");
      Serial.print(p.y);
      Serial.print(" px: ");
      Serial.print(p.x);

       //Testa Botão
      if (p.x > 95 && p.x < 232)
      {
        if (valor_botao1 == 0)
        {
          tft.fillRoundRect(100, 101, 135, 60, 5, BLACK);
          mostra_apaga(106,120);
          valor_botao1 = !valor_botao1;
        }
        else
        {
          tft.fillRoundRect(101,101, 133,60, 5, YELLOW);
          mostra_acende(106,120);
          valor_botao1 = !valor_botao1;
        }
      }
    }
  }
}

 void mostra_acende(int x, int y)
{
  tft.setTextColor(BLACK);
  tft.setCursor(x, y);
  tft.println("ACENDE");
  delay(100);
}
 
void mostra_apaga(int x, int y)
{
  tft.setTextColor(YELLOW);
  tft.setCursor(x, y);
  tft.println(" APAGA");
  delay(100);
}
