#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

#include "defjams.h"
#include "envelope.h"

Envelope::Envelope()
{
    //starttime = 0.0;
    std::cout << "ENVELOPE CREATTTTTED" << std::endl;
    phase = 0;
    phaseIncr = FREQRAD / 2.4; // 0.6 = (bpm(100) / 60 ) * 8 beats e.g two bars
    peakstart = TWO_PI * 0.15;
    peakstop = TWO_PI * 0.85;

}
    

float Envelope::genNextVal()
{
    phase += phaseIncr;
    if (phase >= TWO_PI) {
        phase -= TWO_PI;
        std::cout << "ENVELOPE LOOP START" << std::endl;
    }
    if (phase <= peakstart) {
        return 0.5;
    } else if (phase >= peakstop) {
        float a = phase - peakstop;
        float b = TWO_PI - peakstop;
        float frac = a / b;
        float targ = -1.0 * frac;
        return peakstop + targ;
        //return 0.5;

    } else {
        return 1.0;
    }
}

std::string Envelope::info()
{
    std::ostringstream ret_string;
    ret_string << ANSI_COLOR_CYAN << "Am a wee envelope" << ANSI_COLOR_RESET ;
    return ret_string.str();

}
    
