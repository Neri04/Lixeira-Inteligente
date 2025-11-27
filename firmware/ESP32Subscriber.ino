// Incluir bibliotecas
#include <WiFi.h>
#include <PubSubClient.h>

// Definições e constantes
char SSIDName[] = "Wokwi-GUEST";
char SSIDPass[] = "";

char BrokerURL[] = "broker.hivemq.com";
char BrokerUserName[] = "";
char BrokerPassword[] = "";
char MQTTClientName[] = "RA10427342_SUB";
int BrokerPort = 1883;

// Tópico que receberá a distância
char Topico_Distancia[] = "RA10427342/Distancia";

// Variáveis globais
WiFiClient espClient;
PubSubClient clienteMQTT(espClient);

// Função para reconectar ao broker MQTT
void mqttReconnect() {
  while (!clienteMQTT.connected()) {
    Serial.println("Reconectando ao broker MQTT...");

    if (clienteMQTT.connect(MQTTClientName, BrokerUserName, BrokerPassword)) {
      Serial.println("Conectado!");
      clienteMQTT.subscribe(Topico_Distancia); // SUBSCRIBE aqui
    } else {
      Serial.print("Erro, rc=");
      Serial.println(clienteMQTT.state());
      Serial.println("Tentando novamente em 5 segundos...");
      delay(5000);
    }
  }
}

// Função callback
void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Mensagem recebida no tópico: ");
  Serial.println(topic);

  String payload = "";
  for (int i = 0; i < length; i++) {
    payload += (char)message[i];
  }
  Serial.print("Valor recebido: ");
  Serial.println(payload);

  // Converter para float
  float distancia = payload.toFloat();

  // Definir limite da lixeira cheia
  if (distancia <= 15.0) {
    Serial.println("Lixeira CHEIA → LED ON");
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    Serial.println("Lixeira OK → LED OFF");
    digitalWrite(LED_BUILTIN, LOW);
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);

  WiFi.begin(SSIDName, SSIDPass);
  Serial.print("Conectando ao Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  // Configurar MQTT
  clienteMQTT.setServer(BrokerURL, BrokerPort);
  clienteMQTT.setCallback(callback);
}

void loop() {
  if (!clienteMQTT.connected()) {
    mqttReconnect();
  }

  clienteMQTT.loop();
}
