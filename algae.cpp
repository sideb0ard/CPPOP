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
    //int randDisappear;
    // from http://www.phy.mtu.edu/~suits/notefreqs.html
    float weeNotes [] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    float notes [] = { 174.61, 185.00, 196.00, 207.65, 220.00, 233.08, 246.94, 261.63, 261.63, 277.18, 293.66, 311.13, 329.63, 349.23, 369.99, 392.00, 415.30, 440.00, 466.16, 493.88, 523.25, 554.37, 587.33, 622.25, 659.25, 698.46, 739.99, 783.99, 830.61, 880.00 };
                       
    while (1)
    {
        if (prev == (mixer.microtick % 16)  ) // % 16)
        {
            // all good
        } else {
            //std::cout << "PREV:" << prev <<  " // SHACK-a-LACK! ticking!" << mixer.microtick << std::endl;
            prev = mixer.microtick % 16;
            if ( isPrime(mixer.microtick) && (rand() % 10 >= 9))
            {
                std::cout << "BOOYA! Gonna spin a SINE O' " << mixer.microtick << ".. There are this many signals: " << mixer.sigSize() << std::endl;
                int cfreq = weeNotes[(rand() % 23) + 1];
                int mfreq = notes[(rand() % 30) + 1];
                std::thread t(timedSigGenStart, "fm", cfreq, mfreq); //.detach();
                t.detach();
                //siney(primeyGen());
                //siney(notes[noteNum]);

            }
            if (mixer.sigSize() > 2 && (rand() % 5 > 3)) // more than two signals, and 1 in 8 chance 
            {
                int sn = rand() % mixer.sigSize();
                stoprrr(sn); 
                std::cout << "Made a disappearance..." << std::endl;
                //mixer.signals.erase(mixer.signals.begin()+randDisappear);
            }
        }
    }
}
