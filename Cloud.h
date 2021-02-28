#include <PubSubClient.h>
#include <WiFiClientSecure.h>

#ifndef AQM_CLOUD
#define AQM_CLOUD

class Cloud {
private:
  char *name;
  char *ssid;
  char *password;
  char *mqttServer;
  char *mqttUser;
  char *mqttPassword;

public:
  Cloud(char *name, char *ssid, char *password, char *mqttServer, char *mqttUser, char *mqttPassword);
  bool connect();
  bool mqttConnect();
  void send(char *topic, const char *message);
  void sendEvent(char* event);
};

#endif
