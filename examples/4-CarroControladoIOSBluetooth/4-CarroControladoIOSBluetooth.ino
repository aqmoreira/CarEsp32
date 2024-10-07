#include "BluetoothIOS.h"
#include <CarEsp32.h>
/*Carro controlado utilizando a placa CARESP32 via Bluetooth

   Objetivo: Controlar através do Bluetooth o carro utilizando uma app pelo celular.

    GamePad:    Aa              Ee
            Dd      Bb      Hh      Ff
                Cc              Gg

 0 - Quando é solto botão


   IOS: BLE Joystick
   ANDROID: Bluetooth RC Car

   1 - Ajustar o nome do carro bluetooth
   2 - Carregar para placa CARESP32 esta versão do software
   3 - Acessar pelo App e parear 
   4 -Se divertir

  
**/


int comandoRecebido = 0;
CarEsp32 carEsp32;

//Nome do bluetooth
String nomeBLE = "CarPio-01" ;  //Mudar aqui o nome do Bluetooth 

int velocidade = 150; //Velocidade máxima 255
float calibragemMotorA = 1; 
float calibragemMotorB = 1; //Fator de ajuste para calibrar motores para ter aproximadamente a mesma rotação, ajustar com razão do motorA/motorB


class MyCallbacks : public BLECharacteristicCallbacks {
  
  void onWrite(BLECharacteristic *pCharacteristic) {
    String rxValue = pCharacteristic->getValue();

    if (rxValue.length() > 0) {
      comandoRecebido = rxValue[0];
      Serial.println(comandoRecebido);
      switch (comandoRecebido){
        case 'A':   //frente
        case 'a':
          carEsp32.moverFrente();
          break;
        
        case 'B':  //direita
        case 'b':
          carEsp32.moverDireita();
          break;
        
        case 'C': //Atrás
        case 'c':
          carEsp32.moverAtras();
          break;

        case 'D': //Esquerda
        case 'd':
          carEsp32.moverEsquerda();
          break;

        case 'E':
        case 'e':
         //colocar aqui um efeito
          break;

        case 'F':
        case 'f':
          //colocar aqui um efeito
          break;

        case 'G':
        case 'g':
          //colocar aqui um efeito
          break;

        case 'H':
        case 'h':
          //colocar aqui um efeito
          break;

        case 0:
          carEsp32.pararMotor();
          break;

      }
    }
  }
};


void setup() {
  BLECharacteristicCallbacks *callback = new MyCallbacks();
  inicializaBLE(nomeBLE,callback);
 
  Serial.println("O carrinho foi ativado, agora pode parear o bluetooth: " + nomeBLE);

  carEsp32.calibrarMotorA(calibragemMotorA);
  carEsp32.calibrarMotorB(calibragemMotorB);
 
 
}
void loop() {
   loopBLE(); //loop para bluetooth
}
