#include <WiFi.h>

#ifndef AQM_CLOUD
#define AQM_CLOUD

class Cloud {
    private:
        char *ssid;
        char *password;
        
    public:
        Cloud(char *ssid, char *password);
        bool connect();
        void send();
        uint8_t getStatus();
};

#endif
