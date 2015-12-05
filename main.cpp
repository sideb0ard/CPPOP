#include <iostream>
#include <thread>

#include <readline/readline.h>
#include <readline/history.h>
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

  char *buf;
  std::string prompt = std::string("\n") + COOL_COLOR_GREEN + "#> " + ANSI_COLOR_RESET;

  while ((buf = readline(prompt.c_str()))!= NULL) {
    if (buf[0] != 0)
        add_history(buf);
    interpret(buf);
  }

  exxy();

}
