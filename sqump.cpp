#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

#include "defjams.h"
#include "sqump.h"

Sqump::Sqump(float f) : freq{f}
{
    vol = 0.7;
    phase = 0;
    phaseIncr[0] = freq * FREQRAD;
    phaseIncr[1] = freq * FREQRAD * 2;
    phaseIncr[2] = freq * FREQRAD * 3;
    phaseIncr[3] = freq * FREQRAD * 4;
    std::cout << "SQUMP CREATTTTTED... with " << f << std::endl;

}
    
float Sqump::genNextSound()
{
    float val = 0;
    int p;
    for (p=0; p < 4; p++) {
        val += sin(phase += phaseIncr[p]);
        if (phase >= TWO_PI)
            phase -= TWO_PI;
    }
    return vol * (val / 1.53);
}

std::string Sqump::info()
{
    std::ostringstream ret_string;
    ret_string << "Sqump. Freq: " << freq << " // phase: " << phase;
    return ret_string.str();

}
    
