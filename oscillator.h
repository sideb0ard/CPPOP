#ifndef OSCILLATOR_H_
#define OSCILLATOR_H_

#include <vector>

class Oscillator
{
public:
  Oscillator(float f);
  float freq;
  float vol;
  float phase;
  float phaseIncr;
  float clock;

  float genNextSound();
};

#endif // OSCILLATOR_H_
