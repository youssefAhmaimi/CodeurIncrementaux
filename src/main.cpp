#include <Arduino.h>
#include <ESP32Encoder.h> // https://github.com/madhephaestus/ESP32Encoder.git 
 
#define CLK 13 // CLK ENCODER 
#define DT 15 // DT ENCODER 
 
ESP32Encoder encoderGauche;
ESP32Encoder encoderDroit;
void setup () { 
  encoderGauche.attachHalfQuad ( DT, CLK );
  encoderGauche.setCount ( 0 );
  Serial.begin ( 115200 );
}
 
void loop () {    
  long newPosition = encoderGauche.getCount() / 2;
  Serial.println(newPosition);
} 