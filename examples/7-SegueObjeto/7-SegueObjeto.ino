/*Carro controlado utilizando a placa CARESP32

   Objetivo: Carro detecta objeto e mantem uma distancia.

   1 - Ajustar a distancia do objeto. 
   2 - Ajustar velocidade
   3 -Se divertir

   Allan Moreira e Allisson Moreira
**/


#include <CarEsp32.h>

//Definir variaveis
int distanciaCm = 0;  //variável que armazena a leitura do sensor
int velocidade = 800; //Velocidade máxima 1023
int distanciaManter = 20; //Valor da distância que deseja manter do objeto


CarEsp32 carEsp32;  //Variável do Tipo CarEsp32 que é placa que controla o carro

//A função setup é executado apenas uma vez ao ligar ou após reset
void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);
  Serial.print("CARRO MODO AUTONÔMO MANTER DISTÂNCIA");
  Serial.println("");
  Serial.print("Manter Distância de:");
  Serial.print(distanciaManter);
  Serial.print("Velocidade:");
  Serial.print(velocidade);
  //Ajusta a velocidade dos motores para o valor configurado na variável velocidade
  carEsp32.ajustarVelocidade(velocidade);
    
}

//A função loop fica se repetindo enquanto estiver ligada a placa.
void loop() {
  //Faz a leitura da distância de algum objeto na frente do sensor e armazena na variável
  distanciaCm = carEsp32.getDistancia();  
  //Imprime no console serial a distancia lida
  Serial.print("Distancia:");
  Serial.println(distanciaCm);

  
   //Verifica SE a distância lida é menor que distância DistanciaManter 
  if(distanciaCm < distanciaManter &&  distanciaCm >0){ //Se a condição for verdadeira executa as próximas intruções
    carEsp32.moverAtras();
   }
  
  //Verifica SE a distância lida é muito maior que distância DistanciaManter 
  if(distanciaCm > (distanciaManter+3) &&  distanciaCm < (distanciaManter+20)){ //Se a condição for verdadeira executa as próximas intruções
    carEsp32.moverFrente();
   }

 //SE não foi detectado nenhum vira a direita e procura
  if(distanciaCm > (distanciaManter+20)){ //Se a condição for verdadeira executa as próximas intruções
    carEsp32.moverDireita();
  }

  //SE objeto estiver próximo da distancia configurada 
  if(distanciaCm >= distanciaManter && distanciaCm <= (distanciaManter+3)){ //Se a condição for verdadeira executa as próximas intruções
    carEsp32.pararMotor();
  }
    
    

}
