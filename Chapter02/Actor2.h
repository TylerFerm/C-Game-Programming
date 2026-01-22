// Definition of the base actor class used for all game objects.

#pragma once
#include <vector>
#include "Math.h"

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

	// Create the constructor (making sure each actor has a reference to game)
	// Dependency injection: actor constructor recieves a pointer to create another actor or...
	// ...access other required Game functions
	Actor2(class Game* game);

	// Deconstructor (virtual as each object may need to be deconstructed in a different way)
	virtual ~Actor2();

	// The update function (not overridable) that will be called in the Game2::updateGame() function.
	// Having this ensures that every actor has a way to update that updateGame() function can use.
	// Acts somewhat as a wrapper for the Actor2::updateActor() function.
	void update(float deltaTime);

	// Updates all the components attached to the actor (not overridable)
	// TODO: Learn more about this function by looking at the code
	void updateComponents(float delatTime);

	// The overridable update actor function that can be customized without messing up the engine code
	virtual void updateActor(float deltaTime);

	// Getter and setter for position (const to make this as a read only function)
	const Vector2& getPosition() const { return position; }
	void setPosition(const Vector2& pos) { position = pos; }

	// Getter and setter for scale
	const float setScale() const { return scale; }
	void setScale(float scale) { scale = this->scale; }

	// Getter and setter for rotation
	const float getRotation() const { return rotation; }
	void setRotation(float rotation) { rotation = this->rotation; }

	// Getter for the pointer to the game class (just so actor can pass it along if necessary)
	class Game* getGame() { return game; }

	// Add or remove componetns from the actor
	void addComponent(class Component* component);
	void removeComponent(class Component* component);

private:
	// Store the state of the actor
	State state;

	// Store the transform properties of the actor
	Vector2 position;
	float scale;
	float rotation;

	// Store the list of components attached to the actor
	std::vector <class Component*> components;

	// Store the pointer to the main game object
	class Game* game;

};