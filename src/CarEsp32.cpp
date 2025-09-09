// CarEsp32.cpp

#include "CarEsp32.h"
 long duracao;
  // Setting PWM properties
const int freq = 30000;
const int pwmChannel = 0;
const int pwmChannel1 = 1;
const int resolution = 8;
 
CarEsp32::CarEsp32(){
  
  //Sensores Linha
  pinMode( SL1, INPUT);
  pinMode( SL2, INPUT);
  pinMode( SL3, INPUT);
  pinMode( SL4, INPUT);
  pinMode( SL5, INPUT);
  //chaves
  pinMode( SW1, INPUT_PULLUP); // CORRIGIDO: INPUT_PULLUP para botoes
  pinMode( SW2, INPUT_PULLUP); // CORRIGIDO: INPUT_PULLUP para botoes
  pinMode( SW3, INPUT_PULLUP); // CORRIGIDO: INPUT_PULLUP para botoes
  pinMode( SW4, INPUT_PULLUP); // CORRIGIDO: INPUT_PULLUP para botoes
  //Ultrasonico
  pinMode(TRG, OUTPUT);
  pinMode(ECO, INPUT);
  //Motor
  pinMode(MOTOR_A_EN, OUTPUT);
  pinMode(MOTOR_A_IN1, OUTPUT);
  pinMode(MOTOR_A_IN2, OUTPUT);
  //MOTOR_B
  pinMode(MOTOR_B_EN, OUTPUT);
  pinMode(MOTOR_B_IN1, OUTPUT);
  pinMode(MOTOR_B_IN2, OUTPUT);

 // configure LEDC PWM
  ledcAttachChannel(MOTOR_A_EN, freq, resolution, pwmChannel);
  ledcAttachChannel(MOTOR_B_EN, freq, resolution, pwmChannel1);


 

    // inicializa a velocidade padrão 150 (motores amarelo dc)
    velocidade = 150; 
   

}


/**Retorna a distância em cm */
 float CarEsp32::getDistancia(){
      digitalWrite(TRG, LOW);
      delayMicroseconds(2);
      // Seta o pino TRG para estado HIGH por 10 microsegundos
      digitalWrite(TRG, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRG, LOW);
      
      // Ler no pino  ECO, retorna o tempo que levou para retornar o som
      duracao = pulseIn(ECO, HIGH);
      
      // Calculate the distance
      float distanciaCm = duracao * VELOCIDADE_SOM/2;
      return distanciaCm;
  }
/** Retorna um ID da placa */ 
  String CarEsp32::getID(){
    char ssid[23];
    snprintf(ssid, 23, "MCUDEVICE-%llX", ESP.getEfuseMac());
    return String(ssid);
  }

 /** Retorna um byte com os valores do sensores */   
 byte CarEsp32::getSensoresLinha(){

    byte linha = 0;
    if(linhaCorPreta){ // Linha Preta em Fundo Branco (LOW = Preto = na linha)
    
      if( digitalRead(SL1) == LOW){
        bitSet(linha,0);
      }
      if( digitalRead(SL2) == LOW){
        bitSet(linha,1);
      }
      if( digitalRead(SL3) == LOW){
        bitSet(linha,2);
      }
      if( digitalRead(SL4) == LOW){
        bitSet(linha,3);
      }
      if( digitalRead(SL5) == LOW){
        bitSet(linha,4);
      }
    }else{ // Linha Branca em Fundo Preto (HIGH = Branco = na linha)
       if( digitalRead(SL1) == HIGH){
        bitSet(linha,0);
      }
      if( digitalRead(SL2) == HIGH){
        bitSet(linha,1);
      }
      if( digitalRead(SL3) == HIGH){
        bitSet(linha,2);
      }
      if( digitalRead(SL4) == HIGH){
        bitSet(linha,3);
      }
      if( digitalRead(SL5) == HIGH){
        bitSet(linha,4);
      }
    }

    return linha;
  }
  /** Retorna o status do sensor de linha */
  bool CarEsp32::getSensorLinha(int sensor){
    
    bool sensorStatus = false;
       
    if(linhaCorPreta){ // Linha Preta em Fundo Branco (LOW = Preto = na linha)
      if( digitalRead(sensor) == LOW){
        sensorStatus = true;
      }
    } else{ // Linha Branca em Fundo Preto (HIGH = Branco = na linha)
      if( digitalRead(sensor) == HIGH){
       sensorStatus = true;
      }
     }
     return sensorStatus;
  }

/**Aciona o motor A e motor B com determinado sentido e velocidade */
void CarEsp32::acionarMotor(bool sentidoHorarioMotorA,bool sentidoHorarioMotorB, int velo){
  digitalWrite(MOTOR_A_IN1,sentidoHorarioMotorA);
  digitalWrite(MOTOR_A_IN2,!sentidoHorarioMotorA);
  digitalWrite(MOTOR_B_IN1,sentidoHorarioMotorB);
  digitalWrite(MOTOR_B_IN2,!sentidoHorarioMotorB);
  
  ledcWrite(MOTOR_A_EN, velo*fatorAjusteMotorA);
  ledcWrite(MOTOR_B_EN, velo*fatorAjusteMotorB);
}
    
/** Aciona o motor A com sentido e velocidade */
void CarEsp32::acionarMotorA(bool sentidoHorario, int velo){
  digitalWrite(MOTOR_A_IN1,sentidoHorario);
  digitalWrite(MOTOR_A_IN2,!sentidoHorario);
  ledcWrite(MOTOR_A_EN, velo*fatorAjusteMotorA);
}

/** Aciona o motor B com sentido e velocidade */
void CarEsp32::acionarMotorB(bool sentidoHorario, int velo){
  digitalWrite(MOTOR_B_IN1,sentidoHorario);
  digitalWrite(MOTOR_B_IN2,!sentidoHorario);
  ledcWrite(MOTOR_B_EN, velo*fatorAjusteMotorB);
}

/** Para o Motor A */
void CarEsp32::pararMotorA(){
    digitalWrite(MOTOR_A_IN1, LOW);
    digitalWrite(MOTOR_A_IN2, LOW);
    ledcWrite(MOTOR_A_EN, 0); // CORRIGIDO: Zera o PWM
}
/** Para o Motor B */
void CarEsp32::pararMotorB(){
    digitalWrite(MOTOR_B_IN1, LOW);
    digitalWrite(MOTOR_B_IN2, LOW);
    ledcWrite(MOTOR_B_EN, 0); // CORRIGIDO: Zera o PWM
}

/** Para os dois motores */
void CarEsp32::pararMotor(){
    digitalWrite(MOTOR_A_IN1, LOW);
    digitalWrite(MOTOR_A_IN2, LOW);
    digitalWrite(MOTOR_B_IN1, LOW);
    digitalWrite(MOTOR_B_IN2, LOW);
    ledcWrite(MOTOR_A_EN, 0); // CORRIGIDO: Zera o PWM do motor A
    ledcWrite(MOTOR_B_EN, 0); // CORRIGIDO: Zera o PWM do motor B
    
}

/** move os motores para frente */
void CarEsp32::moverFrente(){
    digitalWrite(MOTOR_A_IN1, LOW);
    digitalWrite(MOTOR_A_IN2, HIGH);
    digitalWrite(MOTOR_B_IN1, LOW);
    digitalWrite(MOTOR_B_IN2, HIGH);
    ledcWrite(MOTOR_A_EN, velocidade*fatorAjusteMotorA);
    ledcWrite(MOTOR_B_EN, velocidade*fatorAjusteMotorB);
}

/** Move os motores para trás */
void CarEsp32::moverAtras(){
    digitalWrite(MOTOR_A_IN1, HIGH);
    digitalWrite(MOTOR_A_IN2, LOW);
    digitalWrite(MOTOR_B_IN1, HIGH);
    digitalWrite(MOTOR_B_IN2, LOW);
    // CORRIGIDO: Adiciona o PWM aqui
    ledcWrite(MOTOR_A_EN, velocidade*fatorAjusteMotorA);
    ledcWrite(MOTOR_B_EN, velocidade*fatorAjusteMotorB);
}

/** Mover para Direita */
void CarEsp32::moverDireita(){
    digitalWrite(MOTOR_A_IN1, HIGH);
    digitalWrite(MOTOR_A_IN2, LOW);
    digitalWrite(MOTOR_B_IN1, LOW);
    digitalWrite(MOTOR_B_IN2, HIGH);
    // CORRIGIDO: Adiciona o PWM aqui
    ledcWrite(MOTOR_A_EN, velocidade*fatorAjusteMotorA);
    ledcWrite(MOTOR_B_EN, velocidade*fatorAjusteMotorB);
}
/** Mover para Esquerda */
void CarEsp32::moverEsquerda(){
    digitalWrite(MOTOR_A_IN1, LOW);
    digitalWrite(MOTOR_A_IN2, HIGH);
    digitalWrite(MOTOR_B_IN1, HIGH);
    digitalWrite(MOTOR_B_IN2, LOW);
    // CORRIGIDO: Adiciona o PWM aqui
    ledcWrite(MOTOR_A_EN, velocidade*fatorAjusteMotorA);
    ledcWrite(MOTOR_B_EN, velocidade*fatorAjusteMotorB);
}
/** Liga o carro com a velocidade ajustada anteriormente*/
 void CarEsp32::setaMotorVelocidade()
  {
    // Esta funcao usa a variavel de velocidade INTERNA da classe CarEsp32
    Serial.print("Potência:");
    Serial.print(velocidade);
    Serial.print(" Motor A:");
    Serial.print(velocidade*fatorAjusteMotorA);
    Serial.print(" Motor B:");
    Serial.println(velocidade*fatorAjusteMotorB);
    
    ledcWrite(MOTOR_A_EN, velocidade*fatorAjusteMotorA);
    ledcWrite(MOTOR_B_EN, velocidade*fatorAjusteMotorB);
    
  }

/** Ajustar a velocidade dos motores */
void CarEsp32::ajustarVelocidade(int velo){
  if(velo != velocidade){
    velocidade = velo;
    Serial.print("Potência:");
    Serial.print(velo);
    Serial.print(" Motor A:");
    Serial.print(velocidade*fatorAjusteMotorA);
    Serial.print(" Motor B:");
    Serial.println(velocidade*fatorAjusteMotorB);
  }

}
/** Configura o valor para calibrar o motor A na velocidade */
void CarEsp32::calibrarMotorA(float fator){
  fatorAjusteMotorA = fator;
}
/** Configura o valor para calibrar o motor B na velocidade */
void CarEsp32::calibrarMotorB(float fator){
  fatorAjusteMotorB = fator;
}

/** Seta o tipo de linha. True - Linha Preta , False - Linha Branca */
void CarEsp32::setLinhaCorPreta(bool isCorPreta){
   linhaCorPreta = isCorPreta;
   Serial.print("Linha Preta:");
   Serial.println(linhaCorPreta);
}