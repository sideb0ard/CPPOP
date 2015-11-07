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
