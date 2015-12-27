#ifndef SOUNDB0ARD_
#define SOUNDB0ARD_

class Soundb0ard
{
protected:
    float vol = 0.0;
public:

    virtual float genNextSound() = 0;
    virtual std::string info() = 0;

    virtual float getVol()
    {
        return vol;
    }
    
    virtual void setVol(float volume)
    {
        if (volume <= 1.0) {
            if ( volume <= 0.0 ) {
                vol = 0.0;
            } else {
                vol = volume;
            }
        }
    }


};

#endif // SOUNDB0ARD_
