
// My version of Game.cpp that I created while following along with the textbook

#include "Game2.h"

Game2::Game2() : mWindow(nullptr), mIsRunning(true) {}

bool Game2::initialize() {

	// Initialize the SDL library (initializing the video subsystem in the parameter).
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);

	// Check to make sure that initialization was successful
	if (sdlResult != 0) {
		
		// This log function is used to output messages to the console in SDL.
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError);
		return false;
	}

	// Create a window
	mWindow = SDL_CreateWindow(
		"Game Programming", // Window Title
		100, // Top left x-coordinate of window
		100, // Top left y-coordinate of window
		1024, // Width of window
		768, // Height of window
		0 // Falgs - 0 means no flags set
		);

	// Check to make sure the window was created properly
	if (!mWindow) {
		SDL_Log("Failed to create window: %s", SDL_GetError);
		return false;
	}

	// Since both the library and window were succesful, return true
	return true;
}


void Game2::shutdown() {

	// Destory the provided window
	SDL_DestroyWindow(mWindow);

	// Close SDL
	SDL_Quit();
}


void Game2::runLoop() {

	// While loop that keeps the game running
	while (mIsRunning) {
		//processInput();
		//updateGame();
		//generateOutput();
	}
}