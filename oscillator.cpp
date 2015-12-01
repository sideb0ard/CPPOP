#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

#include "defjams.h"
#include "oscillator.h"

Oscillator::Oscillator(float f) : freq{f}
{
    vol = 0.7;
    amp = 0;
    phase = 0;
    phaseIncr = freq * FREQRAD;
    clock = 0;
    std::cout << "CREATTTTTED... with " << f << std::endl;

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
    ret_string << ANSI_COLOR_CYAN << "Sine. Freq: " << freq << " // phase: " << phase << " // phaseIncr" << phaseIncr << ANSI_COLOR_RESET ;
    return ret_string.str();

}
    
