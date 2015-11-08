#ifndef OSCILLATOR_H_
#define OSCILLATOR_H_

class Oscillator
{
public:
  Oscillator();
  float genNextSound();

private:
  float vol;
  float freq;
  float phase;
  float phaseIncr;
  float clock;
};

#endif // OSCILLATOR_H_
