// Skeleton.cpp

#include "Skeleton.h"
#include "AnimSpriteComponent2.h"
#include "Game2.h"

Skeleton::Skeleton(Game2* game)
	: Actor2(game)
	, horizontalSpeed(0.0f)
	, verticalSpeed(0.0f)
	, isJumping(false)
	, gravity(1200.0f)
	, velocity(-450.0f)
{
	// Create the animations for the skeleton
	asc = new AnimSpriteComponent2(this);

	// Create the walking animation
	std::vector<SDL_Texture*> walkingAnimation = {
		game->getTexture("Assets/Character01.png"),
		game->getTexture("Assets/Character02.png"),
		game->getTexture("Assets/Character03.png"),
		game->getTexture("Assets/Character04.png"),
		game->getTexture("Assets/Character05.png"),
		game->getTexture("Assets/Character06.png")
	};
	asc->addAnimation("walk", walkingAnimation);

	// Create the jumping animation
	std::vector<SDL_Texture*> jumpingAnimation = {
		game->getTexture("Assets/Character07.png"),
		game->getTexture("Assets/Character08.png"),
		game->getTexture("Assets/Character09.png"),
		game->getTexture("Assets/Character10.png"),
		game->getTexture("Assets/Character11.png"),
		game->getTexture("Assets/Character12.png"),
		game->getTexture("Assets/Character13.png"),
		game->getTexture("Assets/Character14.png"),
		game->getTexture("Assets/Character15.png")
	};
	asc->addAnimation("jump", jumpingAnimation);

	// Create the punch animation
	std::vector<SDL_Texture*> punchingAnimation = {
		game->getTexture("Assets/Character16.png"),
		game->getTexture("Assets/Character17.png"),
		game->getTexture("Assets/Character18.png")
	};
	asc->addAnimation("punch", punchingAnimation);

	// Set the idle animation
	std::vector<SDL_Texture*> idleAnimation = {
		game->getTexture("Assets/Character02.png"),
	};
	asc->addAnimation("idle", idleAnimation);
	asc->setCurrentAnimation("idle");

	// Set the speed of the animation
	asc->setAnimFPS(10);
}


void Skeleton::updateActor(float deltatime) {
	// Call the default update actor first
	Actor2::updateActor(deltatime);

	// If falling, apply gravity to skeleton
	if (isJumping) { verticalSpeed += gravity * deltatime; }
	
	// Update position based on speeds and deltatime
	Vector2 pos = getPosition();
	pos.x += horizontalSpeed * deltatime;
	pos.y += verticalSpeed * deltatime;

	// What to do when hitting the ground
	if (pos.y >= 584.0f) {
		// Set the skeleton to be on the ground
		pos.y = 584.0f;
		verticalSpeed = 0.0f;
		isJumping = false;
	}
	
	// Finalize position of skeleton
	setPosition(pos);
}


void Skeleton::processKeyboard(const uint8_t* state) {
	// Default the movement speeds
	horizontalSpeed = 0.0f;

	// Move right or left
	if (state[SDL_SCANCODE_RIGHT])
	{
		horizontalSpeed += 150.0f;
		if (asc->getCurrentAnimation() != "walk" && !isJumping) { asc->setCurrentAnimation("walk"); }
	}
	if (state[SDL_SCANCODE_LEFT])
	{
		horizontalSpeed -= 150.0f;
		if (asc->getCurrentAnimation() != "walk" && !isJumping) { asc->setCurrentAnimation("walk"); }
	}

	// Jump up
	if (state[SDL_SCANCODE_SPACE] && !isJumping)
	{
		verticalSpeed = velocity;
		if (asc->getCurrentAnimation() != "jump") { asc->setCurrentAnimation("jump"); }
		isJumping = true;
	}

	// Set the idle animation
	if (!state[SDL_SCANCODE_RIGHT] && !state[SDL_SCANCODE_LEFT] && !state[SDL_SCANCODE_SPACE]) {
		asc->setCurrentAnimation("idle");
	}

	// Determine whether to flip the sprite
	if (horizontalSpeed < 0) { asc->setFlip(SDL_FLIP_HORIZONTAL); }
	else { asc->setFlip(); }
}