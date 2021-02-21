# Air quality monitor

Connected Particle matter, eCO2 & TVOC air quality monitor.

Features: 
- Particle matter monitoring (PM1, PM12.5, PM4, PM10)
- eCO2 / TVOC monitoring
- MQTT connectivity

## Parts

- [LILYGO® TTGO T-Display ESP32](http://www.lilygo.cn/prod_view.aspx?TypeId=50033&Id=1126&FId=t3:50033:3)
- [Particulate Matter Sensor SPS30](https://www.sensirion.com/en/environmental-sensors/particulate-matter-sensors-pm25/)
- [SGP30 Air Quality Sensor](https://shop.pimoroni.com/products/sgp30-air-quality-sensor-breakout)

## Wiring

Both SPS & SGP sensor are connected to the I2C bus (pin 21 & 22)


## Build

### Dependencies

- [Button2](https://github.com/LennartHennigs/Button2)
- [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI)
- [PubSubClient](https://github.com/knolleary/pubsubclient)
- [WiFiClientSecure](https://github.com/espressif/arduino-esp32/tree/master/libraries/WiFiClientSecure)
- [Adafruit_SGP30](https://github.com/adafruit/Adafruit_SGP30)
- [arduino-sps](https://github.com/Sensirion/arduino-sps)

### Configuration

**Display:**  
The `TFT_eSPI` needs to be configured for TTGo board / screen. Edit the `<your-TFT_eSPI-library-path>/User_Setup_Select.h`:

```c
//#include <User_Setup.h>
#include <User_Setups/Setup25_TTGO_T_Display.h>
```

**Connectivity:**  
Edit the configuration section of the `main.ino` file according to your needs:

```c
// Configuration
char* wifiSsid = "your-ssid";
char* wifiPassword = "your-wifi-password";
char* mqttServer = "your-mqtt.server";
char* mqttUser = "your-mqtt-user";
char* mqttPassword = "your-mqtt-password";
```

**Compiler:**  
Make sure to include the repository directory to your compiler include path.
Example for `vscode`: 

```json
// .vscode/c_cpp_properties.json (inside the source directory)
"configurations": [
        {
            "includePath": [
                ...
                "${workspaceFolder}",
            ],
            ...
        }
    ],
    ...
}
```


# References

- https://github.com/Bodmer/TFT_eSPI/tree/master/examples
- https://github.com/Xinyuan-LilyGO/TTGO-T-Display
- https://cdn.sparkfun.com/assets/2/d/2/a/6/Sensirion_SPS30_Particulate_Matter_Sensor_v0.9_D1__1_.pdf
- https://forum.airnowtech.org/t/the-aqi-equation/169
- https://www.epa.gov/sites/production/files/2014-05/documents/zell-aqi.pdf
- https://forum.airnowtech.org/t/aqi-calculations-overview-ozone-pm2-5-and-pm10/168
