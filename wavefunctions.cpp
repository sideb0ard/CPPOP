#include <cmath>

#include "defjams.h"
#include "oscillator.h"
#include "wavefunctions.h"

float sinetick(Oscillator* osc)
{
    float retval = sin(osc->phase);

    osc->phase += osc->phaseIncr;

    if (osc->phase >= TWO_PI)
        osc->phase -= TWO_PI;
    if (osc->phase < 0.0)
        osc->phase += TWO_PI;

    return retval;
}
