#ifndef currentcontrol__H__
#define currentcontrol__H__

#define NUMSAMPS 100                        // number of points in a waveform

volatile int duty_cycle;
volatile int k_I;
volatile int k_P;

void PWM_init();
void makeWaveform();

#endif // currentcontrol__H__
