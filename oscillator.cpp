#include <cmath>

#include "defjams.h"
#include "oscillator.h"

Oscillator::Oscillator() 
{
  vol = 0.7;
  freq = 320;
  phase = 0;
  phaseIncr = 0.2;
  clock = 0;
}


float Oscillator::genNextSound()
{
  phase += phaseIncr;
  if (phase >= TWO_PI)
    phase -= TWO_PI;
  return vol * sin(phase);

}
