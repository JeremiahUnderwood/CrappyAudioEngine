#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <fstream>
#include <cstring>
#include "AudioEngine.cpp"
#include <chrono>

int main(int argc, char** argv){
	
	const int updateTime = 5000000;
	int timeToNextUpdate = 5000000;
	auto time2 = std::chrono::system_clock::now();
	auto time1 = time2;
	unsigned long deltaTime;
	unsigned long displayDeltaTime;
	
	printf("hello world or somthing\n");
	AudioDevice device = AudioDevice();
	Sound tekken = Sound("myfile.wav");
	Sound duck = Sound("duck.wav");
	device.PlaySound(tekken);
	bool goober = true;
	while (true)
    {
    	time1 = time2;
    	time2 = std::chrono::system_clock::now();
    	deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(time2-time1).count();
    	timeToNextUpdate -= deltaTime;
    	if(timeToNextUpdate <= 0){
    		timeToNextUpdate = updateTime;
    		device.PlaySound(tekken);
    		printf("pointoffailure2");
    	}
    }
	return 0;
}
