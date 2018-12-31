#include <Tube.h>
#include <Time.h>
#include <DS1307RTC.h>

byte tube[] = { 16, 16, 16, 16, 16, 16, 16, 16 };
//byte tube[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
byte color[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

void setTime() {
  int y = 2018;
  int M = 12;
  int d = 30;
  int h = 18;
  int m = 12;
  int s = 0;

  tmElements_t tm;
  tm.Year = y - 1970; // start from 1970
  tm.Month = M;
  tm.Day = d;
  tm.Hour = h;
  tm.Minute = m;
  tm.Second = s;
  setTime(makeTime(tm));
  RTC.set(makeTime(tm));
}

void displayDate() {
  int y = year();
  int m = month();
  int d = day();
  tube[0] = d % 10;
  tube[1] = d / 10;
  tube[2] = m % 10;
  tube[3] = m / 10;
  tube[4] = y % 10;
  tube[5] = (y / 10) % 10;
  tube[6] = (y / 100) % 10;
  tube[7] = y / 1000;
}

void displayTime() {
  int h = hour();
  int m = minute();
  int s = second();
  tube[0] = s % 10;
  tube[1] = s / 10;
  tube[2] = 10;
  tube[3] = m % 10;
  tube[4] = m / 10;
  tube[5] = 11;
  tube[6] = h % 10;
  tube[7] = h / 10;
}

void ISR_RTC() {
  displayTime();
}

void setup() {
  setupTubePin();
  setupRTC(ISR_RTC);
  //setTime();
}

void loop() {
  //displayDate();
  //outputTube(tube, color, 500);
  displayTime();
  outputTube(tube, color, 40);
}
