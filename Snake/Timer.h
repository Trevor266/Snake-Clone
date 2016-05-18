#ifndef _TIMER_H
#define _TIMER_H

//By using this header you can create timer objects that will let you time different events at different intervals
#include "SDL.h"

//This class allows us to set a frame rate and a number of updates we wish to perform
//during that frame rate, ex 60 frames with an 8 frame refresh rate means we want 8 frames
//to display a second, so we times the frames per second by the refresh rate to get the time
//interval we want to display a frame at.
class Timer
{

public:


	Timer(int fps, int updatesPerSecond);

	bool updateFrame();

	int getCurrentElapsedTime();

	//This is so that we can modify the refresh rate if we want to.
	void setNewRefreshRate(int fps, int updatesPerSecond);

private:

	int FPS;
	int refreshRate;
	int currentTime;
	int previousTime;

};


#endif