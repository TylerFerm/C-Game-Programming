// My version of Game.h while I was following along with the textbook.

#pragma once

#include "SDL/SDL.h"

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

};