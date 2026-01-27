// Actor2.cpp

#include "Actor2.h"
#include "Game2.h"
#include "Component2.h"
#include <algorithm>


Actor2::Actor2(Game* game)
	:state(Active)				// Set the actor as active
	, position(Vector2::Zero)	// Set the initial position of the actor to be x=0,y=0
	, scale(1.0f)				// Set the scale to be normal (which is 1)
	, rotation(0.0f)			// Set the actor to not be rotated
	, game(game)				// Pass the game object to the actor
{
	// Add this instance of the actor to the list of all actors in game
	// TODO: Uncomment when game.cpp is done game->addActor(this);
}

Actor2::~Actor2()
{
	// Call the removeActor function from Game to remove the actor from the list of all actors
	// TODO: Uncomment when game.cpp is done game->removeActor(this);

	// Remove every component that is attached to this actor
	while (!components.empty()) {
		// Remove the last element from the vector
		delete components.back();
	}
}

// The non-changeable update code for an actor
void Actor2::update(float deltatime) {
	// As long as this actor is active, update all the components and then update the actor so the changes in the...
	// ...components are reflected
	if (state == Active) {
		updateComponents(deltatime);
		updateActor(deltatime);
	}
}

// TODO: Continue Actor2.cpp