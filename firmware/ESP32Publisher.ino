// Incluir bibliotecas
#include <WiFi.h>
#include <PubSubClient.h>

//Definicoes e constantes
char SSIDName[] = "Wokwi-GUEST"; //nome da rede WiFi
char SSIDPass[] = ""; //senha da rede WiFI

#define TRIG_PIN 12   // Pino Trig conectado ao D12
#define ECHO_PIN 15   // Pino Echo conectado ao D15

char BrokerURL[] = "broker.hivemq.com"; //URL do broker MQTT
char BrokerUserName[] = ""; //nome do usuario para autenticar no broker MQTT
char BrokerPassword[] = ""; //senha para autenticar no broker MQTT
char MQTTClientName[] = "mqtt-mack-pub-sub"; //nome do cliente MQTT
int BrokerPort = 1883; //porta do broker MQTT

// Tópico MQTT
char Topico_Distancia[] = "RA10427342/Distancia";

// Objetos MQTT/WiFi
WiFiClient espClient;
PubSubClient clienteMQTT(espClient);

// Função para reconectar
void mqttReconnect() {
  while (!clienteMQTT.connected()) {
    Serial.println("Conectando-se ao broker MQTT...");
    if (clienteMQTT.connect(MQTTClientName, BrokerUserName, BrokerPassword)) {
      Serial.println("Conectado ao broker!");
    } else {
      Serial.print("Erro, rc=");
      Serial.println(clienteMQTT.state());
      Serial.println("Tentando novamente em 5 segundos...");
      delay(5000);
    }
  }
}

// Função para medir distância
float medirDistancia() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duracao = pulseIn(ECHO_PIN, HIGH);
  float distancia = duracao * 0.0343 / 2;  // em cm

  return distancia;
}

// Setup
void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  clienteMQTT.setServer(BrokerURL, BrokerPort);

  Serial.println("Conectando ao Wi-Fi...");
  WiFi.begin(SSIDName, SSIDPass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

// Loop principal
void loop() {
  if (!clienteMQTT.connected()) {
    mqttReconnect();
  }
  clienteMQTT.loop();

  float distancia = medirDistancia();

  char _d[10];
  dtostrf(distancia, 1, 2, _d);

  clienteMQTT.publish(Topico_Distancia, _d);
  Serial.print("Distância publicada: ");
  Serial.print(_d);
  Serial.println(" cm");

  delay(1000);
}
