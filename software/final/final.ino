#include <Tube.h>
#include <Time.h>
#include <Note.h>

byte tube[] = { 16, 16, 16, 16, 16, 16, 16, 16 };
byte color[] = { 0, 0, 0, 0, 0, 0, 0, 0 };

void runClock();
void runCountDown();
void runSing();
void runRandom();

enum Mode {
  CLOCK,
  COUNT_DOWN,
  SING,
  RANDOM,
};

Mode mode = COUNT_DOWN;

void (*const runMap[])() = {
  runClock,
  runCountDown,
  runSing,
  runRandom,
};

const int singNotes[] = {
  NOTE_, NOTE_C3,
  NOTE_C3, NOTE_E3,
  NOTE_E3, NOTE_G3,
  NOTE_G3, NOTE_E3,
  NOTE_D3, NOTE_E3,
  NOTE_C4, NOTE_A3, NOTE_G3,
  NOTE_A3, NOTE_E3,
  NOTE_A3, NOTE_G3, NOTE_FS3,
  NOTE_G3, NOTE_, NOTE_G3,
  NOTE_F3, NOTE_A3, NOTE_G3, NOTE_C4,
  NOTE_B3, NOTE_D4, NOTE_C4, NOTE_A3,
  NOTE_A3, NOTE_C4, NOTE_A3, NOTE_G3,
  NOTE_E3, NOTE_D3, NOTE_C3, NOTE_G3,
  NOTE_G3, NOTE_A3, NOTE_G3,
  NOTE_G3, NOTE_C4,
  NOTE_C4, NOTE_A3, NOTE_G3,
  NOTE_G3, NOTE_G3,
  NOTE_E4, NOTE_D4, NOTE_E4,
  NOTE_D4, NOTE_G3,
  NOTE_D4, NOTE_D4, NOTE_E4,
  NOTE_C4,
};

const int singDurations[] = {
  12, 4,
  12, 4,
  12, 4,
  12, 4,
  12, 4,
  12, 2, 2,
  12, 4,
  12, 2, 2,
  8, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4,
  12, 2, 2,
  12, 4,
  12, 2, 2,
  12, 4,
  12, 2, 2,
  12, 4,
  12, 2, 2,
  16,
};

const byte singColors[] = {
  0, 1,
  1, 3,
  3, 5,
  5, 3,
  2, 3,
  1, 6, 5,
  6, 3,
  6, 5, 4,
  5, 0, 5,
  4, 6, 5, 1,
  7, 2, 1, 6,
  6, 1, 6, 5,
  3, 2, 1, 5,
  5, 6, 5,
  5, 1,
  1, 6, 5,
  5, 5,
  3, 2, 3,
  2, 5,
  2, 2, 3,
  1,
};

void output(int ms) {
  outputTube(tube, color, ms);
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

void displayWeek() {
  int w = weekday();
  for (int i = 0; i < N_TUBE; ++i) {
    color[i] = w;
  }
}

void randomColor() {
  for (int i = 0; i < N_TUBE; ++i) {
    color[i] = random(1, 7);
  }
}

void randomTube() {
  for (int i = 0; i < N_TUBE; ++i) {
    tube[i] = random(0, 11);
  }
}

void resetColor() {
  for (int i = 0; i < N_TUBE; ++i) {
    color[i] = 0;
  }
}

void resetTube() {
  for (int i = 0; i < N_TUBE; ++i) {
    tube[i] = 16;
  }
}

void runClock() {
  displayDate();
  displayWeek();
  output(500);
  displayTime();
  randomColor();
  output(500);
}

void runCountDown() {
  for (int i = 0; i < N_TUBE; ++i) {
    color[i] = N_TUBE - i - 1;
  }
  tube[7] = 2;
  tube[6] = 0;
  tube[5] = 1;
  tube[4] = 9;
  tube[3] = 10;
  tube[2] = 11;
  while (true) {
    int s = 60 - second();
    if (s == 60) {
      break;
    }
    tube[1] = s / 10;
    tube[0] = s % 10;
    output(200);
    tube[3] = 21 - tube[3];
    tube[2] = 21 - tube[2];
    int c = color[0];
    for (int i = 0; i < N_TUBE - 1; ++i) {
      color[i] = color[i + 1];
    }
    color[7] = c;
  }
  mode = SING;
}

void runSing() {
  resetColor();
  int len = sizeof(singNotes) / sizeof(int);
  for (int i = 0; i < len; ++i) {
    for (int j = 0; j < N_TUBE - 1; ++j) {
      color[j] = color[j + 1];
    }
    color[7] = singColors[i];
    int note = singNotes[i];
    if (note != NOTE_) {
      tone(PIN_GP_0, note);
    }
    int d = singDurations[i];
    for (int j = 0; j < d; ++j) {
      displayTime();
      output(200);
    }
    noTone(PIN_GP_0);
  }
  mode = CLOCK;
}

void runRandom() {
  for (int i = 0; i < 125; ++i) {
    randomTube();
    randomColor();
    output(40);
  }
  mode = CLOCK;
}

void setup() {
  setupTubePin();
  setupRTC(nullptr);
  randomSeed(analogRead(0));
}

void loop() {
  runMap[mode]();
}
