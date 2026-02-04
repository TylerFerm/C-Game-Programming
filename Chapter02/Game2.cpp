// Game2.cpp

#include "Game2.h"
#include "SDL/SDL_image.h"
#include <algorithm>
#include "Actor2.h"
#include "SpriteComponent2.h"
#include "BGSpriteComponent2.h"
#include "Ship.h" // TODO: Change to Ship2 when it is made

Game2::Game2()
	: window(nullptr)
	, renderer(nullptr)
	, isRunning(nullptr)
	, updatingActors(false)
{}


bool Game2::initialize() {
	// Initialize the SDL library
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		// Log the error if SDL_Init failed
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// Create a window for the game to use
	window = SDL_CreateWindow("Chapter 2 Game", 100, 100, 1024, 768, 0);

	// Check if creating the window failed
	if (!window) {
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	// Create a renderer for the game to use
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	// Check if creating the renderer failed
	if (!renderer) {
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	// Load the image libraries and prepare them for use
	if (IMG_Init(IMG_INIT_PNG) == 0) {
		SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
		return false;
	}

	// Create assets related to the game
	loadData();

	// Get the number of ticks
	ticksCount = SDL_GetTicks();

	return true;
}


void Game2::runLoop() {
	// Keep the game loop running as long as needed
	while (isRunning) {
		processInput();
		updateGame();
		generateOutput();
	}
}


void Game2::processInput() {
	// Check to see if a quit button is pressed (as an event)
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		// Look for specifically the quit type of event
		switch (event.type)
		{
			case SDL_QUIT:
				isRunning = false;
				break;
		}
	}

	// Check if the escape key is pressed and end the game
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE]) {
		isRunning = false;
	}

	// Process ship input
	// ship->processKeyboard(state)
}


void Game2::updateGame() {
	// Logic in one sentence:
	// Caps the game to ~60 FPS, calculates how much real time passed since the last frame, ...
	// ...converts it into seconds for physics/movement, and clamps it to prevent simulation instability.
	
	// Do nothing until 16ms has passed since the last frame (capping at ~60 FPS - 1000ms/60FPS ~= 16.7 ms)
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + 16));

	// Compute deltatime (time since last frame in seconds)
	// This is done so movement becomes frame-rate independent. Ex) position += velocity * deltatime
	float deltatime = (SDL_GetTicks() - ticksCount) / 1000.0f;

	// If the game freezes for a moment, cap deltatime so objects don't teleport, collision doesn't break, etc.
	// ~20 FPS minimum simulation step
	if (deltatime > 0.05f) { deltatime = 0.05f; }

	// Store the time for the next frame
	ticksCount = SDL_GetTicks();

	// Update all actors in the vector of actors
	updatingActors = true;
	for (auto actor : actors) {
		// Update actors based on deltatime
		actor->update(deltatime);
	}

	// Move any pending actors to the vector of actors
	for (auto pending : pendingActors) {
		actors.emplace_back(pending);
	}
	pendingActors.clear();

	// Store all the dead actors in a temp vector so we can safely remove them from actors
	std::vector<Actor*> deadActors;
	for (auto actor : actors) {
		if (actor->getState() == Actor2::Dead) {
			deadActors.emplace_back(actor);
		}
	}

	// Remove the dead actors from the vector of actors
	for (auto actor : deadActors) { delete actor; }
}


void Game2::generateOutput() {
	// Clear the renderer
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// Draw all the sprite components
	for (auto sprite : sprites) {
		sprite->draw(renderer);
	}

	// Update the screen with the rendering performed
	SDL_RenderPresent(renderer);
}


void Game2::loadData() {

}


void Game2::unloadData() {
	// Delete the actors
	// Because ~Actor2 calls removeActor, use a different style loop
	while (!actors.empty()) { delete actors.back(); }

	// Destroy all the textures
	for (auto texture : textures) { SDL_DestroyTexture(texture.second); }

	// Clear the textures vector
	textures.clear();
}


SDL_Texture* Game2::getTexture(const std::string& fileName) {
	// Variable to save the texture once it is either found in the map or loaded from file
	SDL_Texture* texture = nullptr;

	// Create an iterator that will try and find the texture associated with the fileName
	auto iter = textures.find(fileName);

	// If the filename was found, return that texture (second)
	if (iter != textures.end()) { texture = iter->second; }
	
	// Otherwise, add the texture and fileName to the map of textures
	else {
		// Load the surface from the file
		SDL_Surface* surface = IMG_Load(fileName.c_str());
		if (!surface)
		{
			SDL_Log("Failed to load texture file %s", fileName.c_str());
			return nullptr;
		}

		// Use the surface to create a texture
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		if (!texture)
		{
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
			return nullptr;
		}

		// Add the texture to the map
		textures.emplace(fileName.c_str(), texture);
	}
	// Return the texture
	return texture;
}


void Game2::shutdown() {
	// Call functions to safely remove actors and close the game
	unloadData();
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


void Game2::addActor(Actor2* actor) {
	// Check to make sure we aren't currently updating actors.
	// If we are not, add to normal actors vector
	if (!updatingActors) { actors.emplace_back(actor); }

	// Otherwise, add the actor to pending actors
	else { pendingActors.emplace_back(actor); }
}


void Game2::removeActor(Actor2* actor) {
	// First check to see if the actor is in pending actors
	auto iter = std::find(pendingActors.begin(), pendingActors.end(), actor);
	if (iter != pendingActors.end()) {
		// Swap the found actor to the end and pop it off (avoid erase copies)
		std::iter_swap(iter, pendingActors.end() - 1);
		pendingActors.pop_back();
	}

	// Now, check to see if it is in the regular actors vector
	iter = std::find(actors.begin(), actors.end(), actor);
	if (iter != actors.end()) {
		// Swap the found actor to the end and pop it off (avoid erase copies)
		std::iter_swap(iter, actors.end() - 1);
		actors.pop_back();
	}
}


void Game2::addSprite(SpriteComponent2* sprite) {
	// Find the insertion point in the sorted vector (first element with a higher draw order)
	int drawOrder = sprite->getDrawOrder();
	auto iter = sprites.begin();
	while (iter != sprites.end()) {
		if (drawOrder < (*iter)->getDrawOrder()) { break; }
	}

	// Insert into the vector
	sprites.insert(iter, sprite);
}


void Game2::removeSprite(SpriteComponent2* sprite) {
	// Find the sprite and remove it (keeping the ordering)
	auto iter = std::find(sprites.begin(), sprites.end(), sprite);
	sprites.erase(iter);
}