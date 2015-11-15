#ifndef SQUMP_H_
#define SQUMP_H_

#include <string>
#include "soundb0ard.h"

class Sqump : public Soundb0ard
{
public:
  Sqump(float f);
  float freq;
  float vol;
  float phase;
  float phaseIncr[4];

  float genNextSound();
  std::string info();
};

#endif // SQUMP_H_
