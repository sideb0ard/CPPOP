#include <cstdlib>
#include <iostream>
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

void siney()
{
  Oscillator sine;
  mixer.signals.push_back(sine);
  //float val;
  //while (1)
  //{
  //  val = sine.genNextSound();
  //  cout << "Ma valley " << val << endl;
  //  //usleep(20000);
  //}
}

void interpret(string input_line)
{
  if (input_line.compare("sine") == 0) {
    cout << "SINEY!\n";
    thread {siney}.detach();
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
    cout << "Get me! " << input_line;
  }

}
    
