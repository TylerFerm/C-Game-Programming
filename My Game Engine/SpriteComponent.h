// SpriteComponent.h

#pragma once

#include "Component.h"
#include "SDL/SDL.h"

// Forward declaration
class Actor;

// Define a component that let's an actor have an associated sprite
class SpriteComponent : public Component
{
public:
	// Constructor for a SpriteComponent
	// The lower the draw order the farther back the sprite will be
	SpriteComponent(Actor* owner, int drawOrder = 100);

	// Deconstructor for SpriteComponent
	~SpriteComponent();

	// Overridable draw function
	virtual void draw(SDL_Renderer* renderer);

	// Overridable texture setting function
	virtual void setTexture(SDL_Texture* texture);

	// Get the draw order
	int getDrawOrder() const { return drawOrder; }
	int getTextureWidth() const { return textureWidth; }
	int getTextureHeight() const { return textureHeight; }

	// Flip the sprite the desired way
	void setFlip(SDL_RendererFlip flip = SDL_FLIP_NONE) { this->flip = flip; }

// Allow inherited classes to use these member variables
protected:
	SDL_Texture* texture;
	int drawOrder;
	int textureWidth;
	int textureHeight;

	// Determine whether to flip the sprite
	SDL_RendererFlip flip;
};