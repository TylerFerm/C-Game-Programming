// component.h

#pragma once

// Create the base class for the components to an actor
class Component
{
public:
	// Constructor for a component
	// The lower the updateOrder is, the earlier the component will update when Actor tells it to
	Component(class Actor* owner, int updateOrder = 100);

	// Deconstructor (can be changed to match specific situations)
	virtual ~Component();

	// Update this component by delta time
	virtual void update(float deltatime);

	// Getter for the updateOrder variable (const for read only)
	int gteUpdateOrder() const { return updateOrder; }

protected:
	// The actor that will own component
	class Actor* owner;

	// The update owner of a component
	int updateOrder;
};
