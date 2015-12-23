#include <chrono>
#include <thread>

#include "bpmrrr.h"
#include "mixer.h"

extern Mixer mixer;

BPMrrr::BPMrrr() {}
void BPMrrr::Run()
{
    while (1)
    {
        //int sleepTime = (60000 / mixer.bpm) / 16;  // microTicks - 16 per BPM
        //std::cout << "bpm boopi - Inc'ing mixer.microtick.." << std::endl;
        sleeptime = (60000 / mixer.bpm) / 16;
        mixer.microtick++;
        //std::cout << "Mictic:::: " << mixer.microtick << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(sleeptime));
    }
}
