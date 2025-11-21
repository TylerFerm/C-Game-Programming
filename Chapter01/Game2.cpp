
// My version of Game.cpp that I created while following along with the textbook

#include "Game2.h"
#include <iostream>

const int thickness = 15;

Game2::Game2() : 
	mWindow(nullptr), 
	mIsRunning(true), 
	mRenderer(nullptr),
	mPaddlePos(Vector2{ 50, 384 }),
	mBallPos(Vector2{ 512, 384 }),
	mTicksCount(0)
{}

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

	// Create a renderer
	mRenderer = SDL_CreateRenderer(
		mWindow, // Window to create renderer for
		-1, // Which graphics driver to use, -1 means let SDL decide
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC // Flags for taking advantage of graphics hardware and enable vsync
	);

	// Check if the renderer initialized successfully
	if (!mRenderer) {
		SDL_Log("Failed to create renderer: %s", SDL_GetError);
		return false;
	}

	// Since both the library and window/renderer were succesful, return true
	return true;
}


void Game2::shutdown() {

	// Destory the provided window
	SDL_DestroyWindow(mWindow);

	// Destory the renderer
	SDL_DestroyRenderer(mRenderer);

	// Close SDL
	SDL_Quit();
}


void Game2::runLoop() {

	// While loop that keeps the game running
	while (mIsRunning) {
		processInput();
		updateGame();
		generateOutput();
	}
}


void Game2::processInput() {
	// Variable for holding the current event
	SDL_Event event;

	// While there are still events in the queue (SDL_PollEvent returns true if that is the case), process inputs
	while (SDL_PollEvent(&event)) {
		// Handle input based on the type recieved.
		switch (event.type) {
			
		// Quit the game
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}

		// Quitting by pressing escape

		// Get the state of the keyboard (an array that contains 1/0 values for each key indicating whether or not they are pressed down)
		const Uint8* state = SDL_GetKeyboardState(NULL);
		
		
		// If escape is pressed (checked using the SDL_Scancode for it), then end the main while loop
		if (state[SDL_SCANCODE_ESCAPE]) {
			// Stop the gamed
			mIsRunning = false;
		}
	}
}


void Game2::generateOutput() {
	// Step 1: Clear the back buffer to a color (the game's current buffer).
	
	// Specify the color
	SDL_SetRenderDrawColor(
		mRenderer,
		0, // R
		0, // G
		255, // B
		255 // A
	);

	// Clear the back buffer to the current draw color
	SDL_RenderClear(mRenderer);

	// Step 2: Draw the entire game scene
	
	// Change the draw color so it is not the same as the background
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	
	// Create the ball (converting the x, y coords from center to top left for SDL_Rect)
	SDL_Rect ball{
		static_cast<int>(mBallPos.x - thickness / 2),
		static_cast<int>(mBallPos.y - thickness / 2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &ball);

	// Draw the paddle
	SDL_Rect paddle{
		static_cast<int>(mPaddlePos.x - thickness / 2),
		static_cast<int>(mPaddlePos.y - thickness / 2),
		thickness,
		100
	};
	SDL_RenderFillRect(mRenderer, &paddle);
	
	// Create a rectangle with specific dimensions
	SDL_Rect wall{
		0, // Top left x
		0, // Top left y
		1024, // Width
		thickness, // Height
	};

	// Draw the top wall
	SDL_RenderFillRect(mRenderer, &wall);

	// Draw the bottom wall
	wall.y = 768 - thickness;
	SDL_RenderFillRect(mRenderer, &wall);

	// Draw the right wall
	wall.x = 1024 - thickness;
	wall.y = 0;
	wall.w = thickness;
	wall.h = 1024;
	SDL_RenderFillRect(mRenderer, &wall);

	// Step 3: Swap the front buffer and back buffer
	SDL_RenderPresent(mRenderer);
}


void Game2::updateGame() {
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
	

	// Delta time is the difference in ticks from last frame (converted to seconds)
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	// Update tick counts (for next frame)
	mTicksCount = SDL_GetTicks();

	// Clamp maximum delta time value
	if (deltaTime > 0.05f) { deltaTime = 0.05f; }

	// Update objects in game world as function of delta time
}