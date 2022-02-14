#ifndef perifericos_h
#define perifericos_h

/*  Matriz de Botoes  */

class MatrizBotoes{

  private:

    //Variaveias que contem informações dos pinos para cada coluna e linha da matriz
    
    int *xPinos;
    int *yPinos;

    int xTamanho;
    int yTamanho;

    //Array que armazena a informação de qual botão está precionado
    
    bool *botoes;
    bool *bufferBotoes;

    bool prontoParaLeitura;

    /*
      Configuração da função dos pinos para a verificação
      As duas configurações são necessarias para possibilitar
      a verificação de mais de dois botões ao mesmo tempo 
    */
    void configuracaoUm(void);
    
    void configuracaoDois(void);

    //Coloca todos os pinos do array xPinos como ON
    void setXOn(void);

    //Coloca todos os pinos do array yPinos como ON  
    void setYOn(void);
    
  public:

    MatrizBotoes(int xPinos[], int xTamanho, int yPinos[],int yTamanho);

    //Realiza a verificação dos botões precionados
    
    void logica(void);

    bool getBotao(bool *botoes);

    unsigned int getQuantidadeDeTecla(void);
  
};

/*  Joystick  */

class Joystick{

  private:

    bool direita, esquerda, cima, baixo;
    
    bool botao;
    
    int x, y;
    int xAnterior, yAnterior;
    
    int calibracaoX, calibracaoY, filtroX, filtroY, sensibilidade;
    
    int pinX, pinY, pinB;
    
  public:

    Joystick(int pinX, int pinY, int pinB,int sensibilidade);

    void calibracao(int precisao);

    void logica(void);
  
    bool getDireita(void);
    bool getEsquerda(void);
    bool getCima(void);
    bool getBaixo(void);
    
    bool getBotao(void);

    int getX(void);
    int getY(void);
    
};

/*  Buzzer  */

class Buzzer{

  private:

    unsigned char pin;

    unsigned char canalPWM;
  
  public:

    Buzzer(unsigned char pin, unsigned char canalPWM,unsigned int frequencia, unsigned char resolucao);
  
    void setBip(unsigned int valor);
  
};

/* RGB */

class RGB{

  private:

    //Variaveis que contem o pino de cada cor 
    unsigned char pinR, pinG, pinB;

    //Variaveis que contem o canal para PWM
    unsigned char rC, gC, bC;
  
  public:

    RGB( unsigned char pinR,unsigned char rC, 
         unsigned char pinG,unsigned char gC,
         unsigned char pinB,unsigned char bC);

    void setCor(unsigned char r,unsigned char g,unsigned char b);
  
};

/* Analogico */

class Analogico{

  private:

    unsigned char pin;
    
  public:

    Analogico(unsigned char pin);

    unsigned int getValor(void);
    
    unsigned int getMedia(unsigned int numeroDeLeituras);
  
};

#endif
