// SpriteComponent2.h

#pragma once

#include "Component2.h"
#include "SDL/SDL.h"

// Forward declaration
class Actor2;

// Define a component that let's an actor have an associated sprite
class SpriteComponent2 : public Component2
{
public:
	// Constructor for a SpriteComponent
	// The lower the draw order the farther back the sprite will be
	SpriteComponent2(Actor2* owner, int drawOrder = 100);

	// Deconstructor for SpriteComponent
	~SpriteComponent2();

	// Overridable draw function
	virtual void draw(SDL_Renderer* renderer);

	// Overridable texture setting function
	virtual void setTexture(SDL_Texture* texture);

	// Get the draw order
	int getDrawOrder() const { return drawOrder; }
	int getTextureWidth() const { return textureWidth; }
	int getTextureHeight() const { return textureHeight; }

// Allow inherited classes to use these member variables
protected:
	SDL_Texture* texture;
	int drawOrder;
	int textureWidth;
	int textureHeight;
};