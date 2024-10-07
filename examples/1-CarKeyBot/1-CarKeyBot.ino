#include <CarEsp32.h>
#define TotalComandos  40
int numItem = 0;
int caminho[TotalComandos];

int velocidade = 400; //Velocidade máxima 1023
float calibragemMotorA = 1; //Fator de ajuste para calibrar motores para ter aproximadamente a mesma rotação
float calibragemMotorB = 1; //Fator de ajuste para calibrar motores para ter aproximadamente a mesma rotação
CarEsp32 carEsp32;
void setup() {
  //put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(36, INPUT);
  pinMode(39, INPUT);
  pinMode(35, INPUT);
  pinMode(34, INPUT);
  pinMode(2, OUTPUT);
  numItem = 0;
  carEsp32.calibrarMotorA(calibragemMotorA);
  carEsp32.calibrarMotorB(calibragemMotorB);
  carEsp32.ajustarVelocidade(velocidade);


}

void loop() {
  //put your main code here, to run repeatedly:


  if (((analogRead(36) == 0) && (analogRead(39) == 0))) {
    numItem = 0;
    digitalWrite(2, true);
    Serial.println("Caminho Zerado");
    for (int i = 0; i < TotalComandos; i++) {
      caminho[i] = 0;
      
    }
    delay(.4 * 1000);
  } else if (((analogRead(35) == 0) && (analogRead(34) == 0))) {
    digitalWrite(2, true);
    delay(500);
      
    Serial.println("Caminho :");
    for (int i = 0; i < TotalComandos; i++) {
      if (caminho[i] != 0) {
        Serial.println(caminho[i]);
        switch(caminho[i]){
          case 1:
              Serial.println("Frente");
              carEsp32.moverFrente();
              delay(700);
              carEsp32.pararMotor();
              break;
          case 2:
              Serial.println("Atras");
              carEsp32.moverAtras();
              delay(700);
              carEsp32.pararMotor();
              break;
          case 3:
              Serial.println("Esquerda");
              carEsp32.moverEsquerda();
              delay(350);
              carEsp32.pararMotor();
              break;
          case 4:
              Serial.println("Direita");
              carEsp32.moverDireita();
              delay(350);
              carEsp32.pararMotor();
              break;
        }
        delay(1000);
      }
      carEsp32.pararMotor();
      
    }
  } else {
    if ((analogRead(35) == 0)) {
      Serial.println("SW1 Apertado");
      caminho[numItem++] = 1;
      digitalWrite(2, true);
      delay(.4 * 1000);
    }
    if ((analogRead(36) == 0)) {
      Serial.println("SW2 Apertado");
      caminho[numItem++] = 2;
      digitalWrite(2, true);
      delay(.4 * 1000);
    }
    if ((analogRead(39) == 0)) {
      caminho[numItem++] = 3;
      Serial.println("SW3 Apertado");
      digitalWrite(2, true);
      delay(.4 * 1000);
    }
    if ((analogRead(34) == 0)) {
      caminho[numItem++] = 4;
      Serial.println("SW4 Apertado");
      digitalWrite(2, true);
      delay(.4 * 1000);
    }
  }
  digitalWrite(2, false);
  delay(.4 * 1000);
}
