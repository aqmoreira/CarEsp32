#ifndef CarEsp32_h
#define CarEsp32_h
#include <Arduino.h>

#define VELOCIDADE_SOM 0.034
//Entrada dos Sensores Linha
#define SL1  16
#define SL2  17
#define SL3  18
#define SL4  19
#define SL5  23
    //Entrada Chaves
#define SW1  35
#define SW2  36
#define SW3  39
#define SW4  34
    //Sensor UltraSon
#define ECO  12
#define TRG  13
//Ponte H
//MOTOR_A
#define MOTOR_A_EN  14
#define MOTOR_A_IN1  27
#define MOTOR_A_IN2  26
//MOTOR_B
#define MOTOR_B_EN  32
#define MOTOR_B_IN1  25
#define MOTOR_B_IN2  33
//I2C
#define SDA  21
#define SCL  22
//SAIDA GENERICA
#define D2  2
#define D4  4
#define D5  5
#define D15  15


class CarEsp32 {
  private:
    bool linha[5] = {false,false,false,false,false};
    long duracao;
    int velocidade = 150;
    float fatorAjusteMotorA = 1; //Fator de ajuste para calibrar motores para ter aproximadamente a mesma rotação
    float fatorAjusteMotorB = 1;
    bool linhaCorPreta = true;
    

  public:
  /**Inicializa a biblioteca */  
  CarEsp32();
  /**Retorna a distância */
    float getDistancia();
  /**Retorna a velocidade setada */
    int getVelocidade();
    /**Retorna o ID do Esp32 */
    String getID();
    /**Retorar um byte com os valores do sensores de linha 0 -31 */
    byte getSensoresLinha();
    /** Retorna True para o sensor na linha. Você deve informar o sensor que deseja.(SL1,SL2,SL3,SL4,SL5) */
    bool getSensorLinha(int sensor);
    /** Aciona os motores no sentidor informado para cada um com a velocidade informada */
    void acionarMotor(bool sentidoHorarioMotorA,bool sentidoHorarioMotorB, int velo);
    /** Aciona o motorA no sentido informado com a velocidade. O sentido pode alterar conforma a ligação do motor */
    void acionarMotorA(bool sentidoHorario, int velo);
    /** Aciona o motorB no sentido informado com a velocidade. O sentido pode alterar conforma a ligação do motor */
  	void acionarMotorB(bool sentidoHorario, int velo);
  	/** Para o motor A */
    void pararMotorA();
    /** Para o motor B */
  	void pararMotorB();
    /** Para o Motor A e Motor B */
    void pararMotor();

  	void moverFrente();
  	void moverAtras();
  	void moverDireita();
  	void moverEsquerda();
    /** Seta a velocidade padrão que o motor vai girar */
    void ajustarVelocidade(int velo);
    
    void setaMotorVelocidade();
    void calibrarMotorA(float fator);
    void calibrarMotorB(float fator);
    void setLinhaCorPreta(bool isCorPreta);
    
    
    
};

#endif
