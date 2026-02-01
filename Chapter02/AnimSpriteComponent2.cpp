
#include "AnimSpriteComponent2.h"
#include "Math.h"

AnimSpriteComponent2::AnimSpriteComponent2(Actor2* owner, int drawOrder)
	:SpriteComponent2(owner, drawOrder) // Call the constructor of the inherited class
	, currentFrame(0.0f)
	, animFPS(24.0f)
{
}


void AnimSpriteComponent2::update(float deltatime)
{
	// First, call the default update defined from the inherited class
	SpriteComponent2::update(deltatime);

	// As long as there are textures in the animation vector, update animation
	if (animTextures.size() > 0) {
		// Update the current frame based on frame rate and delta time
		currentFrame += animFPS * deltatime;

		// Warp current frame if needed
		while (currentFrame >= animTextures.size()) {
			currentFrame -= animTextures.size();
		}

		// Set the current texture
		setTexture(animTextures[static_cast<int>(currentFrame)]);
	}
}


void AnimSpriteComponent2::setAnimTextures(const std::vector<SDL_Texture*>& textures) {
	// Store the vector of textures
	animTextures = textures;

	// If the textures have been set, then set the active texture to the first frame
	if (animTextures.size() > 0) {
		currentFrame = 0.0f;
		setTexture(animTextures[0]);
	}
}
