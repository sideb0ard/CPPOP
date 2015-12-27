#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>
#include <regex>

#include <portaudio.h>

#include "defjams.h"
#include "mixer.h"

extern Mixer mixer;

int isPrime(int n);
int primeyGen();
int setupAudio();
void env();
void exxy();
void fmy(int mfreq, int cfreq);
void interpret(std::string input_line);
void siney(int freq);
void stoprrr(int signalNum);
void timedSigGenStart(const std::string signal, int freq, int freq2);

#endif
