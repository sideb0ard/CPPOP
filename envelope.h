#ifndef ENVELOPE_H_
#define ENVELOPE_H_

#include <string>

class Envelope
{
public:
    Envelope();
    float genNextVal();
    std::string info();

private:
    float phase;
    float phaseIncr;
    float peakstart;
    float peakstop;
    
    int bpm; // taken from Mixer settings
    int looptime; // in beats
};

#endif // ENVELOPE_H_
