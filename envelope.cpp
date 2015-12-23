#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

#include "defjams.h"
#include "envelope.h"
#include "mixer.h"

extern Mixer mixer;

Envelope::Envelope()
{
    //starttime = 0.0;
    //std::cout << "ENVELOPE CREATTTTTED" << std::endl;
    phase = 0;
    looptime = 8; // two bars
    // phaseIncr = FREQRAD / 2.4; // 0.6 = (bpm(100) / 60 ) * 8 beats e.g two bars
    //phaseIncr = FREQRAD / ((6000 / mixer.bpm) * looptime); 
    phaseIncr = 0.0;
    peakstart = TWO_PI * 0.15;
    peakstop = TWO_PI * 0.85;

}
    

float Envelope::genNextVal()
{
    //phaseIncr = FREQRAD / ((6000 / mixer.bpm) * looptime); 
    phaseIncr = FREQRAD / (( 60.0 / mixer.bpm) * looptime);
    phase += phaseIncr;
    if (phase >= TWO_PI) {
        phase -= TWO_PI;
        //std::cout << "ENVELOPE LOOP START" << std::endl;
    }
    if (phase <= peakstart) {
        //return 0.5;
        float frac = phase / peakstart;
        float targ_dist = 1.0 * frac;
        float targ_val = 0.0 + targ_dist;
        return targ_val;
        //return 1.0;
    } else if (phase >= peakstop) {
        float a = phase - peakstop;
        float b = TWO_PI - peakstop;
        float frac = a / b;
        float targ_dist = -1.0 * frac;
        float targ_val = 1.0 + targ_dist;
        //std::cout << "TARG_VAL is " << targ_val << std::endl;
        return targ_val;
        //return 0.5;

    } else {
        return 1.0;
    }
}

std::string Envelope::info()
{
    std::ostringstream ret_string;
    ret_string << ANSI_COLOR_CYAN << "Am a wee envelope: " << phase  << ANSI_COLOR_RESET ;
    return ret_string.str();

}
    
