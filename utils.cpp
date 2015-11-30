#include <cmath>
#include <iostream>
#include <regex>
#include <thread>

#include <portaudio.h>

#include "algae.h"
#include "defjams.h"
#include "mixer.h"
#include "utils.h"

//extern Mixer mixer;

using namespace std;

void exxy()
{
    cout << "\n\033[38;5;47mBEat it, ya val jerk...\033[0m\n" << endl;
    exit(0);
}

int primeyGen()
{
    // init randy
    srand (time(NULL));
    int randy = rand() % 720 + 140; // between 140 - 860 - mostly audible range
    std::cout << "Randy Num : " << randy << " // Is it prime?" << isPrime(randy) << std::endl;
    for ( ; randy <= 860 && !isPrime(randy); randy++) {}
    if (isPrime(randy))
        return randy;
    return 0;
}

int isPrime(int n)
{
    int i, sq, count = 0;
    if ( n == 1 || n == 2 )
        return true;
    sq = sqrt(n);
    for ( i = 2; i <= sq; i++ )
    {
        if (( n % i ) == 0)
            return false;
    }
    return true;
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

void siney(int freq)
{
  //Oscillator sine(freq);
  //Soundb0ard sbd(freq);
  mixer.signals.push_back(new Oscillator(freq));
}

void squmpy(int freq)
{
  //Oscillator sine(freq);
  //Soundb0ard sbd(freq);
  mixer.signals.push_back(new Sqump(freq));
}

void squmpdate(int sqid, int freq)
{
    Sqump *sqmp =  (Sqump *) mixer.signals[sqid];
    sqmp->mod.freq = freq;
    std::cout << "Squmpdated! : sqmp.mod.freq: " << sqmp->mod.freq << std::endl;

}

void sawy(int freq)
{
  //Oscillator sine(freq);
  //Soundb0ard sbd(freq);
  mixer.signals.push_back(new Sawtooth(freq));
}

void triy(int freq)
{
  //Oscillator sine(freq);
  //Soundb0ard sbd(freq);
  mixer.signals.push_back(new Triangle(freq));
}

void interpret(string input_line)
{
    string::size_type sz;
    smatch m;
    regex sn ("sine ([0-9]+)");
    if (regex_search (input_line, m, sn))
    {
        int freq = stoi(m[1], &sz);
        siney(freq);
    }

    regex sq ("sqump ([0-9]+)");
    if (regex_search (input_line, m, sq))
    {
        int freq = stoi(m[1], &sz);
        squmpy(freq);
    }

    regex sqch ("sq ([0-9]+) (mod|car) ([0-9]+)");
    if (regex_search (input_line, m, sqch))
    {
        int sq = stoi(m[1], &sz);
        int freq = stoi(m[3], &sz);
        std::cout << "Oooh, changing a sqump! for " << m[2] << "Freq!: " << freq << std::endl;
        squmpdate(sq, freq);
    }

    regex sw ("saw ([0-9]+)");
    if (regex_search (input_line, m, sw))
    {
        int freq = stoi(m[1], &sz);
        sawy(freq);
    }

    regex tr ("tri ([0-9]+)");
    if (regex_search (input_line, m, tr))
    {
        int freq = stoi(m[1], &sz);
        triy(freq);
    }

    if (input_line.compare("randy") == 0) {
        std::cout << "YEr randyNUm is " << primeyGen() << std::endl;
    }

    if (input_line.compare("primey") == 0) {
        Algae alg;
        std::cout << "Starting Primey generat0r..." << std::endl;
        std::thread {&Algae::Run, &alg}.detach();
    }

    regex pr ("prime ([0-9]+)");
    if (regex_search (input_line, m, pr))
    {
        int pn = stoi(m[1], &sz);
        std::cout << "Yer Prime search says... " << isPrime(pn) << std::endl;
    }

    regex stp ("stop ([0-9]+)");
    if (regex_search (input_line, m, stp))
    {
        int sn = stoi(m[1], &sz);
        mixer.signals.erase(mixer.signals.begin()+sn);
    }
    if (input_line.compare("end") == 0) {
        mixer.signals.clear();
    }
    if (input_line.compare("ps") == 0) {
        for ( int i = 0; i < mixer.signals.size(); i++) 
        {
            //cout << "Sine:" << i << " // Freq: " << mixer.signals[i].car.freq << endl;
            cout << "[" << i << "] " << mixer.signals[i]->info() << endl;
        }
    }
}
