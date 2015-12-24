#ifndef FM_H_
#define FM_H_

#include <string>
#include "soundb0ard.h"
#include "oscillator.h"

class Fm : public Soundb0ard
{
public:
  Fm(float cf, float mf);
  //float freq;
  float vol;
  Oscillator car;
  Oscillator mod;
  //float phase;
  //float phaseIncr[4];

  float genNextSound();
  void update(std::string osc, int freq);
  void setVol(float volume);
  float getVol();
  std::string info();
};

#endif // FM_H_
