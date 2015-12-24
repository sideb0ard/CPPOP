#ifndef SAWTOOTH_H_
#define SAWTOOTH_H_

#include <string>
#include "soundb0ard.h"

class Sawtooth : public Soundb0ard
{
public:
  Sawtooth(float f);
  float freq;
  float vol;
  float phase;
  float phaseIncr;

  float genNextSound();
  std::string info();
  float getVol();
  void setVol(float volume);
};

#endif // SAWTOOTH_H_
