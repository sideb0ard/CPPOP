#include <chrono>
#include <iostream>
#include <thread>

#include "algae.h"
#include "mixer.h"

extern Mixer mixer;

Algae::Algae() : prev(0) {}
void Algae::Run()
{
    //prev == mixer.microTick % 16;
    while (1)
    {
        if (prev == mixer.microtick  ) // % 16)
        {
            // all good
        } else {
            std::cout << "SHACK-a-LACK! ticking!" << mixer.microtick << std::endl;
            prev = mixer.microtick % 16;
        }
    }
}
