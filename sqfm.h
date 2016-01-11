#ifndef SQFM_H_
#define SQFM_H_

#include <string>
#include "soundb0ard.h"
#include "oscillator.h"

class Sqfm : public Soundb0ard
{
public:
  Sqfm(float cf, float mf);
  Oscillator car;
  Oscillator mod;

  void update(std::string osc, int freq);
  float genNextSound();
  std::string info();
};

#endif // SQFM_H_
