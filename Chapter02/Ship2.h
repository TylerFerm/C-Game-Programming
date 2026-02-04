// Ship2.h

#pragma once
#include "Actor2.h"

// Forward declaration
class Game2;

class Ship2 : public Actor2
{
public:
	// The constructor for the Ship2 class
	Ship2(Game2* game);

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
