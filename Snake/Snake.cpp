#include"Snake.h"

//Keystates used for the movement
bool Snake::keyStates[4] = { false, false, false, false};

//This is static because we have to maintain the value each iteration of
//the for loop otherwise the previous data will be overwritten (for segment collision)
bool Snake::collision = true;


Snake::Snake(int width, int height, int x, int y)
{
	//Sets the intial values of the rect
	playerWidth = width;
	playerHeight = height;
	playerX = x;
	playerY = y;

	//Applies those values
	snakeRectangle.x = playerX;
	snakeRectangle.y = playerY;
	snakeRectangle.w = playerWidth;
	snakeRectangle.h = playerHeight;
}

void Snake::HandleEvent(SDL_Event &e)
{

	if (e.type == SDL_KEYDOWN)
	{
		//We don't want the player to be able to move down if they are 
		//currently moving up otherwise they would lose, so we ensure
		//that if they are moving up, we dont let them move down, same for
		//movement along the x axis
		if (e.key.keysym.sym == SDLK_w && keyStates[S] == false)
		{
			keyStates[W] = true;
			keyStates[A] = false;
			keyStates[S] = false;
			keyStates[D] = false;
		}
		if (e.key.keysym.sym == SDLK_a && keyStates[D] == false)
		{
			keyStates[A] = true;
			keyStates[W] = false;
			keyStates[S] = false;
			keyStates[D] = false;
		}
		if (e.key.keysym.sym == SDLK_s && keyStates[W] == false)
		{
			keyStates[S] = true;
			keyStates[A] = false;
			keyStates[W] = false;
			keyStates[D] = false;
		}
		if (e.key.keysym.sym == SDLK_d && keyStates[A] == false)
		{
			keyStates[D] = true;
			keyStates[A] = false;
			keyStates[S] = false;
			keyStates[W] = false;
		}
	}
	
}

//Move the player
void Snake::Move()
{
	if (keyStates[W] == true)
	{
		snakeRectangle.y -= playerXVelocity;
	}
	if (keyStates[S] == true)
	{
		snakeRectangle.y += playerYVelocity;
	}
	if (keyStates[A] == true)
	{
		snakeRectangle.x -= playerXVelocity;
	}
	if (keyStates[D] == true)
	{
		snakeRectangle.x += playerXVelocity;
	}
}

//This hideous method checks if the player collided with the level, we don't have
//to iterate though the segment array because the head is the only thing that can ever
//touch the wall anyway
bool Snake::checkLevelCollision(int width, int height)
{
	//we subtract or add 1 depending on the border being checked
	//because otherwise the player will lose if they get within
	//20 pixels of the border

	//return true if they hit a wall, otherwise return false
	if (snakeRectangle.x <= 0 - 1)
	{
		return true;
	}

	if (snakeRectangle.x >= width - snakeRectangle.w + 1)
	{
		return true;
	}

	if (snakeRectangle.y <= 0 - 1)
	{
		return true;
	}

	if (snakeRectangle.y >= height - snakeRectangle.h + 1)
	{
	
		return true;
	}

	else
	{
		return false;
	}

}

//This ones the ugliest of all, get ready for this...
bool Snake::checkCollisionWithBody(int score)
{

	//First off we have to get the sides of each rect we are testing
	//To save some overhead we initialize all local variables that don't change
	//outside of the for loop, this includes the initialization of the side variables
	//and the snake rectangle since there is only one snake rectangle

	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Assign values to snakeRectangle
	//Calculate the sides of rect B
	leftB = snakeRectangle.x;
	rightB = snakeRectangle.x + snakeRectangle.w ;
	topB = snakeRectangle.y ;
	bottomB = snakeRectangle.y + snakeRectangle.h ;

	//Now we create a temporary rect that will be used as a temporary
	//holding rect for each index of the segment array
	SDL_Rect tempRect;
	
	//We use the score here because that essentially tracks how many segments
	//there currently are, you could do this other ways, it's just how I did it.
	for (int i = 0; i <= score; i++)
	{
		//Assign the temporary rect to the current index we are iterating through
		tempRect = segmentArray[i];

		//Calculate the sides of rect A
		leftA = tempRect.x ;
		rightA = tempRect.x + tempRect.w;
		topA = tempRect.y ;
		bottomA = tempRect.y + tempRect.h;

		//Now the fun part, we HAVE to do this this way because if we don't we
		//wont be able to iterate though the whole array and we will get bugs;
		//First off we test all collisions, if all collisions are false then theres no
		//collision with that segment, however if there is a collision with any of the sides at any point
		//we break out of the for loop and return true to the main, otherwise the data will get over-written
		//and we wont get accurate collision detections
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

//Renders the head of the snake
void Snake::render(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 102, 0, 0);
	SDL_RenderFillRect(renderer, &snakeRectangle);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderDrawRect(renderer, &snakeRectangle);
}

//returns the head of the snake if we need it for anything
SDL_Rect *Snake::getSnakeRectangle()
{
	return &snakeRectangle;
}

//initialize the segment array
void Snake::initializeArray(SDL_Rect *snakeRect)
{
	//Since the score starts at zero, we will have to initialize the 0 index of the array,
	//otherwise we can't do it later.

	//temporary holding 
	SDL_Rect newSegment;

	//Assign the first segment to the right of the head
	newSegment.x = snakeRect->x - snakeRect->w ;
	newSegment.y = snakeRect->y;
	newSegment.w = 20;
	newSegment.h = 20;

	//assign this to the zero index of the array.
	segmentArray[0] = newSegment;
}

//This ones pretty ugly too but extremely important
//We have to make sure we add segments relative to the current direction
//of the movement, if we don't then we wont know where exactly to render the segment
//and we will get weird results
void Snake::addNewSegment(int score)
{
	//If the score is less than 1 we want to set the score to 1 because otherwise
	//we will be over-writting the 0 index of the segment array
	if (score <= 1)
	{
		score += 1;
	}
	//We need the old segment to position the new segment, so we have to subtract 1 from
	//score to get the correct index of the array
	SDL_Rect oldSegment = segmentArray[score - 1];

	//This will be the new rect we pop into the array
	SDL_Rect newSegment;

	//Setting the position relative to the old position and the direction of the movement
	if (keyStates[W] == true)
	{
		newSegment.x = snakeRectangle.x;
		newSegment.y = snakeRectangle.y + snakeRectangle.h;
		newSegment.w = snakeRectangle.w;
		newSegment.h = snakeRectangle.h;
	}

	if (keyStates[S] == true)
	{
		newSegment.x = snakeRectangle.x;
		newSegment.y = snakeRectangle.y - snakeRectangle.h ;
		newSegment.w = snakeRectangle.w;
		newSegment.h = snakeRectangle.h;
	}

	if (keyStates[A] == true)
	{
		newSegment.x = snakeRectangle.x + snakeRectangle.w ;
		newSegment.y = snakeRectangle.y;
		newSegment.w = snakeRectangle.w;
		newSegment.h = snakeRectangle.h;
	}

	if (keyStates[D] == true)
	{
		newSegment.x = snakeRectangle.x - snakeRectangle.w ;
		newSegment.y = snakeRectangle.y;
		newSegment.w = snakeRectangle.w;
		newSegment.h = snakeRectangle.h;
	}

	//Finally we add this to the array at the index specified relative
	//to the score
	segmentArray[score] = newSegment;

}

//Draws the entire array.
void Snake::renderSegements(int score, SDL_Renderer *renderer)
{
	static int colorFlag;
	
	//We have to iterate though the array to draw all of the rects
	for (int i = 0; i <= score; i++)
	{
		
		if (colorFlag == 1)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 0, 0);
			
		}
		else if (colorFlag == 2)
		{
			SDL_SetRenderDrawColor(renderer, 255, 0, 255, 0);
			
		}
		else if (colorFlag == 3)
		{
			SDL_SetRenderDrawColor(renderer, 0, 255, 255, 0);
			
		}
		SDL_RenderFillRect(renderer, &segmentArray[i]);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderDrawRect(renderer, &segmentArray[i]);
		
		if (colorFlag != 1 && colorFlag != 2 && colorFlag != 3)
		{
			colorFlag = 1;
		}
		else if (colorFlag == 1)
		{
			colorFlag = 2;
		}

		else if (colorFlag == 2)
		{
			colorFlag = 3;
		}

		else if (colorFlag == 3)
		{
			colorFlag = 1;
		}
	}

}

//This ones the most vital function of all, it's what makes this into snake
//When we redraw the snake, we only actually have to do three things, destroy the last
//segment, move the head up one, and redraw the segment into the first index of the array
void Snake::updateSegmentPoisitions(int score)
{
	//Since we're using arrays we'll have to actually push the array ourselves, that
	//way we can "delete" the last segment and redraw it in front of the snake
	for (int i = 0; i < score; i++)
	{
		//Takes the current index, and set it equal to the next index up
		segmentArray[i] = segmentArray[i + 1];
	}

	//This will assign this rect equal to the current index of the array
	SDL_Rect tempRect = segmentArray[score];

	//Now the imporatant part, we have to redraw the newest segment relative to the
	//direction of the motion, for example if the snake is moving up, you want to draw
	//the new segment at the exact same x position as the snakes head, but below the head
	//on the y axis, so we just have to do the math for each direction here.
	if (keyStates[W] == true)
	{
		tempRect.x = snakeRectangle.x;
		tempRect.y = snakeRectangle.y + snakeRectangle.h ;
		tempRect.w = snakeRectangle.w;
		tempRect.h = snakeRectangle.h;
	}
	if (keyStates[S] == true)
	{
		tempRect.x = snakeRectangle.x;
		tempRect.y = snakeRectangle.y - snakeRectangle.h ;
		tempRect.w = snakeRectangle.w;
		tempRect.h = snakeRectangle.h;
	}
	if (keyStates[A] == true)
	{
		tempRect.x = snakeRectangle.x + snakeRectangle.w;
		tempRect.y = snakeRectangle.y;
		tempRect.w = snakeRectangle.w;
		tempRect.h = snakeRectangle.h;
	}
	if (keyStates[D] == true)
	{
		tempRect.x = snakeRectangle.x - snakeRectangle.w ;
		tempRect.y = snakeRectangle.y;
		tempRect.w = snakeRectangle.w;
		tempRect.h = snakeRectangle.h;
	}

	//The temporary rect we were using gets put back into
	//the array
	segmentArray[score] = tempRect;
}

//This just returns the segment array if it is needed (it is in a few places)
SDL_Rect *Snake::getSegmentArray()
{
	return segmentArray;
}

void Snake::resetSnake()
{
	//Create a rect that is just empty to
	//reset each segment in the array, although this
	//technically doesn't reset them there's no way that
	//I can find to deallocate the rects
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;

	for (int i = 0; i < 200; i++)
	{
		//Reassign values to the array
		segmentArray[i] = rect;
	}

	//repostion the snake to the x and y you passed in
	snakeRectangle.x = 300;
	snakeRectangle.y = 200;

	//Reset the keystates
	keyStates[W] = false;
	keyStates[A] = false;
	keyStates[S] = false;
	keyStates[D] = false;
	
}