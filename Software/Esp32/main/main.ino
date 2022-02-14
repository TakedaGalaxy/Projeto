#include "perifericos.h"
#include "esp_task_wdt.h"

MatrizBotoes *teclado;
Joystick *joystick;
Buzzer *buzzer;
RGB *rgb;
Analogico *infraVermelho;
Analogico *luminosidade;

TaskHandle_t tarefa1;

void tarefa(void * pvParameters){
  
  while(1){
    teclado->logica();
    joystick->logica();
    vTaskDelay(1);
  }
    
}

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

  xTaskCreatePinnedToCore(
    tarefa,
    "teclado",
    1000,
    NULL,
    1,
    &tarefa1,
    0);

  inicializaLCD();
  
}


void loop() {

  bool leitura[teclado->getQuantidadeDeTecla()];
  
  if(teclado->getBotao(leitura)){

    Serial.printf("\n");
    
    for(int i = 0; i < teclado->getQuantidadeDeTecla();i++)Serial.printf("%d ",leitura[i]);
  
  }else for(int i = 0; i < teclado->getQuantidadeDeTecla();i++)leitura[i] = false;

  interface( leitura[0] || joystick->getEsquerda()  //Esquerda
            ,leitura[2] || joystick->getDireita()   //Direita
            ,leitura[1] || joystick->getCima()      //Cima
            ,leitura[4] || joystick->getBaixo()     //Baixo
            ,leitura[3]                             //Voltar
            ,leitura[5] || joystick->getBotao()     //Enter
            );
  
  /*

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
  */
}
