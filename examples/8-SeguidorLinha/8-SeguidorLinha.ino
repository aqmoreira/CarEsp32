/*Carro controlado utilizando a placa CARESP32

   Objetivo: Seguir uma linha e parar no final quando encontrar a faixa

   1 - Nome dos Sensores de linha
    SL1 - Sensor Linha 1
    SL2 - Sensor Linha 2
    SL3 - Sensor Linha 3
    SL4 - Sensor Linha 4
    SL5 - Sensor Linha 5
    
   2 - Ajustar velocidade
   3 -Se divertir

   Allan Moreira e Allisson Moreira
**/


#include <CarEsp32.h>

//Definir variaveis
int velocidade = 150; //Velocidade máxima 1023
float calibragemMotorA = .85; //Fator de ajuste para calibrar motores para ter aproximadamente a mesma rotação
float calibragemMotorB = 1; //Fator de ajuste para calibrar motores para ter aproximadamente a mesma rotação



CarEsp32 carEsp32;  //Variável do Tipo CarEsp32 que é placa que controla o carro

//A função setup é executado apenas uma vez ao ligar ou após reset
void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);
  Serial.print("CARRO SEGUIDOR DE LINHA");
  Serial.println("");
  
  Serial.print("Velocidade:");
  Serial.print(velocidade);
  //Ajusta a velocidade dos motores para o valor configurado na variável velocidade
  carEsp32.ajustarVelocidade(velocidade);
  carEsp32.calibrarMotorA(calibragemMotorA);
  carEsp32.calibrarMotorB(calibragemMotorB);
    
}

//A função loop fica se repetindo enquanto estiver ligada a placa.
void loop() {
  Serial.print("SL1:");
  Serial.print(carEsp32.getSensorLinha(SL1));
  Serial.print("\t");
  Serial.print("SL2:");
  Serial.print(carEsp32.getSensorLinha(SL2));
  Serial.print("\t");
  Serial.print("SL3:");
  Serial.print(carEsp32.getSensorLinha(SL3));
  Serial.print("\t");
  Serial.print("SL4:");
  Serial.print(carEsp32.getSensorLinha(SL4));
  Serial.print("\t");
  Serial.print("SL5:");
  Serial.print(carEsp32.getSensorLinha(SL5));
  Serial.println(".");

  if(carEsp32.getSensorLinha(SL1)== true && carEsp32.getSensorLinha(SL3) == false){
    carEsp32.moverDireita();
  }

  if(carEsp32.getSensorLinha(SL1)== false && carEsp32.getSensorLinha(SL3) == true){
    carEsp32.moverEsquerda();
  }
  if(carEsp32.getSensorLinha(SL1)== false && carEsp32.getSensorLinha(SL3) == false){
    carEsp32.moverFrente();
  }

  if(carEsp32.getSensorLinha(SL1)== true && carEsp32.getSensorLinha(SL3) == true){
    carEsp32.pararMotor();
  }
  delay(80);
  carEsp32.pararMotor();
  delay(100);
  



  
  
  

}
