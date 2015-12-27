#ifndef FM_H_
#define FM_H_

#include <string>
#include "soundb0ard.h"
#include "oscillator.h"

class Fm : public Soundb0ard
{
public:
  Fm(float cf, float mf);
  Oscillator car;
  Oscillator mod;

  float genNextSound();
  void update(std::string osc, int freq);
  std::string info();
};

#endif // FM_H_
