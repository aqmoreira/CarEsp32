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
