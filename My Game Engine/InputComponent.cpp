// InputComponent.cpp

#include "InputComponent.h"
#include "Actor.h"

InputComponent::InputComponent(Actor* owner)
	:MoveComponent(owner)
	,forwardKey(0)
	,backKey(0)
	,clockwiseKey(0)
	,counterClockwiseKey(0)
{
}


void InputComponent::processInput(const uint8_t* keyState) {
	// Calculate forward speed for movement component
	float forwardSpeed = 0.0f;
	if (keyState[forwardKey]) { forwardSpeed += maxForwardSpeed; }
	if (keyState[backKey]) { forwardSpeed -= maxForwardSpeed; }
	setForwardSpeed(forwardSpeed);

	// Calculate angular speed for MoveComponent
	float angularSpeed = 0.0f;
	if (keyState[clockwiseKey]) { angularSpeed += maxAngularSpeed; }
	if (keyState[counterClockwiseKey]) { angularSpeed -= maxAngularSpeed; }
	setAngularSpeed(angularSpeed);
}
