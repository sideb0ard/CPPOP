#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <string>
#include "soundb0ard.h"

class Triangle : public Soundb0ard
{
public:
  Triangle(float f);
  float freq;
  float vol;
  float phase;
  float phaseIncr;

  float genNextSound();
  std::string info();
  float getVol();
  void setVol(float volume);
};

#endif // TRIANGLE_H_
