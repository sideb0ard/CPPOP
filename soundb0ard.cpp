#include <cmath>
#include <iostream>

#include "defjams.h"
#include "oscillator.h"
#include "soundb0ard.h"

Soundb0ard::Soundb0ard(float f) : car{Oscillator(f)}
{
    //Oscillator car(f);
    //Oscillator mod(f);
    std::cout << "B0ARD CREATTTTTED... with " << f << std::endl;
}


float Soundb0ard::genNextSound()
{
    return car.genNextSound();
}
