#ifndef SOUNDB0ARD_
#define SOUNDB0ARD_

//#include "oscillator.h"

class Soundb0ard
{
public:
    //Soundb0ard(float f);
    //Oscillator car; // carrier
    //Oscillator mod; // modulator

    virtual float genNextSound() = 0;
    virtual std::string info() = 0;

    float freq;
};

#endif // SOUNDB0ARD_
