#include <cstdlib>
#include <iostream>
#include <regex>
#include <thread>

#include <math.h>
#include <portaudio.h>
#include <unistd.h>

#include "defjams.h"
#include "mixer.h"
#include "oscillator.h"

using namespace std;

Mixer mixer;


void exxy()
{
    cout << "\n\033[38;5;47mLater, ya val jerk...\033[0m\n" << endl;
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
  Oscillator sine(freq);
  mixer.signals.push_back(sine);
}

void interpret(string input_line)
{
    string::size_type sz;
    smatch m;
    regex e ("sine ([0-9]+)");
    if (regex_search (input_line, m, e))
    {
        int freq = stoi(m[1], &sz);
        siney(freq);
    }

    if (input_line.compare("end") == 0) {
        mixer.signals.clear();
    }
    if (input_line.compare("ps") == 0) {
        cout << mixer.signals.size() << endl;
    }
}


int main()
{

  setupAudio();
  thread {&Mixer::goMix,&mixer}.detach();

  string input_line;
  while (1)
  {
    cout << "\n\033[38;5;47m#> \033[0m";
    getline(cin, input_line);
    if ( cin.eof() )
      exxy();

    interpret(input_line);
  }

}
    
