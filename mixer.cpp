#include <cstdlib>
#include <iostream>

#include <math.h>

#include "defjams.h"
#include "mixer.h"


Mixer::Mixer() : stream(0), left_phase(0), right_phase(0)
{
    /* initialise sinusoidal wavetable */
    for( int i=0; i<TABLE_SIZE; i++ )
    {
        mixer[i] = (float) sin( ((double)i/(double)TABLE_SIZE) * M_PI * 2. );
    }

    sprintf( message, "No Message" );
}

bool Mixer::open(PaDeviceIndex index)
{
    PaStreamParameters outputParameters;

    outputParameters.device = index;
    if (outputParameters.device == paNoDevice) {
        return false;
    }

    outputParameters.channelCount = 2;       /* stereo output */
    outputParameters.sampleFormat = paFloat32; /* 32 bit floating point output */
    outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;

    PaError err = Pa_OpenStream(
        &stream,
        NULL, /* no input */
        &outputParameters,
        SAMPLE_RATE,
        FRAMES_PER_BUFFER,
        paClipOff,      /* we won't output out of range samples so don't bother clipping them */
        &Mixer::processAudio,
        this            /* Using 'this' for userData so we can cast to Mixer* in paCallback method */
        );

    if (err != paNoError)
    {
        /* Failed to open stream to device !!! */
        return false;
    }

    err = Pa_SetStreamFinishedCallback( stream, &Mixer::paStreamFinished );

    if (err != paNoError)
    {
        Pa_CloseStream( stream );
        stream = 0;

        return false;
    }

    return true;
}

bool Mixer::close()
{
    if (stream == 0)
        return false;

    PaError err = Pa_CloseStream( stream );
    stream = 0;

    return (err == paNoError);
}


bool Mixer::start()
{
    if (stream == 0)
        return false;

    PaError err = Pa_StartStream( stream );

    return (err == paNoError);
}

bool Mixer::stop()
{
    if (stream == 0)
        return false;

    PaError err = Pa_StopStream( stream );

    return (err == paNoError);
}

/* The instance callback, where we have access to every method/variable in object of class Mixer */
int Mixer::paCallbackMethod(const void *inputBuffer, void *outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags)
{
    float *out = (float*)outputBuffer;
    unsigned long i;

    (void) timeInfo; /* Prevent unused variable warnings. */
    (void) statusFlags;
    (void) inputBuffer;

    for( i=0; i<framesPerBuffer; i++ )
    {
        *out++ = mixer[left_phase];  /* left */
        *out++ = mixer[right_phase];  /* right */
        left_phase += 1;
        if( left_phase >= TABLE_SIZE ) left_phase -= TABLE_SIZE;
        right_phase += 3; /* higher pitch so we can distinguish left and right. */
        if( right_phase >= TABLE_SIZE ) right_phase -= TABLE_SIZE;
    }

    return paContinue;

}

/* This routine will be called by the PortAudio engine when audio is needed.
** It may called at interrupt level on some machines so don't do anything
** that could mess up the system like calling malloc() or free().
*/
int Mixer::processAudio( const void *inputBuffer, void *outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void *userData )
{
    /* Here we cast userData to Mixer* type so we can call the instance method paCallbackMethod, we can do that since 
       we called Pa_OpenStream with 'this' for userData */
    return ((Mixer*)userData)->paCallbackMethod(inputBuffer, outputBuffer,
        framesPerBuffer,
        timeInfo,
        statusFlags);
}


void Mixer::paStreamFinishedMethod()
{
    printf( "Stream Completed: %s\n", message );
}

/*
 * This routine is called by portaudio when playback is done.
 */
void Mixer::paStreamFinished(void* userData)
{
    return ((Mixer*)userData)->paStreamFinishedMethod();
}
