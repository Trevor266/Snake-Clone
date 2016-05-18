#include "Timer.h"

//Pass the frames per second you desire, and the number of
//frame updates you want displayed within that frame rate.
Timer::Timer(int fps, int updatesPerSecond)
{
	FPS = fps;
	refreshRate = 1000 / FPS * updatesPerSecond;
	currentTime = SDL_GetTicks();
}

//Checks to see if it is time to update the screen based off the fps and the
//set number of frames to display per refresh cycle, ex.
//If FPS were 60, and we want 8 refreshes in those 60 frames,
//We set the refresh rate to 1000miliseconds / 60 * 8
bool Timer::updateFrame()
{
	//This will insure that the time is always consistent
	currentTime = SDL_GetTicks() - previousTime;

	if (currentTime / refreshRate)
	{
		previousTime += currentTime;
		return true;
	}

	else
	{
		return false;
	}
}

//This is being used as a way to update the refresh rate if for example
//the player is sprinting.
void Timer::setNewRefreshRate(int fps, int updatesPerSecond)
{
	FPS = fps;
	refreshRate = 1000 / FPS * updatesPerSecond;
	currentTime = SDL_GetTicks();
}