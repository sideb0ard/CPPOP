#ifndef SOUNDB0ARD_
#define SOUNDB0ARD_

//#include "oscillator.h"

class Soundb0ard
{
public:
    //Soundb0ard(float f);
    //Oscillator car; // carrier
    //Oscillator mod; // modulator

    virtual float genNextSound() = 0;  // rename to genNextVal?
    virtual std::string info() = 0;
    virtual float getVol() = 0;
    virtual void setVol(float vol) = 0;

    //float vol;
    //float freq;
};

#endif // SOUNDB0ARD_
