// Skeleton.h

#pragma once
#include "Actor.h"

// Forward declaration
class Game;
class AnimSpriteComponent;

class Skeleton : public Actor
{
public:
	// Constructor for the skeleton class
	Skeleton(Game* game);

	// The specific update function for this class
	void updateActor(float deltatime) override;

	// How the skeleton will respond to the keyboard
	void processKeyboard(const uint8_t* state);

	// Getters for horizontal and vertical speed
	float getHorizontalSpeed() const { return horizontalSpeed; }
	float getVerticalSpeed() const { return verticalSpeed; }

private:
	// Movement speeds
	float horizontalSpeed;
	float verticalSpeed;

	// Constants for jumping
	float gravity;
	float velocity;

	// Used to determine if skeleton is jumping
	bool isJumping;

	// Keep track of the animation component
	AnimSpriteComponent* asc;
};

