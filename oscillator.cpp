#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

#include "defjams.h"
#include "oscillator.h"

Oscillator::Oscillator(float f) : freq{f}
{
    vol = 0.0;
    amp = 0;
    phase = 0;
    phaseIncr = freq * FREQRAD;
    clock = 0;
    std::cout << "CREATTTTTED... with " << f << std::endl;

}
    
float Oscillator::getVol()
{
    return vol;
}

void Oscillator::setVol(float volume)
{
    if (volume <= 1.0) {
        if ( volume <= 0.0 ) {
            vol = 0.0;
        } else {
            vol = volume;
        }
    }
}

float Oscillator::phIncr()
{
    return freq * FREQRAD;
}

float Oscillator::genNextSound()
{
    phase += phaseIncr;
    if (phase >= TWO_PI)
        phase -= TWO_PI;
    return vol * sin(phase);
}

std::string Oscillator::info()
{
    std::ostringstream ret_string;
    ret_string << ANSI_COLOR_CYAN << "Sine. Freq: " << freq << " // phase: " << phase << " // phaseIncr" << phaseIncr << " Vol: " << vol << ANSI_COLOR_RESET ;
    return ret_string.str();

}
    
