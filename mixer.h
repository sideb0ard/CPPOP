#ifndef MIXER_H_
#define MIXER_H_

#include <vector>
#include <portaudio.h>

#include "oscillator.h"
#include "sawtooth.h"
#include "soundb0ard.h"
#include "sqump.h"
#include "triangle.h"


class Mixer
{
public:
    Mixer();
    bool open(PaDeviceIndex index);
    bool close();
    bool start();
    bool stop();
    void goMix();
    int sigSize();

    int bpm;
    int microtick; // 16 x bpm

    //std::vector<Oscillator> signals;
    std::vector<Soundb0ard*> signals;

private:
    /* The instance callback, where we have access to every method/variable in object of class Mixer */
    int paCallbackMethod(const void *inputBuffer, void *outputBuffer,
        unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags statusFlags);

    /* This routine will be called by the PortAudio engine when audio is needed.
    ** It may called at interrupt level on some machines so don't do anything
    ** that could mess up the system like calling malloc() or free().
    */
    static int processAudio( const void *inputBuffer, void *outputBuffer,
        unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags statusFlags,
        void *userData );
    
    void paStreamFinishedMethod();


    static void paStreamFinished(void* userData);

    PaStream *stream;
};

#endif // MIXER_H
