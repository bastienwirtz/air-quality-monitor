Usefull ressources

https://github.com/Bodmer/TFT_eSPI/tree/master/examples
https://diyprojects.io/ttgo-t-watch-get-started-esp32-tft_espi-library/
color-setting-and-text-display-esp32-learning-tour-arduino-version.html
https://github.com/Xinyuan-LilyGO/TTGO-T-Display
https://cdn.sparkfun.com/assets/2/d/2/a/6/Sensirion_SPS30_Particulate_Matter_Sensor_v0.9_D1__1_.pdf

https://forum.airnowtech.org/t/the-aqi-equation/169
https://www.epa.gov/sites/production/files/2014-05/documents/zell-aqi.pdf
https://forum.airnowtech.org/t/aqi-calculations-overview-ozone-pm2-5-and-pm10/168


[]

## Bill of materials


## Build

1. Configure the card
Arduino/libraries/TFT_eSPI/User_Setup_Select.h
//#include <User_Setup.h>
#include <User_Setups/Setup25_TTGO_T_Display.h>

Make sure to include the repository directory to your include path. 
Exemple for `vscode`: 

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
