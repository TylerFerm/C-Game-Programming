// component2.cpp

#include "Component.h"
#include "Actor.h"

// Define the constructor for the component class
Component::Component(Actor* owner, int updateOrder)
	:owner(owner),
	updateOrder(updateOrder)
{
	// Add this component to the actor's list of components
	owner->addComponent(this);
}

// Define the deconstructor for the component class
Component::~Component() {
	owner->removeComponent(this);
}