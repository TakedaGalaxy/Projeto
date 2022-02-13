#include "perifericos.h"

MatrizBotoes *teclado;
Joystick *joystick;
Buzzer *buzzer;
RGB *rgb;
Analogico *infraVermelho;
Analogico *luminosidade;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  int xPinos[3] = {14,12,13};
  int yPinos[2] = {4,15};

  teclado = new MatrizBotoes(xPinos,3,yPinos,2);

  joystick = new Joystick(35,34,16,500);

  buzzer = new Buzzer(26,0,1000,8);

  rgb = new RGB(32,1,33,2,25,3);

  infraVermelho = new Analogico(36);
  luminosidade = new Analogico(39);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  teclado->logica();

  Serial.printf("\n");
  
  for(int i = 0; i < 3*2; i++){

    Serial.printf("%d ",teclado->getBotao(i));
    
  }

  joystick->logica();

  Serial.printf(" D %d E %d C %d B %d BUTAO %d",
                joystick->getDireita(),
                joystick->getEsquerda(),
                joystick->getCima(),
                joystick->getBaixo(),
                joystick->getBotao());

  if(joystick->getBotao())buzzer->setBip(125);
  else buzzer->setBip(0);

  if(teclado->getBotao(0)){
    rgb->setCor(125,0,0);
  }

  if(teclado->getBotao(1)){
    rgb->setCor(0,125,0);
  }

  if(teclado->getBotao(2)){
    rgb->setCor(0,0,125);
  }

  Serial.printf(" IR %d LUMIN %d", infraVermelho->getMedia(50), luminosidade->getMedia(50));
  
}
