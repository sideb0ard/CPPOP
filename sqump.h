#ifndef SQUMP_H_
#define SQUMP_H_

#include <string>
#include "soundb0ard.h"
#include "oscillator.h"

class Sqump : public Soundb0ard
{
public:
  Sqump(float f);
  //float freq;
  float vol;
  Oscillator car;
  Oscillator mod;
  //float phase;
  //float phaseIncr[4];

  float genNextSound();
  std::string info();
};

#endif // SQUMP_H_
