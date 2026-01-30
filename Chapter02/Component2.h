// component2.h

#pragma once

// Forward delectation
class Actor2;

// Create the base class for the components to an actor
class Component2
{
public:
	// Constructor for a component
	// The lower the updateOrder is, the earlier the component will update when Actor tells it to
	Component2(Actor2* owner, int updateOrder = 100);

	// Deconstructor (can be changed to match specific situations)
	virtual ~Component2();

	// Update this component by delta time
	virtual void update(float deltatime) {};

	// Getter for the updateOrder variable (const for read only)
	int getUpdateOrder() const { return updateOrder; }

protected:
	// The actor that will own component
	class Actor2* owner;

	// The update owner of a component
	int updateOrder;
};
