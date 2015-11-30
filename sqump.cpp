#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

#include "defjams.h"
#include "sqump.h"

//Sqump::Sqump(float f) : freq{f}, car{f}, mod{730}
Sqump::Sqump(float f) : car{f}, mod{730}
{
    vol = 0.7;
    mod.amp = FREQRAD * 100;
    std::cout << "SQUMP CREATTTTTED... with " << f << std::endl;

}
    
float Sqump::genNextSound()
{

    int modVal = mod.amp * sin(mod.phase);
    car.phase += car.phIncr() + modVal;
    if (car.phase >= TWO_PI)
        car.phase -= TWO_PI;

    mod.phase += mod.phIncr();
    //std::cout << "PHINCR!!: " << mod.phIncr() << std::endl;
    if (mod.phase >= TWO_PI)
        mod.phase -= TWO_PI;

    return vol * sin(car.phase);
}

std::string Sqump::info()
{
    std::ostringstream ret_string;
    ret_string << "Sqump. Car.Freq: " << car.freq << " // Car.phase: " << car.phase << " // Mod.Freq: " << mod.freq << " // Mod.phase: " << mod.phase;
    return ret_string.str();

}
    
