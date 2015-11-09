#include <cmath>
#include <iostream>

#include "defjams.h"
#include "oscillator.h"

Oscillator::Oscillator() 
{
    vol = 0.7;
    freq = 440;
    phase = 0;
    phaseIncr = FREQRAD;
    clock = 0;
}
Oscillator::Oscillator(float f) : freq{f}
{
    vol = 0.7;
    phase = 0;
    phaseIncr = FREQRAD;
    clock = 0;
    std::cout << "CREATTTTTED...\n";
}
    


float Oscillator::genNextSound()
{
  phase += phaseIncr;
  if (phase >= TWO_PI)
    phase -= TWO_PI;
  return vol * sin(phase);

}
