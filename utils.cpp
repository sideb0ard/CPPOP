#include <cmath>
#include <iostream>
#include <sstream>
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

void fmy(int carfreq, int modfreq)
{
  //Oscillator sine(freq);
  //Soundb0ard sbd(freq);
  mixer.signals.push_back(new Fm(carfreq, modfreq));
}

void fmupdate(int sqid, string osc, int freq)
{
    Fm *fm =  (Fm *) mixer.signals[sqid];
    fm->update(osc, freq);
    //if (osc == "mod")
    //    sqmp->mod.freq = freq;
    //else if (osc == "car")
    //    sqmp->car.freq = freq;
    //std::cout << "Fmupdated! : sqmp.mod.freq: " << sqmp->mod.freq << std::endl;

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

// trim from start
static inline std::string &ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

// trim at end
static inline std::string &rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

void interpret(string input_line)
{

    //size_t pos = 0;
    string::size_type sz;

    std::string token;
    std::stringstream stream(input_line);
    while(getline(stream, token, ',') ) {
        std::string ttoken = ltrim(rtrim(token));
        //cout << ltrim(rtrim(token)) << "YARLY" << endl;

        smatch m;
        regex sn ("sine ([0-9]+)");
        if (regex_search (ttoken, m, sn))
        {
            int freq = stoi(m[1], &sz);
            siney(freq);
        }

        regex sq ("fm ([0-9]+) ([0-9]+)");
        if (regex_search (ttoken, m, sq))
        {
            int cfreq = stoi(m[1], &sz);
            int mfreq = stoi(m[2], &sz);
            fmy(cfreq, mfreq);
        }

        regex sqch ("mfm ([0-9]+) (mod|car) ([0-9]+)");
        if (regex_search (ttoken, m, sqch))
        {
            int sq = stoi(m[1], &sz);
            int freq = stoi(m[3], &sz);
            std::cout << "Oooh, changing a fm! for " << m[2] << "Freq!: " << freq << std::endl;
            fmupdate(sq, m[2], freq);
        }

        regex sw ("saw ([0-9]+)");
        if (regex_search (ttoken, m, sw))
        {
            int freq = stoi(m[1], &sz);
            sawy(freq);
        }

        regex tr ("tri ([0-9]+)");
        if (regex_search (ttoken, m, tr))
        {
            int freq = stoi(m[1], &sz);
            triy(freq);
        }

        if (ttoken.compare("randy") == 0) {
            std::cout << "YEr randyNUm is " << primeyGen() << std::endl;
        }

        if (ttoken.compare("primey") == 0) {
            Algae alg;
            std::cout << "Starting Primey generat0r..." << std::endl;
            std::thread {&Algae::Run, &alg}.detach();
        }

        regex pr ("prime ([0-9]+)");
        if (regex_search (ttoken, m, pr))
        {
            int pn = stoi(m[1], &sz);
            std::cout << "Yer Prime search says... " << isPrime(pn) << std::endl;
        }

        regex stp ("stop ([0-9]+)");
        if (regex_search (ttoken, m, stp))
        {
            int sn = stoi(m[1], &sz);
            mixer.signals.erase(mixer.signals.begin()+sn);
        }
        if (ttoken.compare("end") == 0) {
            mixer.signals.clear();
        }
        if (ttoken.compare("ps") == 0) {
            for ( int i = 0; i < mixer.signals.size(); i++) 
            {
                //cout << "Sine:" << i << " // Freq: " << mixer.signals[i].car.freq << endl;
                cout << "[" << i << "] " << mixer.signals[i]->info() << endl;
            }
        }
    }
}
