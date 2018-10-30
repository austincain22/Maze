#include "Sounds.h"
#include <iostream>
using namespace std;

ISoundEngine* engine = createIrrKlangDevice();


Sounds::Sounds()
{
    //ctor
}

Sounds::~Sounds()
{
    //dtor
    engine->drop();
}


void Sounds::playMusic(char* file)
{
    engine->play2D(file,true);
}


void Sounds::playSound(char* file)
{
    engine->play2D(file,false,false);
}


void Sounds::stopAllSounds()
{
    engine->stopAllSounds();
}


int Sounds::initSounds()
{
    if(!engine){
        std::cout << "Could not start the engine\n";
        return 0;
    }
    stopAllSounds();
    return 1;
}
