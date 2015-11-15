#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

#include "defjams.h"
#include "sawtooth.h"

Sawtooth::Sawtooth(float f) : freq{f}
{
    vol = 0.7;
    phase = 0;
    phaseIncr = freq * FREQRAD;
    std::cout << "Sawtooth CREATTTTTED... with " << f << std::endl;

}
    
float Sawtooth::genNextSound()
{
    if ((phase += phaseIncr)  >= TWO_PI)
        phase -= TWO_PI;
    return vol * ((phase / M_PI) - 1);
}

std::string Sawtooth::info()
{
    std::ostringstream ret_string;
    ret_string << "Sawtooth. Freq: " << freq << " // phase: " << phase;
    return ret_string.str();

}
    
