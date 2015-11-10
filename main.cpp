#include <iostream>
#include <thread>

#include <portaudio.h>

#include "mixer.h"

using namespace std;

Mixer mixer;

void exxy();
int setupAudio();
void siney(int freq);
void interpret(string input_line);

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
