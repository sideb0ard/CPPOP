#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

#include "defjams.h"
#include "sqump.h"

Sqump::Sqump(float f) : freq{f}, car{freq}, mod{730}
{
    vol = 0.7;
    mod.amp = FREQRAD * 100;
    std::cout << "SQUMP CREATTTTTED... with " << f << std::endl;

}
    
float Sqump::genNextSound()
{

    int modVal = mod.amp * sin(mod.genNextSound());
    car.phase += car.phaseIncr + modVal;

    return vol * sin(car.genNextSound());
}

std::string Sqump::info()
{
    std::ostringstream ret_string;
    ret_string << "Sqump. Freq: " << freq << " // phase: " << phase;
    return ret_string.str();

}
    
