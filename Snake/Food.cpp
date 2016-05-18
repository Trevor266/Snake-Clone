#include "Food.h"
#include <ctime>

bool Food::collision = false;

//Initialize the size of the food to 5, the rand I chose was simply to keep the food from going
//off screen, I didn't want the food rendering too close to the borders
Food::Food(int levelWidth, int levelHeight)
{
	foodRect.w = 20;
	foodRect.h = 20;
	foodRect.x = rand() % levelWidth - 50;
	foodRect.y = rand() % levelHeight - 20;

}

//This will test collision with the level, it's pretty self explanitory how it works
bool Food::checkCollisionWithSnake(SDL_Rect *snakeRectangle, int levelWidth, int levelHeight)
{

	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = foodRect.x;
	rightA = foodRect.x + foodRect.w;
	topA = foodRect.y;
	bottomA = foodRect.y + foodRect.h;

	//Calculate the sides of rect B
	leftB = snakeRectangle->x;
	rightB = snakeRectangle->x + snakeRectangle->w;
	topB = snakeRectangle->y;
	bottomB = snakeRectangle->y + snakeRectangle->h;

	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}
	else
	{
		//If there was a collision, redraw the food
		levelWidth -= 30;
		levelHeight -= 30;
		foodRect.x = rand() % levelWidth + 1;
		foodRect.y = rand() % levelHeight + 1;
	}
	return true;
}


//Just redraws the food
void Food::redrawFood(int levelWidth, int levelHeight)
{
	srand(time(NULL));
	levelWidth -= 30;
	levelHeight -= 30;
	foodRect.x = rand() % levelWidth + 1;
	foodRect.y = rand() % levelHeight + 1;
}

//Renders the food to the screen
void Food::renderFood(SDL_Renderer *localRenderer)
{
	SDL_SetRenderDrawColor(localRenderer, 0, 255, 255, 0);
	SDL_RenderFillRect(localRenderer, &foodRect);
	SDL_SetRenderDrawColor(localRenderer, 0, 0, 0, 0);
	SDL_RenderDrawRect(localRenderer, &foodRect);
}


//Now this guy is the same as the head/tail collision, the main difference
//being that we have to pass the actual array to the method since the array of segments
//is no longer local to the class
bool Food::checkIfFoodRendersOnSnake(SDL_Rect rect[], int score)
{

	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;


	//Calculate the sides of rect B
	leftB = foodRect.x;
	rightB = foodRect.x + foodRect.w;
	topB = foodRect.y;
	bottomB = foodRect.y + foodRect.h;

	SDL_Rect tempRect;

	for (int i = 0; i <= score; i++)
	{
		tempRect = rect[i];

		//Calculate the sides of rect A
		leftA = tempRect.x;
		rightA = tempRect.x + tempRect.w;
		topA = tempRect.y;
		bottomA = tempRect.y + tempRect.h;

		if (bottomA <= topB)
		{
			collision = false;

		}

		else if (topA >= bottomB)
		{
			collision = false;

		}

		else if (rightA <= leftB)
		{
			collision = false;

		}

		else if (leftA >= rightB)
		{
			collision = false;

		}
		else
		{
			collision = true;
			break;
		}
		if (collision == true)
		{
			break;
		}
	}

	return collision;
}