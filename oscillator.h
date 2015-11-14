#ifndef OSCILLATOR_H_
#define OSCILLATOR_H_

#include <string>
#include "soundb0ard.h"

class Oscillator : public Soundb0ard
{
public:
  Oscillator(float f);
  float freq;
  float vol;
  float phase;
  float phaseIncr;
  float clock;

  float genNextSound();
  std::string info();
};

#endif // OSCILLATOR_H_
