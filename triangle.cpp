#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

#include "defjams.h"
#include "triangle.h"

Triangle::Triangle(float f) : freq{f}
{
    vol = 0.7;
    phase = 0;
    phaseIncr = (TWO_PI / SAMPLE_RATE) * freq;
    std::cout << "Triangle CREATTTTTED... with " << f << std::endl;

}
    
float Triangle::genNextSound()
{
    float twoDivPI = 2.0/M_PI;
    float triVal = (phase * twoDivPI);
    if (phase < 0)
        triVal = 1.0 + triVal;
    else
        triVal = 1.0 - triVal;
    if ((phase += phaseIncr)  >= M_PI)
        phase -= TWO_PI;
    return vol * triVal;
}

std::string Triangle::info()
{
    std::ostringstream ret_string;
    ret_string << "Triangle. Freq: " << freq << " // phase: " << phase;
    return ret_string.str();

}
    
