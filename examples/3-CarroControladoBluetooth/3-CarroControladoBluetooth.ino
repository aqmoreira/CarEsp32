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


// Import required libraries
#include <BluetoothSerial.h> 
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Port Profile for Bluetooth is not available or not enabled. It is only available for the ESP32 chip.
#endif
#include <CarEsp32.h>

BluetoothSerial ESP_BT;

int comandoRecebido = 0;
CarEsp32 carEsp32;


//Nome do bluetooth
String nomeBLE = "CarPio-02" ;  //Mudar aqui o nome do Bluetooth 

int velocidade = 150; //Velocidade máxima 255
float calibragemMotorA = 1; 
float calibragemMotorB = 1; //Fator de ajuste para calibrar motores para ter aproximadamente a mesma rotação, ajustar com razão do motorA/motorB

void setup() {
  Serial.begin(115200);
  ESP_BT.begin(nomeBLE); 
  Serial.println("O carrinho foi ativado, agora pode parear o bluetooth:" + nomeBLE);

  carEsp32.calibrarMotorA(calibragemMotorA);
  carEsp32.calibrarMotorB(calibragemMotorB);
  Serial.println(carEsp32.getID());
 

 
 
}

void loop() {
  if(ESP_BT.available()){
    comandoRecebido = ESP_BT.read();

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

        case '0':
          carEsp32.pararMotor();
          break;

      }
    fflush(stdin);
    delay(20);
  }
}
