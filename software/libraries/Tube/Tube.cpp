#include <Arduino.h>
#include <DS1307RTC.h>
#include <Time.h>
#include <Wire.h>
#include "./Tube.h"

void setupTubePin() {
  pinMode(PIN_CLR_B, OUTPUT);
  pinMode(PIN_CLR_G, OUTPUT);
  pinMode(PIN_CLR_R, OUTPUT);

  pinMode(PIN_CTL_2, OUTPUT);
  pinMode(PIN_CTL_1, OUTPUT);
  pinMode(PIN_CTL_0, OUTPUT);

  pinMode(PIN_VAL_C, OUTPUT);
  pinMode(PIN_VAL_3, OUTPUT);
  pinMode(PIN_VAL_2, OUTPUT);
  pinMode(PIN_VAL_1, OUTPUT);
  pinMode(PIN_VAL_0, OUTPUT);

  pinMode(PIN_SWQ, INPUT_PULLUP);
}

void outputOneTube(byte ctl, byte val, byte clr) {
  digitalWrite(PIN_CLR_B, (clr >> 2) & 1);
  digitalWrite(PIN_CLR_G, (clr >> 1) & 1);
  digitalWrite(PIN_CLR_R, (clr >> 0) & 1);

  digitalWrite(PIN_CTL_2, (ctl >> 2) & 1);
  digitalWrite(PIN_CTL_1, (ctl >> 1) & 1);
  digitalWrite(PIN_CTL_0, (ctl >> 0) & 1);

  digitalWrite(PIN_VAL_C, (val >> 4) & 1);
  digitalWrite(PIN_VAL_3, (val >> 3) & 1);
  digitalWrite(PIN_VAL_2, (val >> 2) & 1);
  digitalWrite(PIN_VAL_1, (val >> 1) & 1);
  digitalWrite(PIN_VAL_0, (val >> 0) & 1);
}

void outputTube(byte tube[], byte color[], int msec) {
  int count = msec / (N_TUBE * SCAN_DELAY_MS);
  for (int i = 0; i < count; ++i) {
    for (byte j = 0; j < N_TUBE; ++j) {
      outputOneTube(j, tube[j], color[j]);
      delay(SCAN_DELAY_MS);
    }
  }
}

void setupRTC(void (*fn)()) {
  Serial.begin(115200);

  Wire.begin();
  Wire.beginTransmission(0x68); // Slave mode address
  Wire.write(0x07);
  Wire.write(0x10);  // Set Square Wave to 1 Hz
  Wire.endTransmission();
  if (fn) {
    attachInterrupt(digitalPinToInterrupt(PIN_SWQ), fn, RISING);
  }

  setSyncProvider(RTC.get);
  while (timeStatus() == timeNotSet);
}
