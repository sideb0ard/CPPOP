#ifndef MIXER_H_
#define MIXER_H_

#include <vector>
#include <portaudio.h>

#include "envelope.h"
#include "fm.h"
#include "oscillator.h"
#include "soundb0ard.h"


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
    int microtick; // 16 per bpm
//    int sleeptime; // time between microticks - (6000ms / bpm) / 16 microticks

    //std::vector<Oscillator> signals;
    std::vector<Soundb0ard*> signals;
    std::vector<Envelope*> envelopes;

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
