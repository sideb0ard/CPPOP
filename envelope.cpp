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
    ticker = 0;
    looptime = 8; // two bars
    // phaseIncr = FREQRAD / 2.4; // 0.6 = (bpm(100) / 60 ) * 8 beats e.g two bars
    //phaseIncr = FREQRAD / ((6000 / mixer.bpm) * looptime); 
    bpm = mixer.bpm;
    phaseIncr = FREQRAD / (( 60.0 / bpm) * looptime);
    //float phaseTableSize = ((60.0 / bpm) / SAMPLE_RATE) * looptime;
    //std::cout << "PhaseTable Size = " << phaseTableSize << std::endl;
    //float phases[136054];
    //for 
    
    //peakstart = TWO_PI * 0.15;
    //peakstop = TWO_PI * 0.85;
    peakstart = 136054 * 0.15;
    peakstop = 136054 * 0.85;

    float val;
    for (int i = 0; i < 136054; i++) {
      if (i <= peakstart) {
          float frac = i / peakstart;
          float targ_dist = 1.0 * frac;
          float targ_val = 0.0 + targ_dist;
          val = targ_val;
      } else if (i >= peakstop) {
          float a = i - peakstop;
          float b = 136054 - peakstop;
          float frac = a / b;
          float targ_dist = -1.0 * frac;
          float targ_val = 1.0 + targ_dist;
          val = targ_val;
      } else {
          val = 1.0;
      }
      //phases.push_back(val);
      phases[i] = val;
      //phase += phaseIncr;
      //phase++;
    }

    //phase = 0;

    //std::cout << "PHASESZZZ: " << phases << std::endl;
}
    

float Envelope::genNextVal()
{
    if ( bpm != mixer.bpm ) {
        bpm = mixer.bpm;
        phaseIncr = FREQRAD / (( 60.0 / mixer.bpm) * looptime);
    }

    int val = phase;
    phase++;
    if (phase >= 136054) {
        phase -= 136054;
    }
    return phases[val];
}

std::string Envelope::info()
{
    std::ostringstream ret_string;
    ret_string << ANSI_COLOR_CYAN << "Am a wee envelope: " << phases[phase]  << ANSI_COLOR_RESET ;
    //for (int i = 0; i < 136054; i++) 
    //  std::cout << phases[i] << ' ';
    return ret_string.str();

}
    
