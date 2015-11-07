#include <portaudio.h>


class Sine
{
public:
    Sine();
    bool open(PaDeviceIndex index);
    bool close();
    bool start();
    bool stop();

private:
    /* The instance callback, where we have access to every method/variable in object of class Sine */
    int paCallbackMethod(const void *inputBuffer, void *outputBuffer,
        unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags statusFlags);

    /* This routine will be called by the PortAudio engine when audio is needed.
    ** It may called at interrupt level on some machines so don't do anything
    ** that could mess up the system like calling malloc() or free().
    */
    static int paCallback( const void *inputBuffer, void *outputBuffer,
        unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags statusFlags,
        void *userData );
    
    void paStreamFinishedMethod();
    /*
     * This routine is called by portaudio when playback is done.
     */
    static void paStreamFinished(void* userData);

    PaStream *stream;
    float sine[TABLE_SIZE];
    int left_phase;
    int right_phase;
    char message[20];
};
