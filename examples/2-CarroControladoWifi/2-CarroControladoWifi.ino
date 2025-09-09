/*Carro controlado utilizando a placa CARESP32

   Objetivo: Controlar através do WIFI o carro utilizando como controle o html apresentado ao acessar o IP.

   1 - Ajustar os dados de acesso ao WIFI
   2 - Carregar para placa CARESP32 esta versão do software
   3 - Abrir o monitor serial para ver o IP que ela conectou
   4 - Acessar por qualquer dispositovo conectado na mesma rede via navegador o IP apresentado
   5 -Se divertir

   Allan Moreira
**/

// Import required libraries
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <CarEsp32.h>
#include "Controle.h"

// Se desejar conectar em uma rede Wifi existente
const char* ssid = "NomedaRedeWifi";
const char* password = "#senhaRedewifi";

//Rede AP do CARRO caso não consiga entrar no WIFI
const char* ssidCar     = "8A-G8";
const char* passwordCar = "123456789";

int velocidade = 150; //Velocidade máxima 255
float calibragemMotorA = 1; //Fa1ator de ajuste para calibrar motores para ter aproximadamente a mesma rotação
float calibragemMotorB = 1; //Fator de ajuste para calibrar motores para ter aproximadamente a mesma rotação




// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
CarEsp32 carEsp32;



void notifyClients() {
  //ws.textAll(String(ledState));
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  String msg = "";
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {

    data[len] = 0;


    for (size_t i = 0; i < info->len; i++) {
      msg += (char) data[i];
    }
    processarComando(msg);
    Serial.printf("%s\n", msg.c_str());



    //    if (strcmp((char*)data, "toggle") == 0) {
    //      ledState = !ledState;
    //      notifyClients();
    //    }
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      {
        AwsFrameInfo *info = (AwsFrameInfo *)arg;
        if (info->final && info->index == 0 && info->len == len)
        {
          //the whole message is in a single frame and we got all of it's data
          if (info->opcode == WS_TEXT)
          {
            data[len] = 0;
            char *command = (char *)data;
            processarComando(command);
          }
        }
        break;
      }
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void processarComando(String command) {
  //Serial.print("cmd para processar:");
  Serial.println(command);
  if (command == "F") carEsp32.moverFrente();
  else if (command == "A") carEsp32.moverAtras();
  else if (command == "E") carEsp32.moverEsquerda();
  else if (command == "D") carEsp32.moverDireita();
  else if (command == "P") carEsp32.pararMotor();
  else {
    int veloci = command.toInt();
    if (veloci > 0 && veloci < 1023) {
      carEsp32.ajustarVelocidade(veloci);
    }

  }


}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

String processor(const String& var) {
  Serial.println(var);
  
  return String();
}

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);
  Serial.print("ID:");
  Serial.println(ssidCar);

  

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);

  //  while (WiFi.status() != WL_CONNECTED) {
  //    delay(1000);
  //    Serial.println("Connecting to WiFi..");
  //  }
  delay(2000);
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("*WiFi CONECTADO*");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    delay(2000);
  } else {
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssidCar, passwordCar);
    IPAddress myIP = WiFi.softAPIP();

    Serial.println("");
    Serial.println("**************************************");
    Serial.print("NÃO CONSEGUIU CONECTAR NO WIFI: ");
    Serial.println(ssid);
    Serial.println("***************************************");
    Serial.println("");
    Serial.print("*WIFI DO CARRO ATIVADO. CONECTE NA REDE:");
    Serial.println(ssidCar);
    Serial.print("SENHA:");
    Serial.println(passwordCar);
    Serial.print("CARRO ENDEREÇO IP: ");
    Serial.println(myIP);
    delay(2000);

    
  }


  initWebSocket();
 

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html, processor);
  });

  // Start server
  server.begin();
  carEsp32.calibrarMotorA(calibragemMotorA);
  carEsp32.calibrarMotorB(calibragemMotorB);
}

void loop() {
  ws.cleanupClients();

}
