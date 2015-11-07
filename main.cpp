#include <cstdlib>
#include <iostream>
#include <thread>

#include <math.h>
#include <portaudio.h>
#include <unistd.h>

#include "defjams.h"
#include "sine.h"

using namespace std;


void exxy()
{
  cout << "\n\033[38;5;47mLater, ya val jerk...\033[0m\n" << endl;
  exit(0);
}

int siney() 
{
    PaError err;
    Sine sine;

    printf("PortAudio Test: output sine wave. SR = %d, BufSize = %d\n", SAMPLE_RATE, FRAMES_PER_BUFFER);
    
    err = Pa_Initialize();
    if( err != paNoError ) goto error;

    if (sine.open(Pa_GetDefaultOutputDevice()))
    {
        if (sine.start())
        {
            printf("Play for %d seconds.\n", NUM_SECONDS );
            Pa_Sleep( NUM_SECONDS * 1000 );

            sine.stop();
        }

        sine.close();
    }

    Pa_Terminate();
    printf("Test finished.\n");
    
    return err;

error:
    Pa_Terminate();
    fprintf( stderr, "An error occured while using the portaudio stream\n" );
    fprintf( stderr, "Error number: %d\n", err );
    fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
    return err;
  //while (1)
  //{
  //  cout << "beeeeeeee\n";
  //  usleep(2000000);
  //}
}

void interpret(string input_line)
{
  if (input_line.compare("sine") == 0) {
    cout << "SINEY!\n";
    thread {siney}.detach();
    //s1.join();
  }

}

void setupAudio()
{
  PaError err;
  err = Pa_Initialize();
  if( err != paNoError )
    cout << "BARFED\n";
}


int main()
{

  // setupAudio();

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
    
