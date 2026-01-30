// component2.cpp

#include "Component2.h"
#include "Actor2.h"

// Define the constructor for the component class
Component2::Component2(Actor2* owner, int updateOrder)
	:owner(owner),
	updateOrder(updateOrder)
{
	// Add this component to the actor's list of components
	owner->addComponent(this);
}

// Define the deconstructor for the component class
Component2::~Component2() {
	owner->removeComponent(this);
}