#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

#include "defjams.h"
#include "sqfm.h"

Sqfm::Sqfm(float cf, float mf) : car{cf}, mod{mf}
{
    mod.amp = FREQRAD * 100;
    std::cout << "SQFM CREATTTTTED... with " << cf << " :: " << mf << std::endl;

}

void Sqfm::update(std::string osc, int freq)
{
    if (osc == "mod")
        mod.freq = freq;
    else if (osc == "car")
        car.freq = freq;
    std::cout << "Fmupdated! : mod.freq: " << mod.freq << std::endl;

}
    
float Sqfm::genNextSound()
{

    auto modVal = mod.amp * sin(mod.phase);
    car.phase += car.phIncr() + modVal;
    if (car.phase >= TWO_PI)
        car.phase -= TWO_PI;
    if (car.phase < 0.0)
        car.phase += TWO_PI;

    mod.phase += mod.phIncr();
    if (mod.phase >= TWO_PI)
        mod.phase -= TWO_PI;
    if (mod.phase < 0.0)
        mod.phase += TWO_PI;

    // return vol * sin(car.phase);
    return vol * ((2.0 * (car.phase * (1.0 / TWO_PI) )) - 1.0);
}

std::string Sqfm::info()
{
    std::ostringstream ret_string;
    ret_string << ANSI_COLOR_WHITE << "SQFm. Car.Freq: " << car.freq << " // Car.phase: " << car.phase << " // Mod.Freq: " << mod.freq << " // Mod.phase: " << mod.phase << "VOL: " << vol << ANSI_COLOR_RESET;
    return ret_string.str();

}
    
