// BGSpriteComponent.cpp

#include "BGSpriteComponent.h"
#include "Actor.h"

BGSpriteComponent::BGSpriteComponent(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	,scrollSpeed(0.0f)
{
}


void BGSpriteComponent::update(float deltatime) {
	// Call the default update function from parent
	SpriteComponent::update(deltatime);

	// For each texture in the background texture vector, update it
	for (BGTexture& bg : backgroundTextures) {
		// Update the x offset
		bg.offset.x += scrollSpeed * deltatime;

		// If this is completely off screen, reset offset to the right of the last bg texture
		if (bg.offset.x < -screenSize.x) {
			bg.offset.x = (backgroundTextures.size() - 1) * screenSize.x - 1;
		}
	}
}


void BGSpriteComponent::draw(SDL_Renderer* renderer) {
	// Draw each background texture
	for (BGTexture& bg : backgroundTextures) {
		
		SDL_Rect r;
		// Assume screen size dimensions
		r.w = static_cast<int>(screenSize.x);
		r.h = static_cast<int>(screenSize.y);
		// Center the rectangle around the position of the owner
		r.x = static_cast<int>(owner->getPosition().x - r.w / 2 + bg.offset.x);
		r.y = static_cast<int>(owner->getPosition().y - r.h / 2 + bg.offset.y);

		// Draw this background
		SDL_RenderCopy(renderer, bg.texture, nullptr, &r);
	}
}


void BGSpriteComponent::setBackgroundTextures(const std::vector<SDL_Texture*>& textures) {
	// Keep track of the number of textures
	int count = 0;
	// For each texture in the provided vector, add them to the background textures vector
	for (SDL_Texture* texture : textures) {
		// Store the offset and texture together
		BGTexture temp;
		temp.texture = texture;

		// Each texture is screen width in offset
		temp.offset.x = count * screenSize.x;
		temp.offset.y = 0;

		// Add the texture to the vector
		backgroundTextures.emplace_back(temp);
		count++;
	}
}