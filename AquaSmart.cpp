#include <ESP8266WiFi.h> 
#include <PubSubClient.h>

#define pinReservatorio D1  
#define pinSensorAquario D2
#define pinRele   D4 

bool estadoAquario = 0;
bool estadoReserv = 0;

//WiFi
const char* SSID = "XXXX";       // SSID /Nome da rede Wifi
const char* PASSWORD = "XXXX";   // Senha da rede Wifi
WiFiClient wifiClient;                        
 
//MQTT Server
const char* BROKER_MQTT = "test.mosquitto.org"; //URL do broker MQTT 
int BROKER_PORT = 1883;                         // Porta do Broker MQTT

#define ID_MQTT  "BCI01"            
#define TOPIC_PUBLISH "Monitoramento/reservatorio"    
PubSubClient MQTT(wifiClient);        

//Declaração das Funções
void mantemConexoes();  
void conectaWiFi();     
void conectaMQTT();     
void enviaPacote();     

void setup() {
  pinMode(pinReservatorio, INPUT_PULLUP); 
  pinMode(pinSensorAquario, INPUT_PULLUP);
  pinMode(pinRele, OUTPUT);          

  Serial.begin(115200);

  conectaWiFi();
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);   
}

void loop() {
  mantemConexoes();
  enviaValores();
  MQTT.loop();


estadoAquario = digitalRead(pinSensorAquario);
estadoReserv = digitalRead(pinReservatorio);

//---Acionamento da bomba de recalque---

  //quando a boia do reservatorio está alta
  if (estadoReserv == 0) {
    Serial.println ("Nivel adequado");

     //Se a boia do aquario estiver baixa
     if (estadoAquario) {
        //O rele vai ligar
        digitalWrite(pinRele, 0);
        
        
     } else {
      //Caso contrario o rele vai desligar
        digitalWrite(pinRele, 1);
     }

    //Quando a boia do reservatorio estiver baixa   
  } else {
    //O rele vai desligar
     digitalWrite(pinRele, 1);
     Serial.println ("Nivel critico");
     //delay(3000);
     
  }
}

void mantemConexoes() {
    if (!MQTT.connected()) {
       conectaMQTT(); 
    }
    
    conectaWiFi(); //se não há conexão com o WiFI, a conexão é refeita
}

void conectaWiFi() {

  if (WiFi.status() == WL_CONNECTED) {
     return;
  }
        
  Serial.print("Conectando-se na rede: ");
  Serial.print(SSID);
  Serial.println("  Aguarde!");

  WiFi.begin(SSID, PASSWORD); // Conecta na rede WI-FI  
  while (WiFi.status() != WL_CONNECTED) {
      delay(100);
      Serial.print(".");
  }
  
  Serial.println();
  Serial.print("Conectado com sucesso, na rede: ");
  Serial.print(SSID);  
  Serial.print("  IP obtido: ");
  Serial.println(WiFi.localIP()); 
}

void conectaMQTT() { 
    while (!MQTT.connected()) {
        Serial.print("Conectando ao Broker MQTT: ");
        Serial.println(BROKER_MQTT);
        if (MQTT.connect(ID_MQTT)) {
            Serial.println("Conectado ao Broker com sucesso!");
        } 
        else {
            Serial.println("Noo foi possivel se conectar ao broker.");
            Serial.println("Nova tentatica de conexao em 10s");
            delay(10000);
        }
    }
}

//---Envia dados---
void enviaValores() {
static bool estadoReservatorio = 0;
static bool estadoReservatorioAnt = 0;


  estadoReservatorio = digitalRead(pinReservatorio);
  
     if (!estadoReservatorio && estadoReservatorioAnt) {

        //Botao Apertado     
        MQTT.publish(TOPIC_PUBLISH, "Nivel adequado");
        Serial.println("Boia alta. Payload enviado.");
        

     } else if (estadoReservatorio && !estadoReservatorioAnt) {

        //Botao Solto
        MQTT.publish(TOPIC_PUBLISH, "Nivel critico");
        Serial.println("Boia baixa. Payload enviado.");
        
     }
     
  
  estadoReservatorioAnt = estadoReservatorio;
}







