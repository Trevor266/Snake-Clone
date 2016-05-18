#ifndef _FOOD_H_
#define _FOOD_H_
#include "Texture.h"

class Food
{

public:

	//Initialize the size of the food
	Food(int levelHeight, int levelWidth);

	//If there was a collision with the head of the snake
	bool checkCollisionWithSnake(SDL_Rect *snakeRectangle, int levelWidth, int levelHeight);
	
	//Check if the food rendered on the body of the snake, if it did we
	//redraw the food
	bool checkIfFoodRendersOnSnake(SDL_Rect rect[], int score);

	//Renders the food onto the screen
	void renderFood(SDL_Renderer *localRenderer);

	//Redraws the food in case we don't like where it got placed
	void redrawFood(int levelWidth, int levelHeight);
	


private:

	//Tracks the collision, has to be static to test through an entire array
	static bool collision;
	//The rect that will represent the attributes of the food
	SDL_Rect foodRect;



};

#endif