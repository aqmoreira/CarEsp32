/**
Carro aceitas comandos através das chaves.
SW1 - SW2 - SW3 - SW4
Comandos:
  SW1 - Frente
  SW2 - Trás
  SW3 - Esquerda
  SW4 - Direita
  SW1 + SW4 - Executa os comandos da memória
  SW2 + SW3 - Limpa comandos da Memória

*/
#include <CarEsp32.h>
#define TotalComandos 40
int numItem = 0;
int caminho[TotalComandos];

int velocidade = 180;        //Velocidade máxima 255
float calibragemMotorA = 1;  //Fator de ajuste para calibrar motores para ter aproximadamente a mesma rotação
float calibragemMotorB = 1;  //Fator de ajuste para calibrar motores para ter aproximadamente a mesma rotação
CarEsp32 carEsp32;
void setup() {
  //put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(SW1, INPUT);  //SW1 - 35
  pinMode(SW2, INPUT);  //SW2 - 36
  pinMode(SW3, INPUT);  //SW3 - 39
  pinMode(SW4, INPUT);  //SW4 - 34
  pinMode(2, OUTPUT);
  numItem = 0;
  carEsp32.calibrarMotorA(calibragemMotorA);
  carEsp32.calibrarMotorB(calibragemMotorB);
  carEsp32.ajustarVelocidade(velocidade);
}

void loop() {
  //put your main code here, to run repeatedly:


  if (((analogRead(SW2) == 0) && (analogRead(SW3) == 0))) {  //SW2 e SW3
    numItem = 0;
    digitalWrite(2, true);
    Serial.println("Caminho Zerado");
    for (int i = 0; i < TotalComandos; i++) {
      caminho[i] = 0;
    }
    delay(.4 * 1000);
  } else if (((analogRead(SW1) == 0) && (analogRead(SW4) == 0))) {  //SW1 e SW4
    digitalWrite(2, true);
    delay(500);

    Serial.println("Caminho :");
    for (int i = 0; i < TotalComandos; i++) {
      if (caminho[i] != 0) {
        Serial.println(caminho[i]);
        switch (caminho[i]) {
          case 1:  //FRENTE
            Serial.println("Frente");
            carEsp32.moverFrente();
            delay(700);
            carEsp32.pararMotor();
            break;
          case 2:  //ATRAS
            Serial.println("Tras");
            carEsp32.moverAtras();
            delay(700);
            carEsp32.pararMotor();
            break;
          case 3:  //ESQUERDA
            Serial.println("Esquerda");
            carEsp32.moverEsquerda();
            delay(600);
            carEsp32.pararMotor();
            break;
          case 4:  //DIREITA
            Serial.println("Direita");
            carEsp32.moverDireita();
            delay(600);
            carEsp32.pararMotor();
            break;
        }
        delay(1000);
      }
      carEsp32.pararMotor();
    }
  } else {
    if ((analogRead(SW1) == 0)) {  //Frente
      Serial.println("SW1 Apertado - Frente");
      caminho[numItem++] = 1;
      digitalWrite(2, true);
      delay(.4 * 1000);
    }
    if ((analogRead(SW2) == 0)) {  //Trás
      Serial.println("SW2 Apertado - Trás");
      caminho[numItem++] = 2;
      digitalWrite(2, true);
      delay(.4 * 1000);
    }
    if ((analogRead(SW3) == 0)) {  //Esquerda
      caminho[numItem++] = 3;
      Serial.println("SW3 Apertado - Esquerda");
      digitalWrite(2, true);
      delay(.4 * 1000);
    }
    if ((analogRead(SW4) == 0)) {  //Direita
      caminho[numItem++] = 4;
      Serial.println("SW4 Apertado - Direita");
      digitalWrite(2, true);
      delay(.4 * 1000);
    }
  }
  digitalWrite(2, false);
  delay(.4 * 1000);
}
