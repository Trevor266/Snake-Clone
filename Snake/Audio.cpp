#include "Audio.h"

//All this does is initialize all the audio stuff, because going in and
//reading the documentation for frequencies and crap is really annoying.

bool initializeAudio()
{
	bool success = true;

	if (!(SDL_INIT_AUDIO) < 0)
	{
		printf("Error intializing the audio subsystem, SDL_Error: %s\n\n", SDL_GetError());
		success = false;
	}
	else
	{
		printf("Audio subsystem initialized\n\n");
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048))
	{
		printf("Error intializing SDL_Mixer, Mix error: %s\n\n", Mix_GetError());
		success = false;
	}
	else
	{
		printf("SDL_Mixer initialized.\n\n");
	}
	return success;
}