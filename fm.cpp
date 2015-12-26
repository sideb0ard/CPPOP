#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

#include "defjams.h"
#include "fm.h"

//Fm::Fm(float f) : freq{f}, car{f}, mod{730}
Fm::Fm(float cf, float mf) : car{cf}, mod{mf}
{
    vol = 0.0;
    mod.amp = FREQRAD * 100;
    std::cout << "SQUMP CREATTTTTED... with " << cf << " :: " << mf << std::endl;

}

float Fm::getVol()
{
    return vol;
}

void Fm::setVol(float volume)
{
    if (volume <= 1.0) {
        if ( volume <= 0.0 ) {
            vol = 0.0;
        } else {
            vol = volume;
        }
    }
}

void Fm::update(std::string osc, int freq)
{
    //Fm *sqmp =  (Fm *) mixer.signals[sqid];
    if (osc == "mod")
        mod.freq = freq;
    else if (osc == "car")
        car.freq = freq;
    std::cout << "Fmupdated! : mod.freq: " << mod.freq << std::endl;

}
    
float Fm::genNextSound()
{

    //int modVal = mod.amp * sin(mod.phase);
    //int modVal = 10 * sin(mod.phase);
    auto modVal = mod.amp * sin(mod.phase);
    car.phase += car.phIncr() + modVal;
    if (car.phase >= TWO_PI)
        car.phase -= TWO_PI;

    mod.phase += mod.phIncr();
    ////std::cout << "car.phase: " << car.phase << "MOD.phaze!!: " << mod.phase << std::endl;
    if (mod.phase >= TWO_PI)
        mod.phase -= TWO_PI;

    return vol * sin(car.phase);
    //return vol * 0.2;
}

std::string Fm::info()
{
    std::ostringstream ret_string;
    ret_string << ANSI_COLOR_YELLOW << "Fm. Car.Freq: " << car.freq << " // Car.phase: " << car.phase << " // Mod.Freq: " << mod.freq << " // Mod.phase: " << mod.phase << ANSI_COLOR_RESET;
    return ret_string.str();

}
    
