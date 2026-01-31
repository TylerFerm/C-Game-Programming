// Definition of the base actor class used for all game objects.

#pragma once
#include <vector>
#include "Math.h"

// Forward deceleration
class Game2;
class Component2;

// Define the base class for all game objects (actors)
class Actor2
{
public:
	// Define the possible states of the actor.
	enum State {
		Active,
		Paused,
		Dead
	};

	/*
	The constructor for the Actor class. Adds the actor to the list of all actors in game.
	
	Dependency injection: actor constructor receives a pointer to create another actor or...
	...access other required Game functions

	Parameters:
		Game* game: A pointer to the game object

	Return: nothing.
	*/
	Actor2(Game2* game);

	// Deconstructor (virtual as each object may need to be deconstructed in a different way)
	virtual ~Actor2();

	// The update function (not overridable) that will be called in the Game2::updateGame() function.
	// Having this ensures that every actor has a way to update that updateGame() function can use.
	// Acts somewhat as a wrapper for the Actor2::updateActor() function.
	void update(float deltaTime);

	// Updates all the components attached to the actor (not overridable)
	void updateComponents(float delatTime);

	// The overridable update actor function that can be customized without messing up the engine code
	virtual void updateActor(float deltaTime) {};

	// Getter and setter for position (const to make this as a read only function)
	const Vector2& getPosition() const { return position; }
	void setPosition(const Vector2& pos) { position = pos; }

	// Getter and setter for scale
	const float getScale() const { return scale; }
	void setScale(float scale) { scale = this->scale; }

	// Getter and setter for rotation
	const float getRotation() const { return rotation; }
	void setRotation(float rotation) { rotation = this->rotation; }

	// Getter for the pointer to the game class (just so actor can pass it along if necessary)
	Game2* getGame() { return game; }

	// Add or remove components from the actor
	void addComponent(Component2* component);
	void removeComponent(Component2* component);

private:
	// Store the state of the actor
	State state;

	// Store the transform properties of the actor
	Vector2 position;
	float scale;
	float rotation;

	// Store the list of components attached to the actor
	std::vector <Component2*> components;

	// Store the pointer to the main game object
	Game2* game;

};