// My version of Game.h while I was following along with the textbook.

#pragma once

#include "SDL/SDL.h"

// Declare a vector that has both x and y components (a container for coords)
struct Vector2 {
	float x;
	float y;
};

class Game2
{
public:
	// Constructor
	Game2();

	// Initialize the game
	bool initialize();

	// Run the game loop until the game is over
	void runLoop();

	// Shutdown the game
	void shutdown();

private:

	// Helper functions for the game loop

	void processInput();

	void updateGame();

	void generateOutput();

	// Window created by SDL
	SDL_Window* mWindow;

	// Renderer to draw graphics
	SDL_Renderer* mRenderer;

	// Game should continue to run while this is true
	bool mIsRunning;

	// Paddle 1 coords position
	Vector2 mPaddlePosP1;

	// Direction of paddle 1
	int mPaddleDirP1;

	// Paddle 2 coords position
	Vector2 mPaddlePosP2;

	// Direction of paddle 2
	int mPaddleDirP2;

	// Ball coords position
	Vector2 mBallPos;

	// Ball velocity
	Vector2 mBallVel;

	// Keep track of the number of ticks
	Uint32 mTicksCount;
};