// MoveComponent.h

#pragma once
#include "Component.h"

// A class for defining movement (to be attached to an actor)
class MoveComponent : public Component
{
public:
	// Constructor for the MoveComponent class. Has a lower update order so that it can be updated before other components
	MoveComponent(class Actor* owner, int updateOrder = 10);

	// Update function for MoveComponent (override from parent)
	void update(float deltatime) override;

	// Getter for angularSpeed member variable
	float getAngularSpeed() const { return angularSpeed; }

	// Setter for angularSpeed member variable
	void setAngularSpeed(float speed) { angularSpeed = speed; }

	// Getter for forwardSpeed member variable
	float getForwardSpeed() const { return forwardSpeed; }

	// Setter for forwardSpeed member variable
	void setForwardSpeed(float speed) { forwardSpeed = speed; }

private:
	// Controls the rotation of the owner (radians/second)
	float angularSpeed;

	// Controls the forward movement (units/second)
	float forwardSpeed;
};