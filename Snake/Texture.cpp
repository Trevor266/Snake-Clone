#include "Texture.h"

//Rather than have the constructor set local variables, I just have it do everything,
//That way it keeps the amount of methods we have to call smaller and it's not really any
//more expensive either way so why not?
Texture::Texture(std::string Imagepath, SDL_Renderer *localRenderer)
{
	classRenderer = localRenderer;
	path = Imagepath;

	SDL_Surface *surface = NULL;

	surface = IMG_Load(path.c_str());
	
		if (surface == NULL)
		{
			printf("Unable to load image to surface, IMG_Error: %s\n", IMG_GetError());
		}
		else
		{
			classTexture = NULL;
			classTexture = SDL_CreateTextureFromSurface(classRenderer, surface);
			if (classTexture == NULL)
			{
				printf("Unable to create texture from surface, SDL_Error: %s\n", SDL_GetError());
			}
		}

		SDL_FreeSurface(surface);
}

//Returns the texture
SDL_Texture *Texture::getTexture()
{
	return classTexture;
}