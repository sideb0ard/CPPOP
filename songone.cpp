#include <chrono>
#include <iostream>
#include <thread>

#include "songone.h"
#include "utils.h"

Songone::Songone(){}

void Songone::Run()
{
    float weeNotes [] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    float notes [] = { 174.61, 185.00, 196.00, 207.65, 220.00, 233.08, 246.94, 261.63, 261.63, 277.18, 293.66, 311.13, 329.63, 349.23, 369.99, 392.00, 415.30, 440.00, 466.16, 493.88, 523.25, 554.37, 587.33, 622.25, 659.25, 698.46, 739.99, 783.99, 830.61, 880.00 };
    int sleepyTime;
    int mody;

    // intro
    timedSigGenStart("fm", 80, 256);
    sleepyTime = rand() % 30000;
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepyTime));
    if ((rand() % 10) >= 9)
      timedSigGenStart("fm", 80, 253);
    else 
      timedSigGenStart("fm", 80, 257);

    sleepyTime = rand() % 2000;
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepyTime));

    mody = notes[rand() % 30];
    timedSigGenStart("fm", 23, mody);
    sleepyTime = rand() % 4000;
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepyTime));

    stoprrr(0); // three running, this stops one, and brings to two
    sleepyTime = rand() % 5000;
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepyTime));

    stoprrr(0); // two running, this stops one, and brings to one
    sleepyTime = rand() % 5000;
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepyTime));

    sleepyTime = rand() % 5000;
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepyTime));
    mody = notes[rand() % 30];
    timedSigGenStart("fm", 27, mody);

    sleepyTime = rand() % 5000;
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepyTime));
    stoprrr(0); // three running, this stops one, and brings to two


}
