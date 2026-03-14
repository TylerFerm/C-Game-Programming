// MoveComponent.cpp

#include "MoveComponent.h"
#include "Actor.h"

// Constructor for MoveComponent
MoveComponent::MoveComponent(Actor* owner, int updateOrder)
	:Component(owner, updateOrder)
	,angularSpeed(0.0f)
	,forwardSpeed(0.0f)
{
}

// Overridden update function for MoveComponent
void MoveComponent::update(float deltatime) {
	// If the angularSpeed of the actor is not near zero or zero, then rotate the actor
	if (!Math::NearZero(angularSpeed)) {
		// Set the rotation based on current rotation and angularSpeed
		owner->setRotation(owner->getRotation() + (angularSpeed * deltatime));
	}

	// If the forwardSpeed of the actor is not near zero or zero, then move actor forward
	if (!Math::NearZero(forwardSpeed)) {
		// Set the new position of the actor based on forwardSpeed and deltatime and direction
		Vector2 pos = owner->getPosition();
		pos += owner->getForward() * forwardSpeed * deltatime;

		// (Screen wrapping code only for asteroids)
		// TODO: Extract this out maybe
		if (pos.x < 0.0f) { pos.x = 1022.0f; }
		else if (pos.x > 1024.0f) { pos.x = 2.0f; }

		if (pos.y < 0.0f) { pos.y = 766.0f; }
		else if (pos.y > 768.0f) { pos.y = 2.0f; }

		// Set the new position
		owner->setPosition(pos);
	}
}