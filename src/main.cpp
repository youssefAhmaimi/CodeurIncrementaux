#include <Arduino.h>

// =========================
// ENCODEUR GAUCHE
// =========================
#define CLK_L 35
#define DT_L  34

volatile long encoderLeftCount = 0;
volatile int lastCLK_L = 0;

void IRAM_ATTR handleEncoderLeft() {
  int clkState = digitalRead(CLK_L);
  int dtState  = digitalRead(DT_L);

  if (clkState != lastCLK_L) {
    if (dtState != clkState) {
      encoderLeftCount++;   // sens horaire
    } else {
      encoderLeftCount--;   // sens anti-horaire
    }
  }

  lastCLK_L = clkState;
}


// =========================
// ENCODEUR DROIT
// =========================
// ⚠️ Mets ici tes vrais pins
#define CLK_R  13
#define DT_R   27

volatile long encoderRightCount = 0;
volatile int lastCLK_R = 0;

void IRAM_ATTR handleEncoderRight() {
  int clkState = digitalRead(CLK_R);
  int dtState  = digitalRead(DT_R);

  if (clkState != lastCLK_R) {
    if (dtState != clkState) {
      encoderRightCount++;   // sens horaire
    } else {
      encoderRightCount--;   // sens anti-horaire
    }
  }

  lastCLK_R = clkState;
}


// =========================
// SETUP
// =========================
void setup() {
  Serial.begin(115200);

  // Gauche
  pinMode(CLK_L, INPUT_PULLUP);
  pinMode(DT_L,  INPUT_PULLUP);
  lastCLK_L = digitalRead(CLK_L);
  attachInterrupt(digitalPinToInterrupt(CLK_L), handleEncoderLeft, CHANGE);

  // Droit
  pinMode(CLK_R, INPUT_PULLUP);
  pinMode(DT_R,  INPUT_PULLUP);
  lastCLK_R = digitalRead(CLK_R);
  attachInterrupt(digitalPinToInterrupt(CLK_R), handleEncoderRight, CHANGE);
}


// =========================
// LOOP
// =========================
void loop() {
  long left  = encoderLeftCount;
  long right = encoderRightCount;

  Serial.print("Left: ");
  Serial.print(left);
  Serial.print("   |   Right: ");
  Serial.println(right);

  delay(50);
}
