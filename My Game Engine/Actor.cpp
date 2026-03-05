// Actor.cpp

#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>


Actor::Actor(Game* game)
	:state(Active)				// Set the actor as active
	, position(Vector2::Zero)	// Set the initial position of the actor to be x=0,y=0
	, scale(1.0f)				// Set the scale to be normal (which is 1)
	, rotation(0.0f)			// Set the actor to not be rotated
	, game(game)				// Pass the game object to the actor
{
	// Add this instance of the actor to the list of all actors in game
	game->addActor(this);
}

Actor::~Actor()
{
	// Call the removeActor function from Game to remove the actor from the list of all actors
	game->removeActor(this);

	// Remove every component that is attached to this actor
	while (!components.empty()) {
		// Remove the last element from the vector
		delete components.back();
	}
}

// The non-changeable update code for an actor
void Actor::update(float deltatime) {
	// As long as this actor is active, update all the components and then update the actor so the changes in the...
	// ...components are reflected
	if (state == Active) {
		updateComponents(deltatime);
		updateActor(deltatime);
	}
}

// Update each component attached to this actor
void Actor::updateComponents(float deltatime) {

	// Loop through all the components and call their update function
	for (Component* comp : components) {
		comp->update(deltatime);
	}
}

// Attach a component to this actor
void Actor::addComponent(Component* component) {
	// Find the place to insert the new component
	int updateOrder = component->getUpdateOrder();

	// Create an iterator to pass to the insert function
	auto iter = components.begin();

	// Loop through the components until the correct spot is found
	while (iter != components.end()) {
		// If the update order is less than the current component, then break
		if (updateOrder < (*iter)->getUpdateOrder()) { break; }
		iter++;
	}
	
	// Insert the component into the right place to keep sorted order
	components.insert(iter, component);
}

// Remove a component from this actor
void Actor::removeComponent(Component* component) {
	// Find the location of the component that is to be removed
	auto iter = std::find(components.begin(), components.end(), component);

	// Check to make sure the removed component is actually in the list of components. If so, remove
	if (iter != components.end()) { components.erase(iter); }
}