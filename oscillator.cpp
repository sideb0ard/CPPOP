#include <cmath>
#include <iostream>

#include "defjams.h"
#include "oscillator.h"

Oscillator::Oscillator() 
{
    vol = 0.7;
    freq = 440;
    phase = 0;
    phaseIncr = freq * FREQRAD;
    clock = 0;
}
Oscillator::Oscillator(float f) : freq{f}
{
    vol = 0.7;
    phase = 0;
    phaseIncr = freq * FREQRAD;
    clock = 0;
    std::cout << "CREATTTTTED... with " << f << std::endl;
}
    


float Oscillator::genNextSound()
{
  phase += phaseIncr;
  if (phase >= TWO_PI)
    phase -= TWO_PI;
  return vol * sin(phase);

}
