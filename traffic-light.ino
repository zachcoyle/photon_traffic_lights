// This #include statement was automatically added by the Particle IDE.
#include "neopixel/neopixel.h"

// #define PIXEL_TYPE = NEO_GRB + NEO_KHZ800

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(4, D2, WS2812);

boolean androidIsTesting = false;
boolean iOSIsTesting = false;

boolean androidStatus = true;
boolean iOSStatus = true;

void setup() {
  pixels.begin();
  pixels.show(); // Initialize all pixels to 'off'
  
  Particle.function("androidBuild", androidBuilding);
  Particle.function("iOSBuild", iOSBuilding);
  
  Particle.function("androidDone", androidDoneBuilding);
  Particle.function("iOSDone", iOSDoneBuilding);
  
}

void loop() {}
// void loop() { pixels.show(); }

int iOSBuilding(String command){
    iOSIsTesting = true;
    updatePixels();
    return 0;
}

int androidBuilding(String command){
    Particle.publish("stats", "building");
    
    androidIsTesting = true;
    updatePixels();
    return 0;
}

int androidDoneBuilding(String command){
    androidIsTesting = false;
    androidStatus = command == "success";
    Particle.publish("ADEBUG", command);
    updatePixels();
    return 0;
}


int iOSDoneBuilding(String command){
    iOSIsTesting = false;
    iOSStatus = command == "success";
    updatePixels();
    return 0;
}

void updatePixels(){
    
    pixels.clear();
    
    if(androidIsTesting || iOSIsTesting){
        Particle.publish("DEBUG", "Build Testing");
        pixels.setPixelColor(1, pixels.Color(150,150,0));
        pixels.setPixelColor(2, pixels.Color(150,150,0));
    }
    
    else{
        
        if (iOSStatus && androidStatus){
            Particle.publish("DEBUG", "Build Passed!");
            pixels.setPixelColor(0, pixels.Color(0,150,0));
        }
        
        else{
            Particle.publish("DEBUG", "Build Failed");
            pixels.setPixelColor(3, pixels.Color(150,0,0));
        }
    }
    
    pixels.show();
}