#ifndef currentcontrol__H__
#define currentcontrol__H__

#define NUMSAMPS 100                        // number of points in a waveform

volatile int duty_cycle;
volatile int kI;

void PWM_init();
void makeWaveform();

#endif // currentcontrol__H__
