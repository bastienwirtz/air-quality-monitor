#include "Cloud.h"

Cloud::Cloud(char *ssid, char *password)
{
    this->ssid = ssid;
    this->password = password;
}

bool Cloud::connect()
{
    WiFi.begin(this->ssid, this->password);
    WiFi.disconnect();
    WiFi.begin(this->ssid, this->password);

    int8_t timeout = 5;
    while (WiFi.status() != WL_CONNECTED && timeout > 0) 
    {
        // Loop until the connection is established
        timeout--;
        delay(1000);
    }
    return WiFi.status() == WL_CONNECTED;
}

void Cloud::send()
{
    
}

uint8_t Cloud::getStatus()
{
    WiFi.status();
}
