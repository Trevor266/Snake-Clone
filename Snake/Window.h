#ifndef _WINDOW_H_
#define _WINDOW_H_
#include <SDL.h>

class Window
{
public:
	Window(int width, int height);
	SDL_Window *getWindow();
	SDL_Surface *getWindowSurface();
	
private:
	SDL_Window *window;	
	SDL_Surface *windowSurface;
};

#endif