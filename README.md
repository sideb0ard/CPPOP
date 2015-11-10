# CPPPOP

C++ Pop Pop

reimplementing my audio shell in C++

Build instructions:

Install PortAudio -- http://www.portaudio.com/

Do this:
g++ -std=c++11 -pthread -o CPPPOP main.cpp mixer.cpp oscillator.cpp utils.cpp -lportaudio

Run it. make sine waves.
