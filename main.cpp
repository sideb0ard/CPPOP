#include <iostream>
#include <thread>

#include <portaudio.h>

#include "bpmrrr.h"
#include "mixer.h"
#include "utils.h"

using namespace std;

Mixer mixer;
BPMrrr bpm;

int main()
{
  setupAudio();
  thread {&Mixer::goMix, &mixer}.detach();
  thread {&BPMrrr::Run, &bpm}.detach();

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
