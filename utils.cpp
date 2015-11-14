#include <iostream>
#include <regex>

#include <portaudio.h>

#include "defjams.h"
#include "mixer.h"

extern Mixer mixer;

using namespace std;

void exxy()
{
    cout << "\n\033[38;5;47mBEat it, ya val jerk...\033[0m\n" << endl;
    exit(0);
}

int setupAudio() 
{
    PaError err;

    printf("PortAudio Sizzurp: output sine wave. SR = %d, BufSize = %d\n", SAMPLE_RATE, FRAMES_PER_BUFFER);
    
    err = Pa_Initialize();
    if( err != paNoError ) goto error;

    return err;

error:
    Pa_Terminate();
    fprintf( stderr, "An error occured while using the portaudio stream\n" );
    fprintf( stderr, "Error number: %d\n", err );
    fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
    return err;
}

void siney(int freq)
{
  //Oscillator sine(freq);
  //Soundb0ard sbd(freq);
  mixer.signals.push_back(new Oscillator(freq));
}

void interpret(string input_line)
{
    string::size_type sz;
    smatch m;
    regex sn ("sine ([0-9]+)");
    if (regex_search (input_line, m, sn))
    {
        int freq = stoi(m[1], &sz);
        siney(freq);
    }

    regex stp ("stop ([0-9]+)");
    if (regex_search (input_line, m, stp))
    {
        int sn = stoi(m[1], &sz);
        mixer.signals.erase(mixer.signals.begin()+sn);
    }
    if (input_line.compare("end") == 0) {
        mixer.signals.clear();
    }
    if (input_line.compare("ps") == 0) {
        for ( int i = 0; i < mixer.signals.size(); i++) 
        {
            //cout << "Sine:" << i << " // Freq: " << mixer.signals[i].car.freq << endl;
            cout << mixer.signals[i]->info() << endl;
        }
    }
}
