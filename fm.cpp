#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

#include "defjams.h"
#include "fm.h"

//Fm::Fm(float f) : freq{f}, car{f}, mod{730}
Fm::Fm(float cf, float mf) : car{cf}, mod{mf}
{
    mod.amp = FREQRAD * 100;
    std::cout << "SQUMP CREATTTTTED... with " << cf << " :: " << mf << std::endl;

}

void Fm::update(std::string osc, int freq)
{
    if (osc == "mod")
        mod.freq = freq;
    else if (osc == "car")
        car.freq = freq;
    std::cout << "Fmupdated! : mod.freq: " << mod.freq << std::endl;

}
    
float Fm::genNextSound()
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

    return vol * sin(car.phase);
}

std::string Fm::info()
{
    std::ostringstream ret_string;
    ret_string << ANSI_COLOR_YELLOW << "Fm. Car.Freq: " << car.freq << " // Car.phase: " << car.phase << " // Mod.Freq: " << mod.freq << " // Mod.phase: " << mod.phase << "VOL: " << vol << ANSI_COLOR_RESET;
    return ret_string.str();

}
    
