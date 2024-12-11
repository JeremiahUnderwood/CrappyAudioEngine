#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <fstream>
#include <cstring>
#include "Sound.cpp"

class AudioDevice{
	
	private:
		ALCdevice* device;
		ALCcontext* context;
		unsigned int sourceid;
		
	public:
		
		void PlaySound(Sound sound){
			alSourcei(sourceid, AL_BUFFER, sound.GetBuffer());
			alSourcef(sourceid, AL_GAIN, 1);
		    alSourcePlay(sourceid);
		    
		}
		
		void StopSound(Sound sound){
			//alGenSources(1, &sourceid);
			//alSourcei(sourceid, AL_BUFFER, sound.GetBuffer());
			//alSourcef(sourceid, AL_GAIN, 1);
			alSourcei(sourceid, AL_BUFFER, AL_NONE);
			alSourceStop(sourceid);
			printf("pointoffailure1");
		}
		
		AudioDevice(){
			device = alcOpenDevice(NULL);
		    if (device == NULL)
		    {
		        std::cout << "ERROR: cannot open sound card\n";
		    }
		    context = alcCreateContext(device, NULL);
		    if (context == NULL)
		    {
		        std::cout << "ERROR: cannot open context\n";
		    }
		    alcMakeContextCurrent(context);
		    alGenSources(1, &sourceid);
		}
		
		~AudioDevice(){
			alcDestroyContext(context);
    		alcCloseDevice(device);
		}
	
};
