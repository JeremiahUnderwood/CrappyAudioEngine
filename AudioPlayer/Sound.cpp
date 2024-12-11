#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <fstream>
#include <cstring>

class Sound{
	
	private:
		char* data = new char[0]; //actual audio data
		//formatting data
		int channels = 0;
		int sampleRate = 0;
		int bitsPerSample = 0;
		int dataSize = 0;
		float volume = 1;
		unsigned int bufferid, sourceid, format;
		//end formatting data
		
		int cStringToInt(char* buffer, int length) //for convinience and portablility. To decrease code size, it would possibly be best to have this in the main function or some other inlcude
		{
			int a = 0;
			for (int i = 0; i < length; i++)
				((char*)&a)[i] = buffer[i];
		    return a;
		}
		
	public:
		
		ALuint GetBuffer(){
			return bufferid;
		}
		
		ALuint GetSource(){
			return sourceid;
		}
		
		Sound(const char* filename){
			char buffer[4];
		    std::ifstream in(filename, std::ios::binary);
		    in.read(buffer, 4); //RIFF identifier
			if (strncmp(buffer, "RIFF", 4) != 0)
		    {
		    	std::cout << "this is not a valid WAVE file" << "\n";
		    }
		    else{
		    	in.read(buffer, 4);      //File Size
			    in.read(buffer, 4);      //WAVE //WAVE identifier
			    in.read(buffer, 4);      //Format
			    in.read(buffer, 4);      //block size (16)
			    in.read(buffer, 2);      //Audio format (Integer)
			    in.read(buffer, 2);      //Channels
				channels = cStringToInt(buffer, 2);
				in.read(buffer, 4);      //frequency/sample rate
				sampleRate = cStringToInt(buffer, 4);
				in.read(buffer, 4);      //bytes per second to read
				in.read(buffer, 2);      //bytes per block
			    in.read(buffer, 2);      //bits per sample
			    bitsPerSample = cStringToInt(buffer, 2);
			    in.read(buffer, 4);      //DATA identifier
				in.read(buffer, 4);      //data size
			    dataSize = cStringToInt(buffer, 4);
			    data = new char[dataSize];
			    in.read(data, dataSize);
			    
			    //load into buffers/sources
			    alGenBuffers(1, &bufferid);
			    if (channels == 1)
			    {
			        if (bitsPerSample == 8)
			        {
			            format = AL_FORMAT_MONO8;
			        }
			        else {
			            format = AL_FORMAT_MONO16;
			        }
			    }
			    else {
			        if (bitsPerSample == 8)
			        {
			            format = AL_FORMAT_STEREO8;
			        }
			        else {
			            format = AL_FORMAT_STEREO16;
			        }
			    }
			    alBufferData(bufferid, format, data, dataSize, sampleRate);
			    /*alGenSources(1, &sourceid);
			    alSourcei(sourceid, AL_BUFFER, bufferid);
			    alSourcef(sourceid, AL_GAIN, volume);*/
			    //end buffers/sources
			    
		    }
		}
		
		~Sound(){
			alDeleteSources(1, &sourceid);
    		alDeleteBuffers(1, &bufferid);
			delete[] data;
		}
};
