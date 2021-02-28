#include "Cloud.h"

WiFiClientSecure espWifiClient;
PubSubClient mqtt(espWifiClient);

Cloud::Cloud(char *name, char *ssid, char *password, char *mqttServer, char *mqttUser, char *mqttPassword) {
  this->name = name;
  this->ssid = ssid;
  this->password = password;
  this->mqttServer = mqttServer;
  this->mqttUser = mqttUser;
  this->mqttPassword = mqttPassword;
}

bool Cloud::connect() {
  WiFi.begin(this->ssid, this->password);

  int8_t timeout = 5;
  while (WiFi.status() != WL_CONNECTED && timeout > 0) {
    // Loop until the connection is established
    timeout--;
    delay(1000);
  }

  mqtt.setServer(this->mqttServer, 8883);
  this->mqttConnect();
  return WiFi.status() == WL_CONNECTED;
}

bool Cloud::mqttConnect() {
  mqtt.connect(this->name, this->mqttUser, this->mqttPassword);
  mqtt.setBufferSize(512);
  bool connected = mqtt.connected();
  if (mqtt.connected()) {
    this->sendEvent("connected");
  }
  return mqtt.connected();
}

void Cloud::send(char *topic, const char *message) {
  if (WiFi.status() != WL_CONNECTED) {
    return;
  }

  if (!mqtt.connected()) {
    mqttConnect();
  }

  if (mqtt.connected()) {
    mqtt.publish(topic, message);
  }
}

void Cloud::sendEvent(char* event) {
    char messageBuffer[255];
    sprintf(messageBuffer, "{\"device\":\"%s\", \"event\": \"%s\"}", this->name, event);
    mqtt.publish("home/devices/event", messageBuffer);
}
