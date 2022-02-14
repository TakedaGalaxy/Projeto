#include <U8g2lib.h>
#include <SPI.h>

#define TELA_INICIAL     1
#define TELA_SENSORES    2


U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, 18, 23, 5, 22);

extern MatrizBotoes *teclado;
extern Joystick *joystick;
extern Buzzer *buzzer;
extern RGB *rgb;
extern Analogico *infraVermelho;
extern Analogico *luminosidade;

//Armazena todas as telas em forma de função
void (*telas[10])(bool,bool,bool,bool,bool,bool);

//Armazena o id atual da tela
unsigned int indexTelaAtual = TELA_INICIAL;

void inicializaLCD(void){
  
  u8g2.begin(); 

  telas[TELA_INICIAL]  = telaInicial;
  telas[TELA_SENSORES] = telaSensores;
  
};

void interface(bool esquerda, bool direita, bool cima, bool baixo, bool voltar ,bool enter){

  u8g2.clearBuffer();
  
  telas[indexTelaAtual](esquerda,direita,cima,baixo,voltar,enter);
  
  u8g2.sendBuffer();
  
}

/* Telas */

int xSelecao = 0, ySelecao = 0;

void telaInicial(bool esquerda, bool direita, bool cima, bool baixo, bool voltar, bool enter){

  //u8g2.setFont(u8g2_font_6x13_tf);

  if(xSelecao < 1) xSelecao += direita;
  if(xSelecao > 0) xSelecao -= esquerda;

  if(ySelecao < 2) ySelecao += baixo;
  if(ySelecao > 0) ySelecao -= cima;

  u8g2.setFont(u8g2_font_helvR08_tr);

  u8g2.drawStr(13,8+12, "Sensores");
  
  if(xSelecao == 0 && ySelecao == 0){

    u8g2.drawFrame(10,8,50,15); 

    if(enter) indexTelaAtual = TELA_SENSORES;
    
  }

  u8g2.drawStr(13,17+8+12, "--------");
  
  if(xSelecao == 0 && ySelecao == 1){

    u8g2.drawFrame(10,15+10,50,15);
  
  }

  u8g2.drawStr(13,64-7-3, "--------");
  
  if(xSelecao == 0 && ySelecao == 2){

    u8g2.drawFrame(10,64-7-15,50,15);
  
  }

  //////////////////////////////////////////////////////////////

  u8g2.drawStr(128-50-7,8+12, "--------");
  
  if(xSelecao == 1 && ySelecao == 0){

    u8g2.drawFrame(128-50-10,8,50,15);
  
  }

  u8g2.drawStr(128-50-7,17+8+12, "--------");

  if(xSelecao == 1 && ySelecao == 1){

    u8g2.drawFrame(128-50-10,15+10,50,15);
  
  }

  u8g2.drawStr(128-50-7,64-7-3, "--------");
  
  if(xSelecao == 1 && ySelecao == 2){

    u8g2.drawFrame(128-50-10,64-7-15,50,15);
  
  }
  
  
  //u8g2.drawButtonUTF8(x*10, y*10, U8G2_BTN_HCENTER|U8G2_BTN_BW2, 34,  2,  2, "Btn" );


  return;

}

void telaSensores(bool esquerda, bool direita, bool cima, bool baixo, bool voltar, bool enter){

  u8g2.setFont(u8g2_font_helvR08_tr);

  u8g2.setCursor(0,10);
  u8g2.printf("IR  : %0.4d",infraVermelho->getMedia(50));

  u8g2.setCursor(0,20);
  u8g2.printf("LUZ : %0.4d",luminosidade->getMedia(50));

  u8g2.setCursor(0,30);
  u8g2.printf("JOY X : %0.4d",joystick->getX());
  
  u8g2.setCursor(0,40);
  u8g2.printf("JOY Y : %0.4d",joystick->getY());

  return;
  
}
