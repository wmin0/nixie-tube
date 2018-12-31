#ifndef _TUBE_H_
#define _TUBE_H_

#define PIN_CLR_R 3
#define PIN_CLR_G 4
#define PIN_CLR_B 5

#define PIN_CTL_0 6
#define PIN_CTL_1 7
#define PIN_CTL_2 8

#define PIN_VAL_0 9
#define PIN_VAL_1 10
#define PIN_VAL_2 11
#define PIN_VAL_3 12
#define PIN_VAL_C 13

#define PIN_SWQ 2
#define PIN_GP_0 A0
#define PIN_GP_1 A1
#define PIN_GP_2 A2
#define PIN_GP_3 A3

#define N_TUBE 8
#define SCAN_DELAY_MS 2

extern "C++" {

void setupTubePin();
void outputOneTube(byte ctl, byte val, byte clr);
void outputTube(byte tube[], byte color[], int msec);

void setupRTC(void (*fn)());

};

#endif
