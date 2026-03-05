// Ship.h

#pragma once
#include "Actor.h"

// Forward declaration
class Game;

class Ship : public Actor
{
public:
	// The constructor for the Ship class
	Ship(Game* game);

	// The specific update function for this class
	void updateActor(float deltatime) override;

	// How the ship will respond to the keyboard
	void processKeyboard(const uint8_t* state);

	// Getters for the right and down speed
	float getRightSpeed() const { return rightSpeed; }
	float getDownSpeed() const { return downSpeed; }

private:
	float rightSpeed;
	float downSpeed;
};
