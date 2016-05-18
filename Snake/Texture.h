#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>


class Texture
{
	
public:

	//We pass in the path of the image we want to load and the renderer, the renderer
	//has to be passed because just trust me on this one, using a renderer local to a class
	//is a complete disaster.
	Texture(std::string path, SDL_Renderer *localRenderer);

	//Returns the texture
	SDL_Texture *getTexture();

	

private:

	std::string path;

	SDL_Renderer *classRenderer;
	SDL_Texture *classTexture;

};



#endif