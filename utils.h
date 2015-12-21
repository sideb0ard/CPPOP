#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>
#include <regex>

#include <portaudio.h>

#include "defjams.h"
#include "mixer.h"

extern Mixer mixer;

void exxy();
int isPrime(int n);
int setupAudio();
int primeyGen();
void siney(int freq);
void sawy(int freq);
void triy(int freq);
void env();
void interpret(std::string input_line);

#endif
