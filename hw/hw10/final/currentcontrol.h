#ifndef currentcontrol__H__
#define currentcontrol__H__

#define NUMSAMPS 100                        // number of points in a waveform

volatile int duty_cycle;

void PWM_init();
void makeWaveform();

#endif // currentcontrol__H__
