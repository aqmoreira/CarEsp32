# CarEsp32

É uma placa que server de suporte para ESP32 DEV Kit V1 30 pinos, para conectar sensores como sensor de linha, sensor ultrasônico, sensor i2c, tem já os pinos para controle de uma ponte H (L298N), pinos específico para sensor de linha para carrinho seguidor, 4 chaves táctil para programação. Alguns linos para uso genérico.
<p align="center">

</p>
Required : 

## Features
Carro controlado utilizando a placa CARESP32
  
    Nome dos Sensores de linha: SL1,SL2,SL3,SL4,SL5
    Nome das Chaves: SW1, SW2, SW3, SW4

```c++
    //Acionar MotorA:
      carEsp32.acionarMotorA(false,  velocidade); //avança
      carEsp32.acionarMotorA(true,  velocidade);  //retrocede
    //Acionar MotorB:
      carEsp32.acionarMotorB(false,  velocidade); //avança
      carEsp32.acionarMotorB(true,  velocidade);  //retrocede
    //Parar Motor:
      carEsp32.pararMotor();  //Para o motor A e B
      carEsp32.pararMotorA();  //Para o motor A
      carEsp32.pararMotorB();  //Para o motor B
   // Ler o Sensor Linha:
      carEsp32.getSensorLinha(SL2)
      Exemplo de uso se SL1 e SL3 é true, para os motores:
      if(carEsp32.getSensorLinha(SL1) == true 
          && carEsp32.getSensorLinha(SL3) == true){
            carEsp32.pararMotor();  
      }
```

## Quickstart

### CarEsp32 

Um simples exemplo de uso

```c++
/**
 * Programa de teste da placa CARESP 32
 * 1 - Testar chave 
 * 2- Testar Ultrasonico
 * 3 - Entrada Sensores de Linha
 * Allan Moreira e Allisson Moreira
 */
#include <CarEsp32.h>



int chaveEstado = 0;
bool linha[5] = {false,false,false,false,false};
CarEsp32 carEsp32;
void setup() {
  Serial.begin(115200);
 
  Serial.print("ID:");
  Serial.println(carEsp32.getID());
  

}

void loop() {
  Serial.print("Distancia:");
  Serial.println(carEsp32.getDistancia());
  
  chaveEstado = digitalRead(SW1);
  if( chaveEstado == LOW){
    Serial.println("SW1 - Apertado");
  }
  chaveEstado = digitalRead(SW2);
  if( chaveEstado == LOW){
    Serial.println("SW2 - Apertado");
  }
  chaveEstado = digitalRead(SW3);
  if( chaveEstado == LOW){
    Serial.println("SW3 - Apertado");
  }
  chaveEstado = digitalRead(SW4);
  if( chaveEstado == LOW){
    Serial.println("SW4 - Apertado");
  }

  chaveEstado = digitalRead(SL1);
  if( chaveEstado == LOW){
    linha[0] = false;
  }else{
    linha[0] = true;
  }
  chaveEstado = digitalRead(SL2);
  if( chaveEstado == LOW){
    linha[1] = false;
  }else{
    linha[1] = true;
  }
  chaveEstado = digitalRead(SL3);
  if( chaveEstado == LOW){
    linha[2] = false;
  }else{
    linha[2] = true;
  }
  chaveEstado = digitalRead(SL4);
  if( chaveEstado == LOW){
    linha[3] = false;
  }else{
    linha[3] = true;
  }
  chaveEstado = digitalRead(SL5);
  if( chaveEstado == LOW){
    linha[4] = false;
  }else{
    linha[4] = true;
  }

  Serial.println("Linhas:");
  for(byte i=0; i<sizeof(linha); i++){
    Serial.print(linha[i]);
  }
  Serial.println("");


  

  delay(500);
}

```
