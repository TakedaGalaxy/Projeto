#include <arduino.h>
#include "perifericos.h"

/*  Matriz de Botoes  */

//Privado

void MatrizBotoes::configuracaoUm(void){
      
  for(int i = 0; i < this->xTamanho; i++) pinMode(this->xPinos[i],OUTPUT);
  for(int i = 0; i < this->yTamanho; i++) pinMode(this->yPinos[i],INPUT_PULLUP);
    
}

void MatrizBotoes::configuracaoDois(void){
      
  for(int i = 0; i < this->xTamanho; i++) pinMode(this->xPinos[i],INPUT_PULLUP);
  for(int i = 0; i < this->yTamanho; i++) pinMode(this->yPinos[i],OUTPUT);
    
}

void MatrizBotoes::setXOn(void){

  for(int i = 0; this->xPinos[i] != -1; i++) digitalWrite(this->xPinos[i],1);
      
}

void MatrizBotoes::setYOn(void){

  for(int i = 0; this->yPinos[i] != -1; i++) digitalWrite(this->yPinos[i],1);
      
}

//Publico

MatrizBotoes::MatrizBotoes(int xPinos[], int xTamanho, int yPinos[],int yTamanho){

  this->xPinos = (int*)malloc(xTamanho);
  for(int i = 0; i < xTamanho; i++)
    this->xPinos[i] = xPinos[i];
  
  this->xTamanho = xTamanho;
  
  this->yPinos = (int*)malloc(yTamanho);
  for(int i = 0; i < yTamanho; i++)
    this->yPinos[i] = yPinos[i];
  
  this->yTamanho = yTamanho;
  
  this->botoes = (bool*)malloc(xTamanho*yTamanho);
  this->bufferBotoes = (bool*)malloc(xTamanho*yTamanho);

  this->prontoParaLeitura = false;
  
  return;
  
}

void MatrizBotoes::logica(void){

  //Casso o valor anterior não seja lido não verifica o novo valor
  if(this->prontoParaLeitura)return;
  
  int indexBotao = 0;

  //Inicializando com os botoes com o valor 0
  for(int i = 0; i < this->getQuantidadeDeTecla(); i++)this->botoes[i] = 0;

  //Configura a dinamica dos pinos
  configuracaoUm();
  
  for(int y = 0; y < this->yTamanho; y++){

    for(int x = 0; x < this->xTamanho; x++){

      this->setXOn();

      digitalWrite(this->xPinos[x], LOW);

      if(!digitalRead(this->yPinos[y])){

        this->botoes[indexBotao] = true;
        
      }
      
      indexBotao++;
      
    }
    
  }
  
  indexBotao = 0;
  
  //Configura a dinamica dos pinos
  configuracaoDois();
  
  for(int y = 0; y < this->yTamanho; y++){

    this->setYOn();

    digitalWrite(this->yPinos[y], LOW);
    
    for(int x = 0; x < this->xTamanho; x++){

      if(!digitalRead(this->xPinos[x])){

        this->botoes[indexBotao] = true;
        
      }
      
      indexBotao++;
      
    }
    
  }
  
  this->prontoParaLeitura = true;
  
}

bool MatrizBotoes::getBotao(bool *botoes){

  if(this->prontoParaLeitura){
    
    this->prontoParaLeitura = false;

    for(int i = 0; i < this->getQuantidadeDeTecla(); i++)botoes[i] = this->botoes[i];
    
    return 1;
    
  }else return 0;
  
}

unsigned int MatrizBotoes::getQuantidadeDeTecla(void){
  return this->xTamanho*this->yTamanho;
}


/*  joystick  */

//Publico
Joystick::Joystick(int pinX, int pinY, int pinB,int sensibilidade){

  this->pinX = pinX;
  this->pinY = pinY;
  this->pinB = pinB;

  this->sensibilidade = sensibilidade;

  this->x = 0;
  this->xAnterior = 0;

  this->y = 0;
  this->yAnterior = 0;
  
  pinMode(pinB, INPUT_PULLUP);
  
  calibracao(200);
  
  return;
  
}

void Joystick::calibracao(int precisao){

  int minX = analogRead(this->pinX);
  int minY = analogRead(this->pinY);

  int maxX = analogRead(this->pinX);
  int maxY = analogRead(this->pinY);

  int mediaX = 0;
  int mediaY = 0;
  
  for(int i = 0; i < precisao; i++){

    int leituraX = analogRead(this->pinX);
    int leituraY = analogRead(this->pinY);
    
    if (leituraX > maxX)    maxX = leituraX;
    else if(leituraX < minX)  minX = leituraX; 

    if (leituraY > maxY)    maxY = leituraY;
    else if(leituraY < minY)  minY = leituraY; 

    mediaX += leituraX;
    mediaY += leituraY;
    
  }

  mediaX /= precisao;
  mediaY /= precisao;
  
  this->filtroX = (maxX - minX)/2;
  this->filtroY = (maxY - minY)/2;

  this->calibracaoX = mediaX;
  this->calibracaoY = mediaY;

  printf("CX %d CY %d FX %d FY %d",filtroX,filtroY,calibracaoX,calibracaoX);
  
  return;
  
}

void Joystick::logica(void){

  //Realizando a leitura dos calores ad de cada potenciometro
  int xLeitura = analogRead(this->pinX)- calibracaoX;
  int yLeitura = analogRead(this->pinY)- calibracaoY;

  if(xLeitura >= this->xAnterior + this->filtroX){ 
    
    this->x = xLeitura;
    this->xAnterior = this->x;
    
  }
  else if (xLeitura <= this->xAnterior - this->filtroX){ 
    
    this->x = xLeitura;
    this->xAnterior = this->x;
    
  }

  if(yLeitura >= this->yAnterior + this->filtroY){ 
    
    this->y = yLeitura;
    this->yAnterior = this->y;
    
  }
  else if (yLeitura <= this->yAnterior - this->filtroY){ 
    
    this->y = yLeitura;
    this->yAnterior = this->y;
    
  }


  this->botao = !digitalRead(this->pinB);

  if(this->x < -this->sensibilidade){

    this->esquerda = true;
    this->direita  = false;
   
  }else if(this->x > this->sensibilidade){

    this->esquerda = false;
    this->direita  = true;
     
  }else{
    
    this->esquerda = false;
    this->direita  = false;
    
  }

  if(this->y < -this->sensibilidade){

    this->baixo = false;
    this->cima  = true;
   
  }else if(this->y > this->sensibilidade){

    this->baixo = true;
    this->cima  = false;
     
  }else{
    
    this->baixo = false;
    this->cima  = false;
    
  }
  
  return;

}

bool Joystick::getDireita(void) {return this->direita;}
bool Joystick::getEsquerda(void){return this->esquerda;}
bool Joystick::getCima(void)    {return this->cima;}
bool Joystick::getBaixo(void)   {return this->baixo;}

bool Joystick::getBotao(void)   {return this->botao;}

int Joystick::getX(void)        {return this->x;}
int Joystick::getY(void)        {return this->y;}

/* Buzzer */

//Publico
Buzzer::Buzzer(unsigned char pin, unsigned char canalPWM,unsigned int frequencia, unsigned char resolucao){
  
  this->pin = pin;
  this->canalPWM = canalPWM;

  ledcSetup(canalPWM, frequencia, resolucao);

  ledcAttachPin(pin, canalPWM);

  ledcWrite(canalPWM,0);
  
  return;

}

void Buzzer::setBip(unsigned int valor){
      
  ledcWrite(this->canalPWM, valor);

}

/* RGB */

RGB::RGB( unsigned char pinR,unsigned char rC, 
          unsigned char pinG,unsigned char gC,
          unsigned char pinB,unsigned char bC){

  //Grava os pinos de cada cor
  this->pinR = pinR;
  this->pinG = pinG;
  this->pinB = pinB;

  //Grava os canais para cada cor
  this->rC = rC;
  this->gC = gC;
  this->bC = bC;

  //Configura os canais para cada cor  
  ledcSetup(rC,100,8);
  ledcSetup(gC,100,8);
  ledcSetup(bC,100,8);  

  //Vincula o pino da cor ao canal
  ledcAttachPin(pinR,rC);
  ledcAttachPin(pinG,gC);
  ledcAttachPin(pinB,bC);
  
  return;
  
}

void RGB::setCor(unsigned char r,unsigned char g,unsigned char b){

  //Altera o dutyCycle do PWM  
  ledcWrite(this->rC,r);
  ledcWrite(this->gC,g);
  ledcWrite(this->bC,b);
  
  return;

}

/* Analogico */

Analogico::Analogico(unsigned char pin){

  this->pin = pin;

  return;

}

unsigned int Analogico::getValor(void){

  return analogRead(this->pin);
  
}

unsigned int Analogico::getMedia(unsigned int numeroDeLeituras){

  double leituras = 0;

  for(int i = 0; i < numeroDeLeituras; i++){

    leituras += this->getValor();
    
  }
  
  return int(leituras / numeroDeLeituras);

}
