#include <Tube.h>

byte tube[] = { 6, 9, 5, 8, 4, 0, 10, 1 };
byte color[] = { 0, 1, 2, 3, 4, 5, 6, 7 };


void setup() {
  setupTubePin();
  setupRTC(nullptr);
  // put your setup code here, to run once:
  randomSeed(analogRead(0));
}

void loop() {
  // put your main code here, to run repeatedly:
  byte t[] = { 16, 16, 16, 16, 16, 16, 16, 16 };
  byte c[] = { 0, 0, 0, 0, 0, 0, 0, 0 }; 
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 99; ++j) {
      for (int k = i; k < 8; ++k) {
        t[k] = random(0, 11);
        c[k] = random(0, 7);
      }
      outputTube(t, c, 16);
    }
    t[i] = tube[i];
    c[i] = color[i];
    outputTube(t, c, 16);
  }
  outputTube(t, c, 10000);
}
