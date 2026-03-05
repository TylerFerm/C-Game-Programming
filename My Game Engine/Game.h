// Definition of the game class


#pragma once // prevents multiple inclusions 

#include "SDL/SDL.h"
#include <unordered_map>
#include <string>
#include <vector>

// Forward declaration
class Skeleton;

class Game
{
public:
	// Default initialize of the game class
	Game();

	// Initialize the game, returning true if all elements are initialized correctly
	bool initialize();

	// Run the game loop: input, update, draw
	void runLoop();

	// Shutdown the game by safely closing what needs to be closed
	void shutdown();

	// Add or remove a new actor to/from the list of actors
	void addActor(class Actor* actor);
	void removeActor(class Actor* actor);

	// Add or remove a new sprite t0/from the list of sprites
	void addSprite(class SpriteComponent* sprite);
	void removeSprite(class SpriteComponent* sprite);

	// Get a texture either from file or from a map of textures
	SDL_Texture* getTexture(const std::string& fileName);

private:
	// Define the 3 key steps of the game loop
	void processInput();
	void updateGame();
	void generateOutput();

	// Chapter 2 game specific functions for loading assets and creating actors
	void loadData();
	void unloadData();

	// Keep a map of the textures loaded (TODO: learn more about how this works)
	// This is so that multiple actors can use the same texture without having to load it from the file again
	std::unordered_map <std::string, SDL_Texture*> textures;

	// Store a vector of all the actors in the game
	std::vector <class Actor*> actors;

	// Store a vector of all the pending actors in the game
	// This is needed to handle the case where, while updating the actors (looping over the actors vector)...
	// ...you decide to create a new actor. In this case, you cannot add an element to the actors vector because...
	// ...you are iterating over it. Once iteration is done, then you can move this actors to the main actors vector
	std::vector <class Actor*> pendingActors;

	// All the sprite components drawn (acts similar to the actors vector)
	std::vector <class SpriteComponent*> sprites;

	// Create the window for the game
	SDL_Window* window;
	
	// Create the renderer for the game
	SDL_Renderer* renderer;

	// Other game related metrics
	Uint32 ticksCount;
	bool isRunning;

	// Track if we are updating actors right now (so does the actor go straight to the actors vector or pendingActors vector
	bool updatingActors;

	// Game specific
	class Ship* ship;
	Skeleton* skeleton;
};