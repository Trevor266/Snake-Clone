#include "Window.h"

//Initialize the window, here you can change the arguments you pass to the window creation,
//since you typically only have window it makes more sense to me to just go in once in a rare
//while and change the arguments in the constructor rather than pass a bunch of weird stuff
//to it. We also assign the window surface because we will definitly need that for anything
//related to textures or renderering in general.
Window::Window(int width, int height)
{
	window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
	windowSurface = SDL_GetWindowSurface(window);
}

//returns the window
SDL_Window *Window::getWindow()
{
	return window;
}

//returns the window format, the renderer needs this so it knows
//the screen format, etc.
SDL_Surface *Window::getWindowSurface()
{
	return windowSurface;
}