#include <chrono>
#include <iostream>
#include <thread>

#include "songone.h"
#include "utils.h"

Songone::Songone(){}

void Songone::Run()
{
    timedSigGenStart("fm", 80, 256);
    //randSleep = rand()
    std::this_thread::sleep_for(std::chrono::milliseconds(20000));
    timedSigGenStart("fm", 80, 253);
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    timedSigGenStart("fm", 80, 257);
    std::this_thread::sleep_for(std::chrono::milliseconds(7000));
    stoprrr(0);
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    stoprrr(0);
    timedSigGenStart("fm", 23, 300);
    stoprrr(0);
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    timedSigGenStart("fm", 23, 200);
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    timedSigGenStart("fm", 23, 100);
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    stoprrr(0);
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    stoprrr(0);
    std::this_thread::sleep_for(std::chrono::milliseconds(6000));
    stoprrr(0);

}
