/*Carro controlado utilizando a placa CARESP32

   Objetivo: Carro andar e evitar batida.

   1 - Ajustar a distancia para fazer a curva. dados de acesso ao WIFI
   2 - Ajustar velocidade
   3 -Se divertir

   Allan Moreira e Allisson Moreira
**/


#include <CarEsp32.h>

//Definir variaveis
int distanciaCm = 0;  //variável que armazena a leitura do sensor
int velocidade = 400; //Velocidade máxima 1023
int distanciaSegura = 20; //Valor da distância segura


CarEsp32 carEsp32;  //Variável do Tipo CarEsp32 que é placa que controla o carro

//A função setup é executado apenas uma vez ao ligar ou após reset
void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);
  Serial.print("CARRO MODO AUTONÔMO EVITANDO BATIDA");
  Serial.println("");
  Serial.print("Distância de segurança:");
  Serial.print(distanciaSegura);
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

  //Verifica SE a distância lida é menor ou igual a Distância Segura
  if(distanciaCm <= distanciaSegura){ //Se a condição for verdadeira executa as próximas intruções
    
    carEsp32.moverDireita();  //move o carro para direita
    delay(400);               //Espera 400 milisegundos
    carEsp32.moverFrente();   //Mode o carro para frente
   
  }

}
