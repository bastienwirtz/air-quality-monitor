#include "Cloud.h"

WiFiClientSecure espWifiClient;
PubSubClient mqtt(espWifiClient);

Cloud::Cloud(char *ssid, char *password, char *mqttServer, char *mqttUser, char *mqttPassword) {
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
  char *deviceid = "pmsensor";
  mqtt.connect(deviceid, this->mqttUser, this->mqttPassword);
  // delay(1); // Ensure the watchdog do not think the process is locked (avoid
  // reboot).

  bool connected = mqtt.connected();
  if (mqtt.connected()) {
    mqtt.publish("home/devices/connect", deviceid);
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

uint8_t Cloud::getStatus() { return WiFi.status(); }
