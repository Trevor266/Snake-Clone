/*02/03/2015 - Trevor Hart
* All code and algorithms were written 
* by Trevor Hart using SDL 2 and C/C++.
* This code may be used however you wish.
* This code may be redistributed freely
* by anyone however you must include this
* somewhere in the source code if you do. 
* The algorithms used were also created by 
* Trevor Hart, you may use them as a reference
* and even copy and paste however if you do
* so and distribute the software you must give credit
* to the creator of the algorithms, source code, etc.
* This game is completely free, you may 
* distribute it however you wish, you may sell
* this code as long as it is not an exact copy;
* that said, it would be nice to hear from you so
* if you want to do that then my e-mail 
* is TrevorHart66@yahoo.com. You
* should also mention somewhere that this
* was made with SDL since they only ask that
* you mention that you used their API.
*/
#include "Window.h"
#include "Texture.h"
#include "Audio.h"
#include "Snake.h"
#include "Food.h"
#include "Timer.h"

bool init()
{
	bool success = true;
	SDL_Init(SDL_INIT_VIDEO | IMG_INIT_PNG);
	return success;
}


int main(int argc, char *argv[])
{
	//The stuff that you have to have no matter what to do all the basics
	init();
	initializeAudio();
	Window window(600, 400);
	SDL_Surface *windowSurface = window.getWindowSurface();
	SDL_Surface *icon = IMG_Load("Images/SnakeIcon.png");
	SDL_SetWindowIcon(window.getWindow(), icon);
	SDL_Renderer *renderer = SDL_CreateRenderer(window.getWindow(), -1, SDL_RENDERER_ACCELERATED);

	//Music related stuff
	Mix_Chunk *pickup = Mix_LoadWAV("Sound/Effects/Pickup2.wav");

	//Game objects
	Snake snake(20, 20, 300, 200);
	Food food(600, 400);
	snake.initializeArray(snake.getSnakeRectangle());

	//count is just a control to let us redraw food
	//once, because for some weird reason it draws
	//offscreen on startup
	int count = 0;
	int score = 0;
	
	//Arguments are the fps and the number of frames to show in that fps
	//(  refreshRate = fps / x  )
	Timer movementTimer(60, 1);

	////This is all stuff related to in game dialog boxes////
	//buttons to select to quit or replay
	const SDL_MessageBoxButtonData gameOverButtons[] = {
		{0, 0, "Quit" },
		{0, 1, "Play Again" },
	};

	//Buttons to select the difficulty
	const SDL_MessageBoxButtonData difficultyButtons[] = {
		{ 0, 0, "Easy" },
		{ 0, 1, "Hard" },
	};

	//Color scheme for our message boxes
	const SDL_MessageBoxColorScheme colorScheme = {
		{ 
			{ 255, 0, 0 },
			
			{ 0, 255, 0 },
			
			{ 255, 255, 0 },
			
			{ 0, 0, 255 },
			
			{ 255, 0, 255 }
		}
	};

	//game over message box data
	const SDL_MessageBoxData gameOvermessageboxdata = {
		SDL_MESSAGEBOX_INFORMATION, 
		window.getWindow(), 
		"Game over!",
		"Would you like to try again?", 
		SDL_arraysize(gameOverButtons), 
		gameOverButtons, 
		&colorScheme 
	};

	//difficulty message box data
	const SDL_MessageBoxData difficultyMessageboxdata = {
		SDL_MESSAGEBOX_INFORMATION,
		window.getWindow(),
		"Snake",
		"Select a difficulty: ",
		SDL_arraysize(difficultyButtons),
		difficultyButtons,
		&colorScheme
	};

	//Says what button was pressed
	int buttonid;
	//This is to make sure that the difficulty selection only gets called once
	int messageShow = 0;
	////End of dialog box stuff////

	SDL_Event e;

	bool quit = false;
	
while (!quit)
{

	//Tracks whether or not player chose an option for dialog boxes
	bool DifficultyDescision = false;
	bool GameOverDescision = false;

	SDL_SetRenderDrawColor(renderer, 75, 75, 75, 0);

	SDL_RenderClear(renderer);

	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			quit = true;
		}
		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_ESCAPE)
			{
				quit = true;
			}
		}
		snake.HandleEvent(e);
	}
		
	//Every frame we want to update the movement and the positions of each segment
	if (movementTimer.updateFrame())
	{
		snake.Move();
		snake.updateSegmentPoisitions(score);
	}

	////Everything contained here is related to game over messages////
	//If the player collides with a wall
	if (snake.checkLevelCollision(600, 400))
	{

		while (!GameOverDescision)
		{
			
			SDL_ShowMessageBox(&gameOvermessageboxdata, &buttonid);

			if (buttonid == 0)
			{
				//They hit no, so don't do anything
				quit = true;
				GameOverDescision = true;
			}
			else if (buttonid == 1)
			{
				//They hit yes, so replay
				quit = false;
				//We reset the snake, see the .cpp file for more info
				snake.resetSnake();
				//reset the score
				score = 0;
				//Redraw the food
				food.redrawFood(600, 400);
				//Reinitialize the first element of the array
				snake.initializeArray(snake.getSnakeRectangle());

				messageShow = 0;
				GameOverDescision = true;
			}
		}

	}
	//Or if they collide with themselves
	if (snake.checkCollisionWithBody(score))
	{
		while (!GameOverDescision)
		{
			SDL_ShowMessageBox(&gameOvermessageboxdata, &buttonid);
			if (buttonid == 0)
			{
				//They hit no, so just exit the game
				quit = true;			
				GameOverDescision = true;
			}
			else if (buttonid == 1)
			{
				//They hit yes, so replay
				quit = false;
				//We reset the snake, see the .cpp file for more info
				snake.resetSnake();
				//reset the score
				score = 0;
				//Redraw the food
				food.redrawFood(600, 400);
				//Reinitialize the first element of the array
				snake.initializeArray(snake.getSnakeRectangle());

				messageShow = 0;

				GameOverDescision = true;
			}
		}
			
	}
		
	//What to do if food is picked up
	if (food.checkCollisionWithSnake(snake.getSnakeRectangle(), 600, 400))
	{
		snake.addNewSegment(score);
		Mix_PlayChannel(-1, pickup, 0);
		score++;
	}
	
	//Render the snake and segments
	snake.render(renderer);
	snake.renderSegements(score, renderer);

	while (food.checkIfFoodRendersOnSnake(snake.getSegmentArray(), score))
	{
		food.redrawFood(600, 400);
	}

	//The first time you draw food it draws slightly off screen,
	//so this is here to prevent that.
	if (count == 0)
	{
		food.redrawFood(600, 400);
		count++;
	}

	//Render stuff

	food.renderFood(renderer);
	SDL_RenderPresent(renderer);

	//If the difficulty hasn't been selected yt
	if (messageShow == 0)
	{

		while (!DifficultyDescision)
		{

			SDL_ShowMessageBox(&difficultyMessageboxdata, &buttonid);

			if (buttonid == 0)
			{
				//Change the games timing depending on the input
				movementTimer.setNewRefreshRate(60, 8);

				//incriment the messageShow variable so that this doesn't get shown again until
				//they hit replay
				messageShow++;
				DifficultyDescision = true;
				
			}
			if (buttonid == 1)
			{
				movementTimer.setNewRefreshRate(60, 4);
				messageShow++;
				DifficultyDescision = true;	
			}
		}
	}
}
	return 0;
}