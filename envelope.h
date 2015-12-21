#ifndef ENVELOPE_H_
#define ENVELOPE_H_

#include <string>

class Envelope
{
public:
    Envelope();
    float peakstart;
    float peakstop;
    
    float genNextVal();
    std::string info();

private:
    float phase;
    float phaseIncr;
};

#endif // ENVELOPE_H_
