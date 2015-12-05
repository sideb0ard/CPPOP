#include <iostream>
#include <thread>

#include <portaudio.h>

#include "bpmrrr.h"
#include "mixer.h"
#include "utils.h"

using namespace std;

Mixer mixer;
BPMrrr bpm;
vector<string> history;

int main()
{
  setupAudio();
  thread {&Mixer::goMix, &mixer}.detach();
  thread {&BPMrrr::Run, &bpm}.detach();

  string input_line;
  while (1)
  {
    char *buf;

    while ((buf = readline("\n #> "))!= NULL) {
    //cout << "\n" << COOL_COLOR_GREEN << "#> " << ANSI_COLOR_RESET;
    //getline(cin, input_line);
    //if ( cin.eof() )
    //  exxy();
        interpret(input_line);
    }

  }
}
