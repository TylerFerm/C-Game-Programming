// SpriteComponent.cpp

#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"


SpriteComponent::SpriteComponent(Actor* owner, int drawOrder) 
	:Component(owner),
	texture(nullptr),
	drawOrder(drawOrder),
	textureWidth(0),
	textureHeight(0),
	flip(SDL_FLIP_NONE)
{
	// Add this sprite to the list of sprites in game.
	owner->getGame()->addSprite(this);
}


SpriteComponent::~SpriteComponent() {
	// Remove this sprite from the list of sprites in game
	owner->getGame()->removeSprite(this);
}


void SpriteComponent::draw(SDL_Renderer* renderer) {
	// If there is a texture associated with this sprite, then draw it
	if (texture) {
		// Scale the width and height to be based on the owner's scale
		SDL_Rect r;
		r.w = static_cast<int>(textureWidth * owner->getScale());
		r.h = static_cast<int>(textureHeight * owner->getScale());

		// Center the rectangle around the position of the owner
		r.x = static_cast<int>(owner->getPosition().x - r.w / 2);
		r.y = static_cast<int>(owner->getPosition().y - r.h / 2);

		// Draw (making sure to convert angle from radians to degrees)
		SDL_RenderCopyEx(renderer, texture, nullptr, &r, -Math::ToDegrees(owner->getRotation()), nullptr, flip);
	}
}


void SpriteComponent::setTexture(SDL_Texture* texture) {
	// Save the texture
	this->texture = texture;

	// Set the width and the height of this texture
	SDL_QueryTexture(texture, nullptr, nullptr, &textureWidth, &textureHeight);
}