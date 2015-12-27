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
    int err = Pa_Terminate();
    if( err != paNoError )
           printf(  "PortAudio error: %s\n", Pa_GetErrorText( err ) );
    cout << "\n" << COOL_COLOR_GREEN << "Beat it, ya val jerk...\n" << ANSI_COLOR_RESET << endl;
    exit(0);
}

int primeyGen()
{
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
    int i, sq;
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

    printf(ANSI_COLOR_MAGENTA "PortAudio Sizzurp: output sine wave. SR = %d, BufSize = %d\n" ANSI_COLOR_RESET, SAMPLE_RATE, FRAMES_PER_BUFFER);
    
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

void timedSigGenStart(const string signal, int freq, int freq2)
{
    do {} while (mixer.microtick % 16 != 0);
    std::cout << "Starting a " << signal << " at freq " << freq << std::endl;
    if (signal.compare("sine") == 0) 
        siney(freq);
    if (signal.compare("env") == 0) 
        env();
    if (signal.compare("fm") == 0) 
        fmy(freq, freq2);
}

void stoprrr(int signalNum)
{
    int sleeptime = 5;
    float volly = mixer.signals[signalNum]->getVol();
    //std::cout << "ENTERED Vol now For " << signalNum << " // Volume : " << mixer.signals[signalNum]->vol << std::endl;
    while ( mixer.signals[signalNum]->getVol() > 0.0) {
        volly -= 0.001;
        mixer.signals[signalNum]->setVol(volly);
        //std::cout << "Mictic:::: " << mixer.microtick << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(sleeptime));
    }
    mixer.signals.erase(mixer.signals.begin()+signalNum);
    std::cout << "Shut down a pesky signal\n";
}

void startrrr(int signalNum)
{
    std::cout << "Starting a... starting a signal\n";
    int sleeptime = 5;
    float volly = mixer.signals[signalNum]->getVol();
    std::cout << "ENTERED Vol now For " << signalNum << " // Volume : " << mixer.signals[signalNum]->getVol() << std::endl;
    while ( mixer.signals[signalNum]->getVol() < 0.8) {
        std::cout << "Still adding 0.001. Volume is " << mixer.signals[signalNum]->getVol() << std::endl;
        volly += 0.001;
        mixer.signals[signalNum]->setVol(volly);
        //std::cout << "Mictic:::: " << mixer.microtick << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(sleeptime));
    }
    //mixer.signals.erase(mixer.signals.begin()+signalNum);
    std::cout << "Finished starting a signal\n";
}

void siney(int freq)
{
  mixer.signals.push_back(new Oscillator(freq));
  std::thread t(startrrr, mixer.signals.size() - 1); //.detach();
  t.detach();
}

void fmy(int carfreq, int modfreq)
{
  mixer.signals.push_back(new Fm(carfreq, modfreq));
  std::thread t(startrrr, mixer.signals.size() - 1); //.detach();
  t.detach();
}

void fmupdate(int sqid, string osc, int freq)
{
    // need some error checking here before casting
    Fm *fm =  (Fm *) mixer.signals[sqid];
    fm->update(osc, freq);
}

void env()
{
  mixer.envelopes.push_back(new Envelope());
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

    string::size_type sz;

    std::string token;
    std::stringstream stream(input_line);

    // comma separated command input
    while(getline(stream, token, ',') ) {

        std::string ttoken = ltrim(rtrim(token));
        smatch m;

        regex sgn ("(sine|saw|tri) ([0-9]+)");
        if (regex_search (ttoken, m, sgn))
        {

            string signal = m[1];
            int freq = stoi(m[2], &sz);
            std::thread t(timedSigGenStart, signal, freq, 0); //.detach();
            t.detach();
        }

        regex sq ("fm ([0-9]+) ([0-9]+)");
        if (regex_search (ttoken, m, sq))
        {
            int cfreq = stoi(m[1], &sz);
            int mfreq = stoi(m[2], &sz);
            std::thread t(timedSigGenStart, "fm", cfreq, mfreq); //.detach();
            t.detach();

        }

        regex sqch ("mfm ([0-9]+) (mod|car) ([0-9]+)");
        if (regex_search (ttoken, m, sqch))
        {
            int sq = stoi(m[1], &sz);
            int freq = stoi(m[3], &sz);
            std::cout << "Oooh, changing a fm! for " << m[2] << "Freq!: " << freq << std::endl;
            fmupdate(sq, m[2], freq);
        }

        if (ttoken.compare("env") == 0) {
            std::thread t(timedSigGenStart, ttoken, 0.0, 0);
            t.detach();
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

        regex bpmrrr ("bpm ([0-9]+)");
        if (regex_search (ttoken, m, bpmrrr))
        {
            int bpm = stoi(m[1], &sz);
            mixer.bpm = bpm;
            std::cout << "Changing BPM to " << bpm << std::endl;
        }

        regex stp ("stop ([0-9]+)");
        if (regex_search (ttoken, m, stp))
        {
            int sn = stoi(m[1], &sz);
            if (sn < mixer.sigSize()) {
                std::thread t(stoprrr, sn); //.detach();
                t.detach();
            }
            else
                printf("Pull the other one, son!\n");
        }
        if (ttoken.compare("end") == 0) {
            mixer.signals.clear();
        }
        if (ttoken.compare("ps") == 0) {
            cout << ANSI_COLOR_CYAN << "\n[*************** SINE WAVVEY ******************]\n" << ANSI_COLOR_RESET;
            cout << "    BPM: " << mixer.bpm << " MicroTick: " << mixer.microtick << "\n\n";
            for ( int i = 0; i < mixer.signals.size(); i++) 
            {
                cout << "[" << i << "] " << mixer.signals[i]->info() << endl;
            }
            for ( int i = 0; i < mixer.envelopes.size(); i++) 
            {
                cout << "[" << i << "] " << mixer.envelopes[i]->info() << endl;
            }
        }
    }
}
