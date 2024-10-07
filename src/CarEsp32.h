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
    

  public:
    CarEsp32();
    float getDistancia();
    int getVelocidade();
    String getID();
    byte getSensoresLinha();
    bool getSensorLinha(int sensor);
    void acionarMotor(bool sentidoHorarioMotorA,bool sentidoHorarioMotorB, int velo);
    void acionarMotorA(bool sentidoHorario, int velo);
  	void acionarMotorB(bool sentidoHorario, int velo);
  	void pararMotorA();
  	void pararMotorB();
  	void moverFrente();
  	void moverAtras();
  	void moverDireita();
  	void moverEsquerda();
    void ajustarVelocidade(int velo);
    void pararMotor();
    void setaMotorVelocidade();
    void calibrarMotorA(float fator);
    void calibrarMotorB(float fator);
    
    
    
};

#endif
