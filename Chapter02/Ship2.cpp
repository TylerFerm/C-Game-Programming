// Ship2.cpp

#include "Ship2.h"
#include "AnimSpriteComponent2.h"
#include "Game2.h"

Ship2::Ship2(Game2* game)
	: Actor2(game)
	, rightSpeed(0.0f)
	, downSpeed(0.0f)
{
	// Create an animated sprite component
	AnimSpriteComponent2* asc = new AnimSpriteComponent2(this);
	std::vector<SDL_Texture*> anims = {
		game->getTexture("Assets/Ship01.png"),
		game->getTexture("Assets/Ship02.png"),
		game->getTexture("Assets/Ship03.png"),
		game->getTexture("Assets/Ship04.png")
	};
	asc->setAnimTextures(anims);
}


void Ship2::updateActor(float deltatime) {
	// Call the default update actor first
	Actor2::updateActor(deltatime);

	// Update position based on speeds and deltatime
	Vector2 pos = getPosition();
	pos.x += rightSpeed * deltatime;
	pos.y += downSpeed * deltatime;

	// Restrict position to left half of screen
	if (pos.x < 25.0f)
	{
		pos.x = 25.0f;
	}
	else if (pos.x > 500.0f)
	{
		pos.x = 500.0f;
	}
	if (pos.y < 25.0f)
	{
		pos.y = 25.0f;
	}
	else if (pos.y > 743.0f)
	{
		pos.y = 743.0f;
	}

	// Finalize the position of the ship
	setPosition(pos);
}


void Ship2::processKeyboard(const uint8_t* state)
{
	rightSpeed = 0.0f;
	downSpeed = 0.0f;
	// right/left
	if (state[SDL_SCANCODE_D])
	{
		rightSpeed += 250.0f;
	}
	if (state[SDL_SCANCODE_A])
	{
		rightSpeed -= 250.0f;
	}
	// up/down
	if (state[SDL_SCANCODE_S])
	{
		downSpeed += 300.0f;
	}
	if (state[SDL_SCANCODE_W])
	{
		downSpeed -= 300.0f;
	}
}