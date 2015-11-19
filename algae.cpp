#include <chrono>
#include <iostream>
#include <thread>

#include "algae.h"
#include "mixer.h"
#include "utils.h"

extern Mixer mixer;

Algae::Algae() : prev(0) {}
void Algae::Run()
{
    //prev == mixer.microTick % 16;
    int randDisappear;
    while (1)
    {
        if (prev == (mixer.microtick % 16)  ) // % 16)
        {
            // all good
        } else {
            //std::cout << "PREV:" << prev <<  " // SHACK-a-LACK! ticking!" << mixer.microtick << std::endl;
            prev = mixer.microtick % 16;
            if ( isPrime(mixer.microtick) && (rand() % 4 >= 1))
            {
                std::cout << "BOOYA! Gonna spin a SINE O' " << mixer.microtick << ".. There are this many signals: " << mixer.sigSize() << std::endl;
                siney(primeyGen());

            }
            if (mixer.sigSize() > 2 && (rand() % 4 > 1)) // more than two signals, and 1 in 3 chance 
            {
                randDisappear = rand() % mixer.sigSize();
                std::cout << "Make a disappearance..." << std::endl;
                mixer.signals.erase(mixer.signals.begin()+randDisappear);
            }
        }
    }
}
