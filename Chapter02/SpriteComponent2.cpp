// SpriteComponent2.cpp

#include "SpriteComponent2.h"
#include "Actor2.h"
#include "Game2.h"


SpriteComponent2::SpriteComponent2(Actor2* owner, int drawOrder) 
	:Component2(owner),
	texture(nullptr),
	drawOrder(drawOrder),
	textureWidth(0),
	textureHeight(0),
	flip(SDL_FLIP_NONE)
{
	// Add this sprite to the list of sprites in game.
	owner->getGame()->addSprite(this);
}


SpriteComponent2::~SpriteComponent2() {
	// Remove this sprite from the list of sprites in game
	owner->getGame()->removeSprite(this);
}


void SpriteComponent2::draw(SDL_Renderer* renderer) {
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


void SpriteComponent2::setTexture(SDL_Texture* texture) {
	// Save the texture
	this->texture = texture;

	// Set the width and the height of this texture
	SDL_QueryTexture(texture, nullptr, nullptr, &textureWidth, &textureHeight);
}