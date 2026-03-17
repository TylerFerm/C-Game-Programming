// InputComponent.h

#pragma once
#include "MoveComponent.h"
#include <cstdint>

// Class for managing input
class InputComponent : public MoveComponent
{
public:
	// Constructor for InputComponent (give it a lower update order to update first)
	InputComponent(class Actor* owner);

	// Override the processInput function from Component
	void processInput(const uint8_t* keyState) override;

	// Getters and setters for private member variables
	float getMaxForward() const { return maxForwardSpeed; }
	float getMaxAngular() const { return maxAngularSpeed; }
	int getForwardKey() const { return forwardKey; }
	int getBackKey() const { return backKey; }
	int getClockwiseKey() const { return clockwiseKey; }
	int getCounterClockwiseKey() const { return counterClockwiseKey; }

	void setMaxForwardSpeed(float speed) { maxForwardSpeed = speed; }
	void setMaxAngularSpeed(float speed) { maxAngularSpeed = speed; }
	void setForwardKey(int key) { forwardKey = key; }
	void setBackKey(int key) { backKey = key; }
	void setClockwiseKey(int key) { clockwiseKey = key; }
	void setCounterClockwiseKey(int key) { counterClockwiseKey = key; }
private:
	// The maximum forward/angular speeds
	float maxForwardSpeed;
	float maxAngularSpeed;

	// Keys for forward/back movement
	int forwardKey;
	int backKey;

	// Keys for angular movement
	int clockwiseKey;
	int counterClockwiseKey;
};