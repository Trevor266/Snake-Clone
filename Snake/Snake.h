#ifndef _SNAKE_H_
#define _SNAKE_H_

#include "Texture.h"

class Snake
{

public:
	Snake(int width, int hegiht, int x, int y);

	//This will track the keystate which lets us divide up
	//events and movement
	void HandleEvent(SDL_Event &e);
	
	//Moves the snake
	void Move();

	//Renders the head of the snake
	void render(SDL_Renderer *renderer);
	
	//Checks collision with the level
	bool checkLevelCollision(int width, int height);

	//Checks collision with the head of the snake and
	//the body of the snake
	bool checkCollisionWithBody(int score);

	//Initializes the first segment of the array
	void initializeArray(SDL_Rect *snakeRect);

	//Adds a segment to the array.
	void addNewSegment(int score);

	//Renders all the segments in the array
	void renderSegements(int score, SDL_Renderer *renderer);

	//Updates the positions of every segment in the array
	void updateSegmentPoisitions(int score);
	
	//Returns the head of the snake
	SDL_Rect *getSnakeRectangle();

	//Returns the array of segments
	SDL_Rect *getSegmentArray();
	
	void resetSnake();
private:
	
	//Tracks the keystates for movement
	static bool keyStates[4];
	enum Buttons{ W, A, S, D };

	//Used for testing collision against the body of the snake with the head
	static bool collision;

	//player size stuff
	SDL_Rect snakeRectangle;
	int playerWidth, playerHeight, playerX, playerY;

	//speed of the player
	int playerXVelocity = 20;
	int playerYVelocity = 20;

	//Holds the segments of the snake
	SDL_Rect segmentArray[200];
};
#endif