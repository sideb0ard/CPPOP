#ifndef ENVELOPE_H_
#define ENVELOPE_H_

#include <vector>
#include <string>

class Envelope
{
public:
    Envelope();
    float genNextVal();
    std::string info();

private:
    int phase;
    float phases[136054];
    float phaseIncr;
    float peakstart;
    float peakstop;
    //std::vector<float> phases(136054);
    
    int bpm; // taken from Mixer settings
    int looptime; // in beats
    int ticker;
};

#endif // ENVELOPE_H_
