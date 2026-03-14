// component2.h

#pragma once

// Forward delectation
class Actor;

// Create the base class for the components to an actor
class Component
{
public:
	// Constructor for a component
	// The lower the updateOrder is, the earlier the component will update when Actor tells it to
	Component(Actor* owner, int updateOrder = 100);

	// Deconstructor (can be changed to match specific situations)
	virtual ~Component();

	// Update this component by delta time
	virtual void update(float deltatime) {};

	// Process input for this component (overridable)
	virtual void processInput(const uint8_t* keyState);

	// Getter for the updateOrder variable (const for read only)
	int getUpdateOrder() const { return updateOrder; }

protected:
	// The actor that will own component
	Actor* owner;

	// The update owner of a component
	int updateOrder;
};
