// BGSpriteComponent.h

#pragma once

#include "SpriteComponent.h"
#include "Math.h"
#include <vector>

// Forward declaration
class Actor;

// Component for creating a background
class BGSpriteComponent : public SpriteComponent
{
public:
	// Constructor for the background sprite component class
	// The draw order is lower so that it is drawn first and everything is drawn on top
	BGSpriteComponent(Actor* owner, int drawOrder = 10);

	// Update function for the background component (override from parent)
	void update(float deltatime) override;

	// Draw function for background component (override from parent)
	void draw(SDL_Renderer* renderer) override;

	// Set the textures that will be used for the background
	void setBackgroundTextures(const std::vector<SDL_Texture*>& backgroundTextures);
	
	// Set the screen size
	void setScreenSize(const Vector2& size) { screenSize = size; }

	// Set the scroll speed
	void setScrollSpeed(float speed) { scrollSpeed = speed; }

	// Get the scroll speed
	float getScrollSpeed() const { return scrollSpeed; }

private:
	// Struct to encapsulate each background image and its offset
	struct BGTexture
	{
		SDL_Texture* texture;
		Vector2 offset;
	};

	// Store the textures related to the background
	std::vector<BGTexture> backgroundTextures;

	// Store the screen size
	Vector2 screenSize;

	// Store the scroll speed
	float scrollSpeed;

};
